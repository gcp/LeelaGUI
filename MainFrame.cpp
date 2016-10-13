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
#include "GTP.h"
#include "SMP.h"
#include "EngineThread.h"
#include "AboutDialog.h"
#include "NewGameDialog.h"
#include "ClockAdjustDialog.h"
#include "RatedSizeDialog.h"
#include "CalculateDialog.h"
#include "AnalysisWindow.h"
#include "MCOTable.h"

DEFINE_EVENT_TYPE(EVT_NEW_MOVE)
DEFINE_EVENT_TYPE(EVT_BOARD_UPDATE)
DEFINE_EVENT_TYPE(EVT_STATUS_UPDATE)

MainFrame::MainFrame(wxFrame *frame, const wxString& title)
          :TMainFrame(frame, wxID_ANY, title) {

    delete wxLog::SetActiveTarget(NULL);

    wxLog::SetTimestamp("");

    Connect(EVT_NEW_MOVE, wxCommandEventHandler(MainFrame::doNewMove));
    Connect(EVT_BOARD_UPDATE, wxCommandEventHandler(MainFrame::doBoardUpdate));
    Connect(EVT_STATUS_UPDATE, wxCommandEventHandler(MainFrame::doStatusUpdate));
    Connect(wxEVT_DESTROY, wxWindowDestroyEventHandler(MainFrame::doCloseChild));
    // Forward mainline updates to the board panel
    Bind(wxEVT_DISPLAY_MAINLINE, [=](wxCommandEvent& event) {
        m_panelBoard->GetEventHandler()->AddPendingEvent(event);
    });

    cfg_allow_pondering = true;
    cfg_num_threads = std::min(SMP::get_num_cpus(), MAX_CPUS);
    cfg_enable_nets = true;
    cfg_max_playouts = INT_MAX;
    GTP::setup_default_parameters();

    std::auto_ptr<Random> rng(new Random(5489UL));
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

    m_State.init_game(m_ratedSize, 7.5f);
    m_State.set_timecontrol(2 * m_ratedSize * 60 * 100, 0, 0, 0);
    m_panelBoard->setState(&m_State);
    m_panelBoard->setPlayerColor(m_playerColor);

    m_menuAnalyze->FindItem(ID_ANALYSISWINDOWTOGGLE)->Check(false);
    setActiveMenus();

    // set global message area
    Utils::setGUIQueue(this->GetEventHandler(), EVT_STATUS_UPDATE);

    SetIcon(wxICON(aaaa));

    SetSize(530, 640);
    Center();

    wxCommandEvent evt;
    doNewRatedGame(evt);
}

MainFrame::~MainFrame() {
    stopEngine();

    delete wxLog::SetActiveTarget(new wxLogStderr(NULL));
    m_panelBoard->setState(NULL);

    Disconnect(EVT_NEW_MOVE, wxCommandEventHandler(MainFrame::doNewMove));
    Disconnect(EVT_BOARD_UPDATE, wxCommandEventHandler(MainFrame::doBoardUpdate));
    Disconnect(EVT_STATUS_UPDATE, wxCommandEventHandler(MainFrame::doStatusUpdate));
    Disconnect(wxEVT_DESTROY, wxWindowDestroyEventHandler(MainFrame::doCloseChild));

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
        if (!m_pondering) {
            m_engineThread.reset(new TEngineThread(&m_State, this));
        } else {
            m_ponderState = m_State;
            m_engineThread.reset(new TEngineThread(&m_ponderState, this));
        }
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

bool MainFrame::stopEngine() {
    if (!m_engineThread) return false;
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
            wxSound tock("IDW_TOCK", true);
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
        bool won;
        scoreGame(won, komi, handicap, score, prekomi);
        bool accepts = scoreDialog(komi, score, prekomi, handicap);
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

    // signal update of visible board
    wxCommandEvent myevent(EVT_BOARD_UPDATE, GetId());
    myevent.SetEventObject(this);
    ::wxPostEvent(m_panelBoard->GetEventHandler(), myevent);
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

    if (wasAnalyzing) doAnalyze(wxCommandEvent());
}

void MainFrame::doNewGame(wxCommandEvent& event) {
    stopEngine();

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
        m_State.set_timecontrol(mydialog.getTimeControl() * 60 * 100, 0, 0, 0);
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

        wxCommandEvent myevent(EVT_NEW_MOVE, GetId());
        myevent.SetEventObject(this);
        ::wxPostEvent(m_panelBoard->GetEventHandler(), myevent);
    }
}

void MainFrame::setActiveMenus() {
    int boardsize = m_State.board.get_boardsize();
    if (boardsize != 19) {
        m_menuTools->FindItem(ID_MOVE_PROBABLITIES)->Enable(false);
    } else {
        m_menuTools->FindItem(ID_MOVE_PROBABLITIES)->Enable(true);
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
    stopEngine();

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
        m_analysisWindow->Hide();
    }

    int used_rank = rank;
    int handicap;
    int simulations;

    // Correct for neural network enabled
    if (m_ratedSize == 19) {
        if (m_netsEnabled) {
            // Estimate it as being worth 6 stones
            used_rank = rank - 6;
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
        if (used_rank == -36) {
            simulations = 5000;
            handicap = 33;
        } else if (used_rank == -35) {
            simulations = 5000;
            handicap = 32;
        } else if (used_rank == -34) {
            simulations = 5000;
            handicap = 31;
        } else if (used_rank == -33) {
            simulations = 5000;
            handicap = 30;
        } else if (used_rank == -32) {
            simulations = 5000;
            handicap = 29;
        } else if (used_rank == -31) {
            simulations = 5000;
            handicap = 28;
        } else if (used_rank == -30) {
            simulations = 5000;
            handicap = 27;
        } else if (used_rank == -29) {
            simulations = 5000;
            handicap = 27;
        } else if (used_rank == -28) {
            simulations = 5000;
            handicap = 26;
        } else if (used_rank == -27) {
            simulations = 5000;
            handicap = 25;
        } else if (used_rank == -26) {
            simulations = 5000;
            handicap = 24;
        } else if (used_rank == -25) {
            simulations = 5000;
            handicap = 23;
        } else if (used_rank == -24) {
            simulations = 5000;
            handicap = 22;
        } else if (used_rank == -23) {
            simulations = 5000;
            handicap = 21;
        } else if (used_rank == -22) {
            simulations = 5000;
            handicap = 20;
        } else if (used_rank == -21) {
            simulations = 5000;
            handicap = 19;
        } else if (used_rank == -20) {
            simulations = 5000;
            handicap = 18;
        } else if (used_rank == -19) {
            simulations = 5000;
            handicap = 17;
        } else if (used_rank == -18) {
            simulations = 5000;
            handicap = 16;
        } else if (used_rank == -17) {
            simulations = 5000;
            handicap = 15;
        } else if (used_rank == -16) {
            simulations = 5000;
            handicap = 14;
        } else if (used_rank == -15) {
            simulations = 5000;
            handicap = 13;
        } else if (used_rank == -14) {
            simulations = 5000;
            handicap = 12;
        } else if (used_rank == -13) {
            simulations = 5000;
            handicap = 11;
        } else if (used_rank == -12) {
            simulations = 5000;
            handicap = 10;
        } else if (used_rank == -11) {
            simulations = 5000;
            handicap = 9;
        } else if (used_rank == -10) {
            simulations = 5000;
            handicap = 8;
        } else if (used_rank == -9) {
            simulations = 5000;
            handicap = 7;
        } else if (used_rank == -8) {
            simulations = 5000;
            handicap = 6;
        } else if (used_rank == -7) {
            simulations = 5000;
            handicap = 5;
        } else if (used_rank == -6) {
            simulations = 5000;
            handicap = 4;
        } else if (used_rank == -5) {
            simulations = 5000;
            handicap = 3;
        } else if (used_rank == -4) {
            simulations = 5000;
            handicap = 2;
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
            simulations = 20000;
            handicap = 0;
        } else if (used_rank == 1) {
            simulations =  5000;
            handicap = -2;
        } else if (used_rank == 2) {
            simulations = 10000;
            handicap = -2;
        } else if (used_rank == 3) {
            simulations =  7500;
            handicap = -3;
        } else if (used_rank == 4) {
            simulations = 10000;
            handicap = -4;
        } else if (used_rank == 5) {
            simulations = 10000;
            handicap = -6;
        } else if (used_rank == 6) {
            simulations = 10000;
            handicap = -8;
        } else if (used_rank == 7) {
            simulations = 10000;
            handicap = -12;
        } else if (used_rank == 8) {
            simulations = 10000;
            handicap = -14;
        } else if (used_rank == 9) {
            simulations = 15000;
            handicap = -16;
        } else if (used_rank == 10) {
            simulations = 15000;
            handicap = -18;
        } else if (used_rank == 11) {
            simulations = 15000;
            handicap = -20;
        } else if (used_rank == 12) {
            simulations = 20000;
            handicap = -22;
        } else if (used_rank == 13) {
            simulations = 20000;
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
        m_visitLimit = simulations;
        m_playerColor = (handicap >= 0 ? FastBoard::BLACK : FastBoard::WHITE);
        m_panelBoard->setPlayerColor(m_playerColor);
        m_panelBoard->setShowTerritory(false);
        m_ratedGame = true;
        setActiveMenus();
    }

    wxCommandEvent myevent(EVT_NEW_MOVE, GetId());
    myevent.SetEventObject(this);
    ::wxPostEvent(m_panelBoard->GetEventHandler(), myevent);
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
            rank = std::min(13, rank);
                                    
            //mess += wxT("Promoting from") + wxString(" ") + rankToString(rank-1) + wxString("\n");
            //mess += wxT("to") + wxString(" ") + rankToString(rank);
        } else {
            rank = rank - 1;
            rank = std::max(-30, rank);
                                    
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

void MainFrame::scoreGame(bool & won, float & komi, float & handicap, 
                          float & score, float & prekomi) {
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
}

bool MainFrame::scoreDialog(float komi, float score, float prekomi, float handicap) {
    wxString mess;
    
    if (score > 0.0f) {        
        if (m_State.get_last_move() == FastBoard::RESIGN) {
            mess.Printf(_("BLACK wins by resignation"));
        } else {
            if (handicap > 0.5f) {
                mess.Printf(_("Final score:\nBLACK wins by %.0f - %.1f (komi) - %0.f (handicap)\n= %.1f points"), prekomi, komi, handicap, score);        
            } else {
                mess.Printf(_("Final score:\nBLACK wins by %.0f - %.1f (komi)\n= %.1f points"), prekomi, komi, score);        
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
                mess.Printf(_("Final score:\nWHITE wins by %.0f + %.1f (komi) + %0.f (handicap)\n= %.1f points"), -prekomi, komi, handicap, -score);
            } else {
                mess.Printf(_("Final score:\nWHITE wins by %.0f + %.1f (komi)\n= %.1f points"), -prekomi, komi, -score);
            }
        }            
    }   
    
    int result = ::wxMessageBox(mess, _("Game score"), wxOK | wxCANCEL, this);            
    
    if (result == wxOK) {
        return true;
    } else {
        return false;
    }
}

void MainFrame::doScore(wxCommandEvent& event) {   
    float komi, score, prekomi, handicap;
    bool won;
    
    scoreGame(won, komi, handicap, score, prekomi);
    scoreDialog(komi, score, prekomi, handicap);       
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

    wxCommandEvent myevent(EVT_NEW_MOVE, GetId());
    myevent.SetEventObject(this);
    ::wxPostEvent(m_panelBoard->GetEventHandler(), myevent);
}

void MainFrame::gameNoLongerCounts() {
    m_ratedGame = false;
    this->SetTitle(_("Leela"));
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
    m_playerColor = m_State.get_to_move();
    m_panelBoard->setPlayerColor(m_playerColor);
    m_panelBoard->setShowTerritory(false);

    gameNoLongerCounts();

    wxCommandEvent myevent(EVT_BOARD_UPDATE, GetId());
    myevent.SetEventObject(this);
    ::wxPostEvent(m_panelBoard->GetEventHandler(), myevent);

    if (wasAnalyzing) doAnalyze(myevent /* dummy */);
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
    m_playerColor = m_State.get_to_move();
    m_panelBoard->setPlayerColor(m_playerColor);
    m_panelBoard->setShowTerritory(false);

    wxCommandEvent myevent(EVT_BOARD_UPDATE, GetId());
    myevent.SetEventObject(this);
    ::wxPostEvent(m_panelBoard->GetEventHandler(), myevent);

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
    stopEngine();

    wxString caption = _("Choose a file");
    wxString wildcard = _("Go games (*.sgf)|*.sgf");
    wxFileDialog dialog(this, caption, wxEmptyString, wxEmptyString, wildcard,
                        wxFD_OPEN | wxFD_CHANGE_DIR | wxFD_FILE_MUST_EXIST);

    if (dialog.ShowModal() == wxID_OK) {
        wxString path = dialog.GetPath();

        wxLogDebug("Opening: " + path);

        std::auto_ptr<SGFTree> tree(new SGFTree);
        try {
            tree->load_from_file(path.ToStdString());
             wxLogDebug("Read %d moves", tree->count_mainline_moves());
            m_State = tree->follow_mainline_state();
        } catch (...) {
        }

        m_playerColor = m_State.get_to_move();
        m_panelBoard->setPlayerColor(m_playerColor);
        m_panelBoard->setShowTerritory(false);

        //signal board change
        wxCommandEvent myevent(EVT_BOARD_UPDATE, GetId());
        myevent.SetEventObject(this);
        ::wxPostEvent(m_panelBoard->GetEventHandler(), myevent);
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
        wxCommandEvent myevent(EVT_NEW_MOVE, GetId());
        myevent.SetEventObject(this);
        ::wxPostEvent(GetEventHandler(), myevent);
    }
}

void MainFrame::doAnalyze(wxCommandEvent& event) {
    gameNoLongerCounts();
    bool wasAnalyzing = m_analyzing && !m_pondering;
    bool wasGameMove = !m_analyzing && !m_pondering;
    bool wasRunning = stopEngine();
    m_ponderedOnce |= wasRunning;
    m_pondering = false;

    //if (wasGameMove && wasRunning) {
    //    wxQueueEvent(GetEventHandler(), new wxCommandEvent(EVT_NEW_MOVE));
    //}
    if (!wasAnalyzing || !wasRunning) {
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

    mydialog.setTimeControl(*(m_State.get_timecontrol()));

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

void MainFrame::doCloseChild( wxWindowDestroyEvent& event ) {
    if (event.GetWindow() == m_analysisWindow) {
        m_menuAnalyze->FindItem(ID_ANALYSISWINDOWTOGGLE)->Check(false);
        m_analysisWindow = nullptr;
    }
}