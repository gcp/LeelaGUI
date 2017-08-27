#include "stdafx.h"
#include "App.h"
#include "MainFrame.h"

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

    if (argc > 1) {
        long movenum = 999;
        if (argc > 2) {
            wxString moveNumString(argv[2]);
            moveNumString.ToLong(&movenum);
        }
        wxString sgfString(argv[1]);
        frame->loadSGF(sgfString, movenum);
    } else {
        wxCommandEvent evt;
        frame->doNewRatedGame(evt);
    }

    return true;
}
