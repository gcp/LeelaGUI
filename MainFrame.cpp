#include "stdafx.h"
#include "GUI.h"
#include "MainFrame.h"

BEGIN_EVENT_TABLE(MainFrame, TMainFrame)    
END_EVENT_TABLE()

MainFrame::MainFrame(wxFrame *frame, const wxString& title)
          :TMainFrame(frame, wxID_ANY, title) {   

}

MainFrame::~MainFrame() {
}