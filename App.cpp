#include "stdafx.h"
#include "App.h"
#include "MainFrame.h"

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{   
    wxConfig * config = new wxConfig(wxT("Leela"), wxT("Sjeng.Org"));    
    wxConfig::Set(config);

    MainFrame* frame = new MainFrame(NULL, wxT("Leela"));    
    frame->Show();
    
    SetTopWindow(frame);

    return true;
}
