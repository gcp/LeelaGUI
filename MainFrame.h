#include "stdafx.h"
#include "GUI.h"

class MainFrame : public TMainFrame
{
    public:
        MainFrame(wxFrame *frame, const wxString& title);
        ~MainFrame();

    private:                          
        DECLARE_EVENT_TABLE();	
};