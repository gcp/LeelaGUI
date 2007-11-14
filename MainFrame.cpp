#include "stdafx.h"
#include "GUI.h"
#include "MainFrame.h"
#include "TBoardPanel.h"
#include "Zobrist.h"
#include "Random.h"
#include "SGFTree.h"
#include "EngineThread.h"
#include "AboutDialog.h"
#include "NewGameDialog.h"
#include "NagDialog.h"

DEFINE_EVENT_TYPE(EVT_NEW_MOVE)

MainFrame::MainFrame(wxFrame *frame, const wxString& title)
          :TMainFrame(frame, wxID_ANY, title) {   
        
    delete wxLog::SetActiveTarget(new wxLogTextCtrl(m_logText)); 

    wxLog::SetTimestamp(NULL);            
    
    Connect(EVT_NEW_MOVE, wxCommandEventHandler(MainFrame::doNewMove));    
    
    std::auto_ptr<Random> rng(new Random(5489UL));
    Zobrist::init_zobrist(*rng);    
       
    m_playerColor = FastBoard::BLACK;
    m_State.init_game(9, 6.5f);
    m_State.set_timecontrol(3 * 60 * 100, 0, 0);
    m_panelBoard->setState(&m_State);
    m_panelBoard->setPlayerColor(m_playerColor);

    // allow one engine running
    m_engineRunning.Post();
    
    SetIcon(wxICON(aaaa));

    Center();          
}

MainFrame::~MainFrame() {
    if (m_engineRunning.WaitTimeout(2000) == wxSEMA_TIMEOUT) {
        m_engineThread->Kill();
    }

    delete wxLog::SetActiveTarget(new wxLogStderr(NULL));       
    m_panelBoard->setState(NULL); 
    
    Disconnect(EVT_NEW_MOVE, wxCommandEventHandler(MainFrame::doNewMove));
    
    Hide();
    
    NagDialog dialog(this);
    
    dialog.ShowModal();
}

void MainFrame::doExit(wxCommandEvent & event) {
    Close();
}

void MainFrame::doNewMove(wxCommandEvent & event) {
    ::wxLogDebug("New move arrived");
    if (m_State.get_to_move() != m_playerColor) {
        ::wxLogDebug("Computer to move");
        
        if (m_engineRunning.TryWait() != wxSEMA_BUSY) {                                
            m_engineThread = new TEngineThread(&m_State, &m_engineRunning, this);
            if (m_engineThread->Create(1024 * 1024) != wxTHREAD_NO_ERROR) {
                ::wxLogDebug("Error starting engine");
            } else {            
                m_engineThread->Run();
            }
        } else {
            ::wxLogDebug("Engine already running");
        }
    } else if (m_State.get_passes() == 2) {
        float score = m_State.final_score();
        
        if (score > 0.0f) {
            ::wxLogMessage("Final score: BLACK wins by %4.1f", score);
        } else {
            ::wxLogMessage("Final score: WHITE wins by %4.1f", -score);
        }     
    }
    Refresh();
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

void MainFrame::doNewGame(wxCommandEvent& event) {
    m_engineRunning.Wait();
    
    m_State.init_game(9, 6.5f);    
    m_State.set_timecontrol(3 * 60 * 100, 0, 0);
    
    ::wxLogMessage("New game with 3 minutes thinking time and komi 6.5");
    
    m_engineRunning.Post();
    
    m_panelBoard->Refresh();
}

void MainFrame::doScore(wxCommandEvent& event) {
    m_engineRunning.Wait();
    
    float score = m_State.final_score();
    
    if (score > 0.0f) {
        ::wxLogMessage("Final score: BLACK wins by %4.1f", score);
    } else {
        ::wxLogMessage("Final score: WHITE wins by %4.1f", -score);
    }        
    
    m_engineRunning.Post();
}

void MainFrame::doPass(wxCommandEvent& event) {
    m_engineRunning.Wait();

    m_State.play_pass();
    ::wxLogMessage("User passes");
    
    m_engineRunning.Post();
    
    wxCommandEvent myevent(EVT_NEW_MOVE, GetId());
    myevent.SetEventObject(this);                        
    ::wxPostEvent(m_panelBoard->GetEventHandler(), myevent);    
}

void MainFrame::doUndo(wxCommandEvent& event) {
    m_engineRunning.Wait();

    if (m_State.undo_move()) {
        ::wxLogDebug("Undoing one move");
    }
    m_playerColor = m_State.get_to_move();
    m_panelBoard->setPlayerColor(m_playerColor);        
    
    m_engineRunning.Post();
    
    wxCommandEvent myevent(EVT_NEW_MOVE, GetId());
    myevent.SetEventObject(this);                        
    ::wxPostEvent(m_panelBoard->GetEventHandler(), myevent);    
}

void MainFrame::doForward(wxCommandEvent& event) {
    m_engineRunning.Wait();

    if (m_State.forward_move()) {
        ::wxLogDebug("Forward one move");
    }
    m_playerColor = m_State.get_to_move();
    m_panelBoard->setPlayerColor(m_playerColor);
    
    m_engineRunning.Post();
        
    wxCommandEvent myevent(EVT_NEW_MOVE, GetId());
    myevent.SetEventObject(this);                        
    ::wxPostEvent(m_panelBoard->GetEventHandler(), myevent);
}

void MainFrame::doBack10(wxCommandEvent& event) {
    for (int i = 0; i < 10; i++) {
        doUndo(event);
    }
}

void MainFrame::doForward10(wxCommandEvent& event) {
    for (int i = 0; i < 10; i++) {
        doForward(event);
    }
}

void MainFrame::doGoRules(wxCommandEvent& event) {
    ::wxLaunchDefaultBrowser("http://senseis.xmp.net/?RulesOfGoIntroductory");
}

void MainFrame::doHomePage(wxCommandEvent& event) {
   ::wxLaunchDefaultBrowser("http://www.sjeng.org/leela");
}

void MainFrame::doHelpAbout(wxCommandEvent& event) {
    AboutDialog myabout(this);
    
    myabout.ShowModal();    
}

void MainFrame::doNewRatedGame(wxCommandEvent& event) {
    NewGameDialog mydialog(this);
    
    mydialog.ShowModal();
}

void MainFrame::doOpenSGF(wxCommandEvent& event) {    
    m_engineRunning.Wait();    
    
    wxString caption = wxT("Choose a file");
    wxString wildcard = wxT("Go games (*.sgf)|*.sgf");
    wxFileDialog dialog(this, caption, wxEmptyString, wxEmptyString, wildcard, 
                        wxFD_OPEN | wxFD_CHANGE_DIR | wxFD_FILE_MUST_EXIST);
    
    if (dialog.ShowModal() == wxID_OK) {
        wxString path = dialog.GetPath();
        
        ::wxLogDebug("Opening: " + path);
        
        std::auto_ptr<SGFTree> tree(new SGFTree);
        tree->load_from_file(path);  
        
        ::wxLogDebug("Read %d moves", tree->count_mainline_moves());
        
        m_State = tree->get_mainline();
        
        m_playerColor = m_State.get_to_move();
        m_panelBoard->setPlayerColor(m_playerColor);
        
        m_engineRunning.Post();
        
        //signal board change
        wxCommandEvent myevent(EVT_NEW_MOVE, GetId());
        myevent.SetEventObject(this);                        
        ::wxPostEvent(m_panelBoard->GetEventHandler(), myevent);
    } else {
        m_engineRunning.Post();
    }        
}

void MainFrame::doSaveSGF(wxCommandEvent& event) {
    m_engineRunning.Wait();
    
    std::string sgfgame = SGFTree::state_to_string(&m_State, !m_playerColor);
    
    wxString caption = wxT("Choose a file");
    wxString wildcard = wxT("Go games (*.sgf)|*.sgf");
    wxFileDialog dialog(this, caption, wxEmptyString, wxEmptyString, wildcard, 
                        wxFD_SAVE | wxFD_CHANGE_DIR | wxFD_OVERWRITE_PROMPT);
                        
    if (dialog.ShowModal() == wxID_OK) {
        wxString path = dialog.GetPath();
        
        ::wxLogDebug("Saving: " + path);
                
        wxFileOutputStream file(path);
        
        if (file.IsOk()) {
            file.Write(sgfgame.c_str(), sgfgame.size());  
        }        
    }        
    
    m_engineRunning.Post();
}
