#include "stdafx.h"
#include "GUI.h"
#include "MainFrame.h"

MainFrame::MainFrame(wxFrame *frame, const wxString& title)
          :TMainFrame(frame, wxID_ANY, title) {   
    delete wxLog::SetActiveTarget(new wxLogTextCtrl(m_logText));
    Center();  
}

MainFrame::~MainFrame() {
    delete wxLog::SetActiveTarget(new wxLogStderr(NULL));        
}

void MainFrame::doNewGame(wxCommandEvent & event) {
}

void MainFrame::doExit(wxCommandEvent & event) {
    Close();
}

void MainFrame::doPaint(wxPaintEvent& event) {    
    //wxPaintDC tmp(this);        
    event.Skip();           
}

void MainFrame::doActivate(wxActivateEvent& event) {                       
}

void MainFrame::doResize(wxSizeEvent& event) { 
    event.Skip();    
}

void MainFrame::doBoardResize(wxSizeEvent& event) {
    event.Skip();
}