#include "stdafx.h"
#include "GUI.h"
#include "MainFrame.h"
#include "TBoardPanel.h"
#include "Zobrist.h"
#include "Random.h"

MainFrame::MainFrame(wxFrame *frame, const wxString& title)
          :TMainFrame(frame, wxID_ANY, title) {   
    delete wxLog::SetActiveTarget(new wxLogTextCtrl(m_logText)); 
    
    std::auto_ptr<Random> rng(new Random(5489UL));          
    Zobrist::init_zobrist(*rng);    
       
    m_State.init_game(9, 6.5f);
    m_panelBoard->setState(&m_State);
    Center();  
}

MainFrame::~MainFrame() {
    delete wxLog::SetActiveTarget(new wxLogStderr(NULL));       
    m_panelBoard->setState(NULL); 
}

void MainFrame::doNewGame(wxCommandEvent & event) {
    m_State.init_game(9, 6.5f);
    m_panelBoard->Refresh();
}

void MainFrame::doExit(wxCommandEvent & event) {
    Close();
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