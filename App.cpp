#include "stdafx.h"
#include "App.h"
#include "MainFrame.h"
#ifndef WIN32
#include "images.h"
#endif

#ifdef WIN32
bool IsWindowsVistaOrHigher() {
    OSVERSIONINFO osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&osvi);
    return osvi.dwMajorVersion >= 6;
}

typedef BOOL (WINAPI *SetProcDPICall)(void);
#endif

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    wxImage::AddHandler(new wxPNGHandler());

    wxConfig * config = new wxConfig(wxT("Leela"), wxT("Sjeng.Org"));
    wxConfig::Set(config);

#ifdef WIN32
    bool dpiScale = wxConfig::Get()->Read(wxT("dpiscaleEnabled"), (long)0);
    if (!dpiScale) {
        if (IsWindowsVistaOrHigher()) {
            HINSTANCE dllHandle = LoadLibrary(wxT("user32.dll"));
            if (dllHandle) {
                SetProcDPICall procDPI = (SetProcDPICall)GetProcAddress(
                    dllHandle, "SetProcessDPIAware");
                if (procDPI) {
                    procDPI();
                }
                FreeLibrary(dllHandle);
            }
        }
    }
#endif

    MainFrame* frame = new MainFrame(NULL, _("Leela"));

    frame->Show();

#ifdef WIN32
    SetTopWindow(frame);
#endif

    return true;
}
