#include "stdafx.h"
#include "App.h"
#include "MainFrame.h"

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{   
    MainFrame* frame = new MainFrame(NULL, wxT("Leela"));
    frame->Show();
    
    SetTopWindow(frame);

    return true;
}
