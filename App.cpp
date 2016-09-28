#include "stdafx.h"
#include "App.h"
#include "MainFrame.h"

bool IsWindowsVistaOrHigher() {
    OSVERSIONINFO osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&osvi);
    return osvi.dwMajorVersion >= 6;
}

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    wxConfig * config = new wxConfig(wxT("Leela"), wxT("Sjeng.Org"));
    wxConfig::Set(config);

    bool dpiScale = wxConfig::Get()->Read(wxT("dpiscaleEnabled"), (long)0);
    if (!dpiScale) {
        if (IsWindowsVistaOrHigher()) {
            SetProcessDPIAware();
        }
    }

    MainFrame* frame = new MainFrame(NULL, _("Leela"));

    frame->Show();

    SetTopWindow(frame);

    return true;
}
