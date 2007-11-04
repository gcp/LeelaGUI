#include "stdafx.h"
#include "GUI.h"
#include "MainFrame.h"
#include "TBoardPanel.h"
#include "Zobrist.h"
#include "Random.h"
#include "EngineThread.h"

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
    m_panelBoard->setState(&m_State);
    m_panelBoard->setPlayerColor(m_playerColor);

    // allow one engine running
    m_engineRunning.Post();

    Center();          
}

MainFrame::~MainFrame() {
    delete wxLog::SetActiveTarget(new wxLogStderr(NULL));       
    m_panelBoard->setState(NULL); 
    
    Disconnect(EVT_NEW_MOVE, wxCommandEventHandler(MainFrame::doNewMove));
}

void MainFrame::doNewGame(wxCommandEvent & event) {
    m_State.init_game(9, 6.5f);    
    m_panelBoard->Refresh();
}

void MainFrame::doExit(wxCommandEvent & event) {
    Close();
}

void MainFrame::doNewMove(wxCommandEvent & event) {
    ::wxLogDebug("New move arrived");
    if (m_State.get_to_move() != m_playerColor) {
        ::wxLogDebug("Computer to move");
        
        if (m_engineRunning.TryWait() != wxSEMA_BUSY) {                                
            TEngineThread * mythread = new TEngineThread(&m_State, &m_engineRunning, this);
            if (mythread->Create(1024 * 1024) != wxTHREAD_NO_ERROR) {
                ::wxLogDebug("Error starting engine");
            } else {            
                mythread->Run();
            }
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
