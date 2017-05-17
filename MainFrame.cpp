#include "stdafx.h"
#include "GUI.h"
#include "MainFrame.h"
#include "TBoardPanel.h"
#include "SettingsDialog.h"
#include "Zobrist.h"
#include "Random.h"
#include "Utils.h"
#include "Network.h"
#include "Matcher.h"
#include "AttribScores.h"
#include "SGFTree.h"
#include "SGFParser.h"
#include "GTP.h"
#include "SMP.h"
#include "Network.h"
#include "EngineThread.h"
#include "AboutDialog.h"
#include "NewGameDialog.h"
#include "ClockAdjustDialog.h"
#include "RatedSizeDialog.h"
#include "CalculateDialog.h"
#include "AnalysisWindow.h"
#include "ScoreDialog.h"
#include "ScoreHistogram.h"
#include "MCOTable.h"
#ifndef WIN32
#include "img/leela_mock.xpm"
#include "snd/tock.h"
#endif

wxDEFINE_EVENT(wxEVT_NEW_MOVE, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_BOARD_UPDATE, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_STATUS_UPDATE, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_ANALYSIS_UPDATE, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_BESTMOVES_UPDATE, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_EVALUATION_UPDATE, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_SET_MOVENUM, wxCommandEvent);

#define MAX_RANK  13
#define MIN_RANK -30

MainFrame::MainFrame(wxFrame *frame, const wxString& title)
          :TMainFrame(frame, wxID_ANY, title) {

    delete wxLog::SetActiveTarget(NULL);

    wxLog::SetTimestamp("");

    Bind(wxEVT_NEW_MOVE, &MainFrame::doNewMove, this);
    Bind(wxEVT_BOARD_UPDATE, &MainFrame::doBoardUpdate, this);
    Bind(wxEVT_STATUS_UPDATE, &MainFrame::doStatusUpdate, this);
    Bind(wxEVT_DESTROY, &MainFrame::doCloseChild, this);
    // Receive movenum changes (from history panel)
    Bind(wxEVT_SET_MOVENUM, &MainFrame::gotoMoveNum, this);
    // Forward to histogram window, if it exists
    Bind(wxEVT_EVALUATION_UPDATE, &MainFrame::doEvalUpdate, this);
    // Forward mainline updates to the board panel
    Bind(wxEVT_DISPLAY_MAINLINE, [=](wxCommandEvent& event) {
        m_panelBoard->GetEventHandler()->AddPendingEvent(event);
    });
    // Forward top moves to board panel
    Bind(wxEVT_BESTMOVES_UPDATE, [=](wxCommandEvent& event) {
        m_panelBoard->GetEventHandler()->AddPendingEvent(event);
    });
    // Forward to analysis window, if it exists
    Bind(wxEVT_ANALYSIS_UPDATE, [=](wxCommandEvent& event) {
        if (m_analysisWindow) {
            m_analysisWindow->GetEventHandler()->AddPendingEvent(event);
        } else {
            // Need to free up the analysis data
            if (!event.GetClientData()) return;

            using TRowVector = std::vector<std::pair<std::string, std::string>>;
            using TDataVector = std::vector<TRowVector>;

            delete reinterpret_cast<TDataVector*>(event.GetClientData());
        }
    });

    GTP::setup_default_parameters();

    std::unique_ptr<Random> rng(new Random(5489UL));
    Zobrist::init_zobrist(*rng);
    AttribScores::get_attribscores();
    Matcher::get_Matcher();
    Network::get_Network();

    // init game
    m_playerColor = FastBoard::BLACK;
    m_visitLimit = 5000;
    m_ratedGame = true;
    m_analyzing = false;
    m_pondering = false;
    m_disputing = false;
    m_ponderedOnce = true;

    m_netsEnabled = wxConfig::Get()->Read(wxT("netsEnabled"), 1);
    m_passEnabled = wxConfig::Get()->Read(wxT("passEnabled"), 1);
    m_soundEnabled = wxConfig::Get()->Read(wxT("soundEnabled"), 1);
    m_resignEnabled = wxConfig::Get()->Read(wxT("resignEnabled"), 1);
    m_ponderEnabled = wxConfig::Get()->Read(wxT("ponderEnabled"), 1);
    m_ratedSize     = wxConfig::Get()->Read(wxT("ratedSize"), 9);

    // This is a bug in 0.4.0, correct broken values.
    if (m_ratedSize != 9 && m_ratedSize != 19) {
        m_ratedSize = 9;
    }

#ifdef USE_OPENCL
    m_State.init_game(19, 7.5f);
    if (!GTP::perform_self_test(m_State)) {
        ::wxMessageBox(_("OpenCL self-test failed. Check your graphics drivers."),
                       _("Leela"), wxOK | wxICON_EXCLAMATION, this);
        Close();
    }
#endif

    m_State.init_game(m_ratedSize, 7.5f);
    m_State.set_timecontrol(2 * m_ratedSize * 60 * 100, 0, 0, 0);
    m_StateStack.clear();
    m_panelBoard->setState(&m_State);
    m_panelBoard->setPlayerColor(m_playerColor);
    m_menuAnalyze->FindItem(ID_ANALYSISWINDOWTOGGLE)->Check(false);

    // set us as the global message receiver
    Utils::setGUIQueue(this->GetEventHandler(), wxEVT_STATUS_UPDATE);

    // send analysis events here
    Utils::setAnalysisQueue(this->GetEventHandler(),
                            wxEVT_ANALYSIS_UPDATE,
                            wxEVT_BESTMOVES_UPDATE);

    SetIcon(wxICON(aaaa));

#ifdef __WXGTK__
    SetSize(550, 640);
#elif defined(__WXMAC__)
    SetSize(570, 640);
#else
    SetSize(530, 640);
#endif
    Center();

    wxCommandEvent evt;
    doNewRatedGame(evt);

    setActiveMenus();
}

MainFrame::~MainFrame() {
    stopEngine();

    delete wxLog::SetActiveTarget(new wxLogStderr(NULL));
    m_panelBoard->setState(NULL);

    Unbind(wxEVT_EVALUATION_UPDATE, &MainFrame::doEvalUpdate, this);
    Unbind(wxEVT_NEW_MOVE, &MainFrame::doNewMove, this);
    Unbind(wxEVT_BOARD_UPDATE, &MainFrame::doBoardUpdate, this);
    Unbind(wxEVT_STATUS_UPDATE, &MainFrame::doStatusUpdate, this);
    Unbind(wxEVT_DESTROY, &MainFrame::doCloseChild, this);

    Hide();
}

void MainFrame::doStatusUpdate(wxCommandEvent& event) {
    m_statusBar->SetStatusText(event.GetString(), 1);
}

void MainFrame::SetStatusBar(wxString mess, int pos) {
    m_statusBar->SetStatusText(mess, pos);
}

void MainFrame::updateStatusBar(char *str) {
    //wxString wxstr(str);
    //SetStatusText(str);
}

// do whatever we need to do if the visible board gets updated
void MainFrame::doBoardUpdate(wxCommandEvent& event) {
    wxString mess;
    mess.Printf(_("Komi: %d.5; Prisoners white: %d/black: %d"),
                (int)m_State.get_komi(),
                m_State.board.get_prisoners(FastBoard::BLACK),
                m_State.board.get_prisoners(FastBoard::WHITE)
                );
    m_statusBar->SetStatusText(mess, 0);
    Refresh();
}

void MainFrame::doExit(wxCommandEvent & event) {
    Close();
}

void MainFrame::startEngine() {
    if (!m_engineThread) {
        m_engineThread.reset(new TEngineThread(&m_State, this));
        if (m_engineThread->Create(1024 * 1024) != wxTHREAD_NO_ERROR) {
            wxLogDebug("Error starting engine");
        } else {
            m_engineThread->SetPriority(wxPRIORITY_MIN);
            // lock the board
            if (!m_pondering && !m_analyzing) {
                m_panelBoard->lockState();
            }

            m_engineThread->limit_visits(m_visitLimit);
            m_engineThread->set_resigning(m_resignEnabled);
            m_engineThread->set_analyzing(m_analyzing | m_pondering);
            m_engineThread->set_pondering(m_pondering);
            m_engineThread->set_quiet(!m_analyzing);
            m_engineThread->set_nets(m_netsEnabled);
            if (m_passEnabled) {
                m_engineThread->set_nopass(m_disputing);
            } else {
                m_engineThread->set_nopass(true);
            }
            m_engineThread->Run();
            SetStatusBar(_("Engine thinking..."), 1);
        }
    } else {
        wxLogDebug("Engine already running");
    }
}

bool MainFrame::stopEngine(bool update_score) {
    if (!m_engineThread) return false;
    if (!update_score) {
        m_engineThread->kill_score_update();
    }
    m_engineThread->stop_engine();
    m_engineThread->Wait();
    m_engineThread.reset(nullptr);
    return true;
}

void MainFrame::doToggleTerritory(wxCommandEvent& event) {
    m_panelBoard->setShowOwner(!m_panelBoard->getShowOwner());
    
    if (m_panelBoard->getShowOwner()) {
        m_panelBoard->setShowMoyo(false);
        wxMenuItem * moyo = m_menuTools->FindItem(ID_SHOWMOYO);
        moyo->Check(false);
        gameNoLongerCounts();
    }
    
    m_panelBoard->setShowTerritory(false);
    
    m_panelBoard->Refresh();
}

void MainFrame::doToggleMoyo(wxCommandEvent& event) {
    m_panelBoard->setShowMoyo(!m_panelBoard->getShowMoyo());
    
    if (m_panelBoard->getShowMoyo()) {
        m_panelBoard->setShowOwner(false);
        wxMenuItem * influence = m_menuTools->FindItem(ID_SHOWTERRITORY);
        influence->Check(false);
    }

    m_panelBoard->setShowTerritory(false);
    
    m_panelBoard->Refresh();
}

void MainFrame::doToggleProbabilities(wxCommandEvent& event) {
    m_panelBoard->setShowProbabilities(!m_panelBoard->getShowProbabilities());

    if (m_panelBoard->getShowProbabilities()) {
        gameNoLongerCounts();
    }

    if (m_panelBoard->getShowBestMoves()) {
        m_panelBoard->setShowBestMoves(false);
        wxMenuItem * bm = m_menuTools->FindItem(ID_BEST_MOVES);
        bm->Check(false);
    }

    m_panelBoard->Refresh();
}

void MainFrame::doToggleBestMoves(wxCommandEvent& event) {
    m_panelBoard->setShowBestMoves(!m_panelBoard->getShowBestMoves());

    if (m_panelBoard->getShowBestMoves()) {
        gameNoLongerCounts();
    }

    if (m_panelBoard->getShowProbabilities()) {
        m_panelBoard->setShowProbabilities(false);
        wxMenuItem * prob = m_menuTools->FindItem(ID_MOVE_PROBABILITIES);
        prob->Check(false);
    }

    m_panelBoard->Refresh();
}

void MainFrame::doNewMove(wxCommandEvent & event) {
    wxLogDebug(_("New move arrived"));

    stopEngine();
    m_panelBoard->unlockState();
    m_panelBoard->clearViz();

    if (m_pondering) {
        m_pondering = false;
        m_ponderedOnce = true;
    } else {
        m_ponderedOnce = false;
    }

    if (m_State.get_last_move() != FastBoard::PASS) {
        if (m_soundEnabled) {
#ifdef WIN32
            wxSound tock("IDW_TOCK", true);
#else
            wxSound tock(tock_data_length, tock_data);
#endif
            tock.Play(wxSOUND_ASYNC);
        }
    } else {
        if (m_State.get_to_move() == m_playerColor
            && m_State.get_last_move() == FastBoard::PASS) {

            ::wxMessageBox(_("Computer passes"), _("Pass"), wxOK, this);
        }
    }

    if (m_State.get_passes() >= 2 || m_State.get_last_move() == FastBoard::RESIGN) {
        float komi, score, prekomi, handicap;
        bool won = scoreGame(komi, handicap, score, prekomi);
        bool accepts = scoreDialog(komi, handicap, score, prekomi);
        if (accepts || m_State.get_last_move() == FastBoard::RESIGN) {
            ratedGameEnd(won);
        } else {
            m_disputing = true;
            // undo passes
            m_State.undo_move();
            m_State.undo_move();
            if (m_State.get_to_move() != m_playerColor) {
                wxLogDebug("Computer to move");
                startEngine();
            } else {
                m_pondering = true;
                startEngine();
            }
        }
    } else {
        if (!m_analyzing) {
            if (m_State.get_to_move() != m_playerColor) {
                wxLogDebug("Computer to move");
                startEngine();
            } else {
                if (m_ponderEnabled && !m_ratedGame && !m_analyzing
                    && !m_ponderedOnce && !m_visitLimit) {
                    m_pondering = true;
                    startEngine();
                }
            }
        }  else {
            startEngine();
            m_panelBoard->unlockState();
            m_playerColor = m_State.get_to_move();
            m_panelBoard->setPlayerColor(m_playerColor);
        }
        m_panelBoard->setShowTerritory(false);
    }

    if (!m_ratedGame) {
        this->SetTitle(_("Leela") +
                       _(" - move " + wxString::Format(wxT("%i"), m_State.get_movenum() + 1)));
    }

    // signal update of visible board
    wxCommandEvent myevent(wxEVT_BOARD_UPDATE, GetId());
    myevent.SetEventObject(this);
    ::wxPostEvent(m_panelBoard->GetEventHandler(), myevent);
    broadcastCurrentMove();
}

void MainFrame::doPaint(wxPaintEvent& event) {    
    //wxPaintDC tmp(this);        
    event.Skip();           
}

void MainFrame::doActivate(wxActivateEvent& event) {                       
    event.Skip();
}

void MainFrame::doResize(wxSizeEvent& event) {
    event.Skip();
}

void MainFrame::doBoardResize(wxSizeEvent& event) {
    event.Skip();
}

void MainFrame::doSettingsDialog(wxCommandEvent& event) {
    bool wasPondering = m_pondering;
    bool wasRunning = stopEngine();
    bool wasAnalyzing = wasRunning && !wasPondering;    

    SettingsDialog mydialog(this);

    if (mydialog.ShowModal() == wxID_OK) {
        wxLogDebug("OK clicked");

        m_netsEnabled = wxConfig::Get()->Read(wxT("netsEnabled"), 1);
        m_passEnabled = wxConfig::Get()->Read(wxT("passEnabled"), 1);
        m_soundEnabled = wxConfig::Get()->Read(wxT("soundEnabled"), 1);
        m_resignEnabled = wxConfig::Get()->Read(wxT("resignEnabled"), 1);
        m_ponderEnabled = wxConfig::Get()->Read(wxT("ponderEnabled"), 1);
    }

    wxCommandEvent dummy;
    if (wasAnalyzing) doAnalyze(dummy);
}

void MainFrame::doNewGame(wxCommandEvent& event) {
    stopEngine(false);

    NewGameDialog mydialog(this);

    if (mydialog.ShowModal() == wxID_OK) {
        wxLogDebug("OK clicked");

        m_State.init_game(mydialog.getBoardsize(), mydialog.getKomi());
        ::wxBeginBusyCursor();
        CalculateDialog calcdialog(this);
        calcdialog.Show();
        //::wxSafeYield();
        m_State.set_timecontrol(30 * 100, 0, 0, 0);
        m_State.place_free_handicap(mydialog.getHandicap());
        calcdialog.Hide();
        ::wxEndBusyCursor();
        MCOwnerTable::clear();
        m_panelBoard->clearViz();
        if (m_scoreHistogramWindow) {
            m_scoreHistogramWindow->ClearHistogram();
        }
        m_State.set_timecontrol(mydialog.getTimeControl() * 60 * 100, 0, 0, 0);
        m_StateStack.clear();
        m_visitLimit = mydialog.getSimulations();
        m_playerColor = mydialog.getPlayerColor();
        // XXX
        m_netsEnabled = mydialog.getNetsEnabled();
        wxConfig::Get()->Write(wxT("netsEnabled"), m_netsEnabled);
        setActiveMenus();
        // XXX
        m_panelBoard->setPlayerColor(m_playerColor);
        m_panelBoard->setShowTerritory(false);
        m_analyzing = false;
	m_pondering = false;
        m_disputing = false;
        gameNoLongerCounts();

        wxCommandEvent myevent(wxEVT_NEW_MOVE, GetId());
        myevent.SetEventObject(this);
        ::wxPostEvent(m_panelBoard->GetEventHandler(), myevent);
        broadcastCurrentMove();
    }
}

void MainFrame::setActiveMenus() {
    int boardsize = m_State.board.get_boardsize();
    if (boardsize != 19) {
        m_menuTools->FindItem(ID_MOVE_PROBABILITIES)->Enable(false);
    } else {
        m_menuTools->FindItem(ID_MOVE_PROBABILITIES)->Enable(true);
    }
    if (m_StateStack.empty()) {
        m_menuAnalyze->FindItem(ID_POPPOS)->Enable(false);
        m_menuAnalyze->FindItem(ID_MAINLINE)->Enable(false);
        GetToolBar()->EnableTool(ID_POPPOS, false);
        GetToolBar()->EnableTool(ID_MAINLINE, false);
    } else {
        m_menuAnalyze->FindItem(ID_POPPOS)->Enable(true);
        m_menuAnalyze->FindItem(ID_MAINLINE)->Enable(true);
        GetToolBar()->EnableTool(ID_POPPOS, true);
        GetToolBar()->EnableTool(ID_MAINLINE, true);
    }
}

void MainFrame::doSetRatedSize(wxCommandEvent& event) {
    RatedSizeDialog mydialog(this);
    mydialog.ShowModal();

    m_ratedSize = mydialog.getSizeSelected();

    wxConfig::Get()->Write(wxT("ratedSize"), m_ratedSize);

    doNewRatedGame(event);
}

void MainFrame::doNewRatedGame(wxCommandEvent& event) {
    stopEngine(false);

    m_analyzing = false;
    m_disputing = false;
    m_pondering = false;

    int rank;
    if (m_ratedSize == 9) {
        rank = wxConfig::Get()->Read(wxT("LastRank9"), (long)-30);
    } else if (m_ratedSize == 19) {
        rank = wxConfig::Get()->Read(wxT("LastRank19"), (long)-10);
    }

    wxLogDebug("Last rank was: %d", rank);

    wxString mess = wxString(_("Your rank: "));
    mess += rankToString(rank);
    m_statusBar->SetStatusText(mess, 1);

    this->SetTitle(_("Leela - ") + mess);
    if (m_analysisWindow) {
        m_analysisWindow->Close();
    }
    if (m_scoreHistogramWindow) {
        m_scoreHistogramWindow->Close();
    }

    int used_rank = rank;
    int handicap;
    int simulations;

    // Correct for neural network enabled
    if (m_ratedSize == 19) {
        if (m_netsEnabled) {
            // Estimate it as being worth 7 stones
            used_rank = rank - 7;
        }
    }

    if (m_ratedSize == 9) {
        if (used_rank == -30) {
            simulations =  250;
            handicap = 5;
        } else if (used_rank == -29) {
            simulations =  500;
            handicap = 5;
        } else if (used_rank == -28) {
            simulations = 1000;
            handicap = 5;
        } else if (used_rank == -27) {
            simulations = 2500;
            handicap = 5;
        } else if (used_rank == -26) {
            simulations = 5000;
            handicap = 5;
        } else if (used_rank == -25) {
            simulations = 10000;
            handicap = 5;
        } else if (used_rank == -24) {
            simulations = 250;
            handicap = 4;
        } else if (used_rank == -23) {
            simulations = 500;
            handicap = 4;
        } else if (used_rank == -22) {
            simulations = 1000;
            handicap = 4;
        } else if (used_rank == -21) {
            simulations = 2500;
            handicap = 4;
        } else if (used_rank == -20) {
            simulations = 5000;
            handicap = 4;
        } else if (used_rank == -19) {
            simulations = 10000;
            handicap = 4;
        } else if (used_rank == -18) {
            simulations = 250;
            handicap = 3;
        } else if (used_rank == -17) {
            simulations = 500;
            handicap = 3;
        } else if (used_rank == -16) {
            simulations = 1000;
            handicap = 3;
        } else if (used_rank == -15) {
            simulations = 2500;
            handicap = 3;
        } else if (used_rank == -14) {
            simulations = 5000;
            handicap = 3;
        } else if (used_rank == -13) {
            simulations = 10000;
            handicap = 3;
        } else if (used_rank == -12) {
            simulations = 250;
            handicap = 2;
        } else if (used_rank == -11) {
            simulations = 500;
            handicap = 2;
        } else if (used_rank == -10) {
            simulations = 1000;
            handicap = 2;
        } else if (used_rank == -9) {
            simulations = 2500;
            handicap = 2;
        } else if (used_rank == -8) {
            simulations = 5000;
            handicap = 2;
        } else if (used_rank == -7) {
            simulations = 10000;
            handicap = 2;
        } else if (used_rank == -6) {
            simulations = 250;
            handicap = 0;
        } else if (used_rank == -5) {
            simulations = 500;
            handicap = 0;
        } else if (used_rank == -4) {
            simulations = 1000;
            handicap = 0;
        } else if (used_rank == -3) {
            simulations = 2500;
            handicap = 0;
        } else if (used_rank == -2) {
            simulations = 5000;
            handicap = 0;
        } else if (used_rank == -1) {
            simulations = 10000;
            handicap = 0;
        } else if (used_rank == 0) {
            simulations = 250;
            handicap = -2;
        } else if (used_rank == 1) {
            simulations = 500;
            handicap = -2;
        } else if (used_rank == 2) {
            simulations = 1000;
            handicap = -2;
        } else if (used_rank == 3) {
            simulations = 2500;
            handicap = -2;
        } else if (used_rank == 4) {
            simulations = 5000;
            handicap = -2;
        } else if (used_rank == 5) {
            simulations = 10000;
            handicap = -2;
        } else if (used_rank == 6) {
            simulations = 500;
            handicap = -3;
        } else if (used_rank == 7) {
            simulations = 1000;
            handicap = -3;
        } else if (used_rank == 8) {
            simulations = 2500;
            handicap = -3;
        } else if (used_rank == 9) {
            simulations = 5000;
            handicap = -3;
        } else if (used_rank == 10) {
            simulations = 10000;
            handicap = -3;
        } else if (used_rank == 11) {
            simulations = 2500;
            handicap = -4;
        } else if (used_rank == 12) {
            simulations = 5000;
            handicap = -4;
        } else if (used_rank == 13) {
            simulations = 10000;
            handicap = -4;
        }
    } else if (m_ratedSize == 19) {
        if (used_rank == -37) {
            simulations = 2500;
            handicap = 36;
        } else if (used_rank == -36) {
            simulations = 2500;
            handicap = 35;
        } else if (used_rank == -35) {
            simulations = 2500;
            handicap = 34;
        } else if (used_rank == -34) {
            simulations = 2500;
            handicap = 33;
        } else if (used_rank == -33) {
            simulations = 2500;
            handicap = 32;
        } else if (used_rank == -32) {
            simulations = 2500;
            handicap = 31;
        } else if (used_rank == -31) {
            simulations = 2500;
            handicap = 30;
        } else if (used_rank == -30) {
            simulations = 2500;
            handicap = 29;
        } else if (used_rank == -29) {
            simulations = 2500;
            handicap = 28;
        } else if (used_rank == -28) {
            simulations = 2500;
            handicap = 27;
        } else if (used_rank == -27) {
            simulations = 2500;
            handicap = 26;
        } else if (used_rank == -26) {
            simulations = 2500;
            handicap = 25;
        } else if (used_rank == -25) {
            simulations = 2500;
            handicap = 24;
        } else if (used_rank == -24) {
            simulations = 2500;
            handicap = 23;
        } else if (used_rank == -23) {
            simulations = 2500;
            handicap = 22;
        } else if (used_rank == -22) {
            simulations = 2500;
            handicap = 21;
        } else if (used_rank == -21) {
            simulations = 2500;
            handicap = 20;
        } else if (used_rank == -20) {
            simulations = 2500;
            handicap = 19;
        } else if (used_rank == -19) {
            simulations = 2500;
            handicap = 18;
        } else if (used_rank == -18) {
            simulations = 2500;
            handicap = 17;
        } else if (used_rank == -17) {
            simulations = 2500;
            handicap = 16;
        } else if (used_rank == -16) {
            simulations = 2500;
            handicap = 15;
        } else if (used_rank == -15) {
            simulations = 2500;
            handicap = 14;
        } else if (used_rank == -14) {
            simulations = 2500;
            handicap = 13;
        } else if (used_rank == -13) {
            simulations = 2500;
            handicap = 12;
        } else if (used_rank == -12) {
            simulations = 2500;
            handicap = 11;
        } else if (used_rank == -11) {
            simulations = 2500;
            handicap = 10;
        } else if (used_rank == -10) {
            simulations = 2500;
            handicap = 9;
        } else if (used_rank == -9) {
            simulations = 2500;
            handicap = 8;
        } else if (used_rank == -8) {                // 1 kyu
            simulations = 2500;
            handicap = 7;
        } else if (used_rank == -7) {                // 1 dan
            simulations = 2500;
            handicap = 6;
        } else if (used_rank == -6) {
            simulations = 2500;
            handicap = 5;
        } else if (used_rank == -5) {
            simulations = 2500;
            handicap = 4;
        } else if (used_rank == -4) {
            simulations = 2500;
            handicap = 3;
        } else if (used_rank == -3) {
            simulations = 2500;
            handicap = 2;
        } else if (used_rank == -2) {                // 6 dan
            simulations = 2500;
            handicap = 0;
        } else if (used_rank == -1) { // 1 kyu       // 7 dan
            simulations = 5000;
            handicap = 0;
        } else if (used_rank == 0) {  // 1 dan       // 1 pro
            simulations = 10000;
            handicap = 0;
        } else if (used_rank == 1) {
            simulations =  2500;
            handicap = -2;
        } else if (used_rank == 2) {
            simulations =  5000;
            handicap = -2;
        } else if (used_rank == 3) {
            simulations =  3750;
            handicap = -3;
        } else if (used_rank == 4) {
            simulations =  5000;
            handicap = -4;
        } else if (used_rank == 5) {
            simulations =  5000;
            handicap = -6;
        } else if (used_rank == 6) {
            simulations =  5000;
            handicap = -8;
        } else if (used_rank == 7) {
            simulations =  5000;
            handicap = -12;
        } else if (used_rank == 8) {
            simulations =  5000;
            handicap = -14;
        } else if (used_rank == 9) {
            simulations =  7500;
            handicap = -16;
        } else if (used_rank == 10) {
            simulations =  7500;
            handicap = -18;
        } else if (used_rank == 11) {
            simulations =  7500;
            handicap = -20;
        } else if (used_rank == 12) {
            simulations = 10000;
            handicap = -22;
        } else if (used_rank == 13) {
            simulations = 10000;
            handicap = -24;
        }
    }

    wxLogDebug("Handicap %d Simulations %d", handicap, simulations);

    {
        float komi = handicap ? 0.5f : 7.5f;
        m_State.init_game(m_ratedSize, komi);
        ::wxBeginBusyCursor();
        CalculateDialog calcdialog(this);
        calcdialog.Show();
        //::wxSafeYield();
        m_State.set_timecontrol(30 * 100, 0, 0, 0);
        m_State.place_free_handicap(abs(handicap));
        calcdialog.Hide();
        ::wxEndBusyCursor();
        // max 60 minutes per game
        m_State.set_timecontrol(2 * m_ratedSize * 60 * 100, 0, 0, 0);
        m_StateStack.clear();
        MCOwnerTable::clear();
        m_visitLimit = simulations;
        m_playerColor = (handicap >= 0 ? FastBoard::BLACK : FastBoard::WHITE);
        m_panelBoard->setPlayerColor(m_playerColor);
        m_panelBoard->setShowTerritory(false);
        m_ratedGame = true;
        setActiveMenus();
    }

    wxCommandEvent myevent(wxEVT_NEW_MOVE, GetId());
    myevent.SetEventObject(this);
    ::wxPostEvent(m_panelBoard->GetEventHandler(), myevent);
    broadcastCurrentMove();
}

void MainFrame::ratedGameEnd(bool won) {
    //wxString mess;
    wxString rankstr;
    
    if (m_ratedGame) {
        int rank;
        if (m_ratedSize == 9) {
            rank = wxConfig::Get()->Read(wxT("LastRank9"), (long)-30);
        } else if (m_ratedSize == 19) {
            rank = wxConfig::Get()->Read(wxT("LastRank19"), (long)-9);
        }
               
        if (won) {
            rank = rank + 1;
            rank = std::min(MAX_RANK, rank);
                                    
            //mess += wxT("Promoting from") + wxString(" ") + rankToString(rank-1) + wxString("\n");
            //mess += wxT("to") + wxString(" ") + rankToString(rank);
        } else {
            rank = rank - 1;
            rank = std::max(MIN_RANK, rank);
                                    
            //mess += wxT("Demoting from") + wxString(" ") + rankToString(rank+1) + wxString("\n");
            //mess += wxT("to") + wxString(" ") + rankToString(rank);
        }                   
        
//        ::wxMessageBox(mess, wxT("Rated game"), wxOK, this);
        
        if (m_ratedSize == 9) {
            wxConfig::Get()->Write(wxT("LastRank9"), rank);                        
        } else if (m_ratedSize == 19) {
            wxConfig::Get()->Write(wxT("LastRank19"), rank);                        
        }
                
        wxString mess = wxString(_("Your rank: "));
        mess += rankToString(rank);    
        m_statusBar->SetStatusText(mess, 1);
        
        // don't adjust rank twice
        m_ratedGame = false;
    }               
}

bool MainFrame::scoreGame(float & komi, float & handicap,
                          float & score, float & prekomi) {
    bool won;
    stopEngine();

    if (m_State.get_last_move() == FastBoard::RESIGN) {
        komi = m_State.get_komi();
        handicap = m_State.get_handicap();

        int size = m_State.board.get_boardsize() * m_State.board.get_boardsize();
        if (m_State.get_to_move() == FastBoard::WHITE) {
            score = -size;
        } else {
            score = size;
        }
        prekomi = score + komi + handicap;
    } else {
        komi = m_State.get_komi();
        score = m_State.final_score();
        handicap = m_State.get_handicap();
        prekomi = score + komi + handicap;
    }

    won = (score > 0.0f && m_playerColor == FastBoard::BLACK)
          || (score < 0.0f && m_playerColor == FastBoard::WHITE);

    m_panelBoard->doTerritory();
    m_panelBoard->setShowTerritory(true);

    return won;
}

bool MainFrame::scoreDialog(float komi, float handicap,
                            float score, float prekomi) {
    wxString mess;

    if (score > 0.0f) {
        if (m_State.get_last_move() == FastBoard::RESIGN) {
            mess.Printf(_("BLACK wins by resignation"));
        } else {
            if (handicap > 0.5f) {
                mess.Printf(_("BLACK wins by %.0f - %.1f (komi) - %0.f (handicap)\n= %.1f points"), prekomi, komi, handicap, score);        
            } else {
                mess.Printf(_("BLACK wins by %.0f - %.1f (komi)\n= %.1f points"), prekomi, komi, score);        
            }
        }
    } else {
        // avoid minus zero
        prekomi = prekomi - 0.001f;
        score = score - 0.001f;
        if (m_State.get_last_move() == FastBoard::RESIGN) {
            mess.Printf(_("WHITE wins by resignation"));
        } else {
            if (handicap > 0.5f) {
                mess.Printf(_("WHITE wins by %.0f + %.1f (komi) + %0.f (handicap)\n= %.1f points"), -prekomi, komi, handicap, -score);
            } else {
                mess.Printf(_("WHITE wins by %.0f + %.1f (komi)\n= %.1f points"), -prekomi, komi, -score);
            }
        }
    }

    wxString confidence("");
    if (m_State.board.get_boardsize() == 19) {
        float net_score = Network::get_Network()->get_value(&m_State,
                                                            Network::Ensemble::AVERAGE_ALL);
        net_score = (m_State.get_to_move() == FastBoard::BLACK) ?
                    net_score : (1.0f - net_score);
        if (m_State.get_last_move() != FastBoard::RESIGN) {
            if ((score > 0.0f && net_score < 0.5f)
                || (score < 0.0f && net_score > 0.5f)) {
                confidence = _("I am not sure I am scoring this correctly.");
            }
        }
    }

    ScoreDialog mydialog(this, mess, confidence);

    if (mydialog.ShowModal() == wxID_OK) {
        bool result = mydialog.Accepted();
        if (result) {
            return true;
        } else {
            return false;
        }
    }

    return true;
}

void MainFrame::doScore(wxCommandEvent& event) {
    float komi, score, prekomi, handicap;

    bool won = scoreGame(komi, handicap, score, prekomi);
    scoreDialog(komi, handicap, score, prekomi);
}

wxString MainFrame::rankToString(int rank) {
    wxString res;
    
    if (rank < 0) {
        res.Printf(_("%d kyu"), -rank);
    } else {
        if (rank < 7) {
            res.Printf(_("%d dan"), rank + 1);
        } else {
            res.Printf(_("%d pro"), rank - 6);
        }
    }
    
    return res;
}

void MainFrame::doPass(wxCommandEvent& event) {
    stopEngine();    

    m_State.play_pass();
    //::wxLogMessage("User passes");

    wxCommandEvent myevent(wxEVT_NEW_MOVE, GetId());
    myevent.SetEventObject(this);
    ::wxPostEvent(m_panelBoard->GetEventHandler(), myevent);
    broadcastCurrentMove();
}

void MainFrame::gameNoLongerCounts() {
    this->SetTitle(_("Leela") +
                   _(" - move " + wxString::Format(wxT("%i"), m_State.get_movenum() + 1)));
    if (m_ratedGame) {
        m_ratedGame = false;
    }
}

void MainFrame::doRealUndo(int count) {
    bool wasPondering = m_pondering;
    bool wasRunning = stopEngine();
    bool wasAnalyzing = wasRunning && !wasPondering;

    for (int i = 0; i < count; i++) {
        if (m_State.undo_move()) {
            wxLogDebug("Undoing one move");
        }
    }
    doPostMoveChange(wasAnalyzing);
}

void MainFrame::doRealForward(int count) {
    bool wasPondering = m_pondering;
    bool wasRunning = stopEngine();
    bool wasAnalyzing = wasRunning && !wasPondering;

    for (int i = 0; i < count; i++) {
        if (m_State.forward_move()) {
            wxLogDebug("Forward one move");
        }
    }
    doPostMoveChange(wasAnalyzing);
}

void MainFrame::doPostMoveChange(bool wasAnalyzing) {
    m_playerColor = m_State.get_to_move();
    MCOwnerTable::clear();
    m_panelBoard->setPlayerColor(m_playerColor);
    m_panelBoard->setShowTerritory(false);
    m_panelBoard->clearViz();

    this->SetTitle(_("Leela") +
                   _(" - move " + wxString::Format(wxT("%i"), m_State.get_movenum() + 1)));

    wxCommandEvent myevent(wxEVT_BOARD_UPDATE, GetId());
    myevent.SetEventObject(this);
    ::wxPostEvent(m_panelBoard->GetEventHandler(), myevent);
    broadcastCurrentMove();

    if (wasAnalyzing) doAnalyze(myevent /* dummy */);
}

void MainFrame::doBack10(wxCommandEvent& event) {
    doRealUndo(10);
}

void MainFrame::doForward10(wxCommandEvent& event) {
    doRealForward(10);
}

void MainFrame::doGoRules(wxCommandEvent& event) {
    ::wxLaunchDefaultBrowser("http://senseis.xmp.net/?RulesOfGoIntroductory");
}

void MainFrame::doHomePage(wxCommandEvent& event) {
   ::wxLaunchDefaultBrowser("https://sjeng.org/leela");
}

void MainFrame::doHelpAbout(wxCommandEvent& event) {
    AboutDialog myabout(this);
    
    myabout.ShowModal();    
}

void MainFrame::doOpenSGF(wxCommandEvent& event) {
    stopEngine(false);

    wxString caption = _("Choose a file");
    wxString wildcard = _("Go games (*.sgf)|*.sgf");
    wxFileDialog dialog(this, caption, wxEmptyString, wxEmptyString, wildcard,
                        wxFD_OPEN | wxFD_CHANGE_DIR | wxFD_FILE_MUST_EXIST);

    if (dialog.ShowModal() == wxID_OK) {
        wxString path = dialog.GetPath();

        wxLogDebug("Opening: " + path);

        std::unique_ptr<SGFTree> tree(new SGFTree);
        try {
            tree->load_from_file(path.ToStdString());
             wxLogDebug("Read %d moves", tree->count_mainline_moves());
            m_State = tree->follow_mainline_state();
        } catch (...) {
        }

        m_StateStack.clear();
        m_StateStack.push_back(m_State);
        m_playerColor = m_State.get_to_move();
        MCOwnerTable::clear();
        m_panelBoard->setPlayerColor(m_playerColor);
        m_panelBoard->setShowTerritory(false);
        m_panelBoard->clearViz();
        if (m_scoreHistogramWindow) {
            m_scoreHistogramWindow->ClearHistogram();
        }
        gameNoLongerCounts();
        setActiveMenus();

        //signal board change
        wxCommandEvent myevent(wxEVT_BOARD_UPDATE, GetId());
        myevent.SetEventObject(this);
        ::wxPostEvent(m_panelBoard->GetEventHandler(), myevent);
        broadcastCurrentMove();
    }
}

void MainFrame::doSaveSGF(wxCommandEvent& event) {
    stopEngine();

    std::string sgfgame = SGFTree::state_to_string(&m_State, !m_playerColor);

    wxString caption = _("Choose a file");
    wxString wildcard = _("Go games (*.sgf)|*.sgf");
    wxFileDialog dialog(this, caption, wxEmptyString, wxEmptyString, wildcard, 
                        wxFD_SAVE | wxFD_CHANGE_DIR | wxFD_OVERWRITE_PROMPT);

    if (dialog.ShowModal() == wxID_OK) {
        wxString path = dialog.GetPath();

        wxLogDebug("Saving: " + path);

        wxFileOutputStream file(path);

        if (file.IsOk()) {
            file.Write(sgfgame.c_str(), sgfgame.size());  
        }
    }
}

void MainFrame::doForceMove(wxCommandEvent& event) {
    gameNoLongerCounts();
    m_ponderedOnce = true;
    bool wasAnalyzing = m_analyzing;
    bool wasPondering = m_pondering;
    bool wasRunning = stopEngine();
    if (!wasRunning || wasAnalyzing || wasPondering) {
        m_analyzing = false;
        m_pondering = false;
        m_playerColor = !m_State.get_to_move();
        m_panelBoard->setPlayerColor(m_playerColor);
        startEngine();
    }
}

void MainFrame::doResign(wxCommandEvent& event) {
    if (m_State.get_to_move() == m_playerColor) {
        stopEngine();

        m_State.play_move(FastBoard::RESIGN);
        wxCommandEvent myevent(wxEVT_NEW_MOVE, GetId());
        myevent.SetEventObject(this);
        ::wxPostEvent(GetEventHandler(), myevent);
    }
}

void MainFrame::doAnalyze(wxCommandEvent& event) {
    gameNoLongerCounts();
    bool wasAnalyzing = m_analyzing && !m_pondering;
    bool wasRunning = stopEngine();
    m_ponderedOnce |= wasRunning;
    m_pondering = false;

    if (!wasAnalyzing || !wasRunning) {
        if (!wasAnalyzing) {
            m_StateStack.push_back(m_State);
            setActiveMenus();
        }
        m_analyzing = true;
        startEngine();
    } else if (wasAnalyzing) {
        m_analyzing = false;
    }
    m_panelBoard->unlockState();
    m_playerColor = m_State.get_to_move();
    m_panelBoard->setPlayerColor(m_playerColor);
}

void MainFrame::doAdjustClocks(wxCommandEvent& event) {
    ClockAdjustDialog mydialog(this);

    mydialog.setTimeControl(m_State.get_timecontrol());

    if (mydialog.ShowModal() == wxID_OK) {
        wxLogDebug("Adjust clocks clicked");

        m_State.set_timecontrol(mydialog.getTimeControl());
    }
}

void MainFrame::doKeyDown(wxKeyEvent& event) {
    auto keycode = event.GetKeyCode();
    if (keycode == WXK_LEFT) {
        doRealUndo();
    } else if (keycode == WXK_RIGHT) {
        doRealForward();
    } else if (keycode == WXK_TAB) {
        HandleAsNavigationKey(event);
    } else {
        event.Skip();
    }
}

void MainFrame::doShowHideAnalysisWindow(wxCommandEvent& event) {
    gameNoLongerCounts();
    if (!m_analysisWindow) {
        m_analysisWindow = new AnalysisWindow(this);
        m_analysisWindow->Show();
    } else {
        if (!m_analysisWindow->IsShown()) {
            m_analysisWindow->Show();
        } else {
            m_analysisWindow->Hide();
        }
    }
}

void MainFrame::doShowHideScoreHistogram( wxCommandEvent& event ) {
    if (!m_scoreHistogramWindow) {
        m_scoreHistogramWindow = new ScoreHistogram(this);
        m_scoreHistogramWindow->Show();
    } else {
        if (!m_scoreHistogramWindow->IsShown()) {
            m_scoreHistogramWindow->Show();
        } else {
            m_scoreHistogramWindow->Hide();
        }
    }
}

void MainFrame::doCloseChild( wxWindowDestroyEvent& event ) {
    if (event.GetWindow() == m_analysisWindow) {
        m_menuAnalyze->FindItem(ID_ANALYSISWINDOWTOGGLE)->Check(false);
        m_analysisWindow = nullptr;
    }
    if (event.GetWindow() == m_scoreHistogramWindow) {
        m_menuAnalyze->FindItem(ID_SCOREHISTOGRAMTOGGLE)->Check(false);
        m_scoreHistogramWindow = nullptr;
    }
}

void MainFrame::broadcastCurrentMove() {
    if (m_scoreHistogramWindow) {
        wxCommandEvent* cmd = new wxCommandEvent(wxEVT_SET_MOVENUM);
        cmd->SetInt(m_State.get_movenum());
        m_scoreHistogramWindow->GetEventHandler()->QueueEvent(cmd);
    }
}

void MainFrame::doMainLine(wxCommandEvent& event) {
    assert(!m_StateStack.empty());
    if (m_StateStack.empty()) return;
    m_State = m_StateStack.back();
    m_panelBoard->unlockState();
    m_playerColor = m_State.get_to_move();
    m_panelBoard->setPlayerColor(m_playerColor);
    gameNoLongerCounts();

    //signal board change
    wxCommandEvent myevent(wxEVT_BOARD_UPDATE, GetId());
    myevent.SetEventObject(this);
    ::wxPostEvent(m_panelBoard->GetEventHandler(), myevent);
    broadcastCurrentMove();
}

void MainFrame::doPushPosition( wxCommandEvent& event ) {
    m_StateStack.push_back(m_State);
    setActiveMenus();
}

void MainFrame::doPopPosition( wxCommandEvent& event ) {
    assert(!m_StateStack.empty());
    if (m_StateStack.empty()) return;
    doMainLine(event);
    m_StateStack.pop_back();
    gameNoLongerCounts();
    setActiveMenus();
}

void MainFrame::gotoMoveNum(wxCommandEvent& event) {
    int movenum = event.GetInt();

    int current_move = m_State.get_movenum();
    if (movenum > current_move) {
        doRealForward(movenum - current_move);
    } else if (movenum < current_move) {
        doRealUndo(current_move - movenum);
    }
}

void MainFrame::doEvalUpdate(wxCommandEvent& event) {
    if (m_scoreHistogramWindow) {
        m_scoreHistogramWindow->GetEventHandler()->AddPendingEvent(event);
    } else {
        // Need to free up the analysis data
        if (!event.GetClientData()) return;

        delete reinterpret_cast<std::tuple<int, float, float, float>*>(event.GetClientData());
    }
}
void MainFrame::doCopyClipboard(wxCommandEvent& event) {
    if (wxTheClipboard->Open()) {
        std::string sgfgame = SGFTree::state_to_string(&m_State, !m_playerColor);
        auto data = new wxTextDataObject(wxString(sgfgame));
        wxTheClipboard->SetData(data);
        wxTheClipboard->Flush();
        wxTheClipboard->Close();
    }
}

void MainFrame::doPasteClipboard(wxCommandEvent& event) {
    if (wxTheClipboard->Open()) {
        if (wxTheClipboard->IsSupported(wxDF_TEXT)) {
            wxTextDataObject data;
            wxTheClipboard->GetData(data);
            std::string sgfstring = data.GetText().ToStdString();
            std::istringstream strm(sgfstring);
            std::unique_ptr<SGFTree> sgftree(new SGFTree);
            auto games = SGFParser::chop_stream(strm);
            if (!games.empty()) {
                sgftree->load_from_string(games[0]);
                m_State = sgftree->follow_mainline_state();

                m_StateStack.clear();
                m_StateStack.push_back(m_State);
                m_playerColor = m_State.get_to_move();
                MCOwnerTable::clear();
                m_panelBoard->setPlayerColor(m_playerColor);
                m_panelBoard->setShowTerritory(false);
                m_panelBoard->clearViz();
                if (m_scoreHistogramWindow) {
                    m_scoreHistogramWindow->ClearHistogram();
                }
                gameNoLongerCounts();
                setActiveMenus();

                //signal board change
                wxCommandEvent myevent(wxEVT_BOARD_UPDATE, GetId());
                myevent.SetEventObject(this);
                ::wxPostEvent(m_panelBoard->GetEventHandler(), myevent);
                broadcastCurrentMove();
            }
        }
        wxTheClipboard->Close();
    }
}
