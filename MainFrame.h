#include "stdafx.h"
#include "GUI.h"
#include "GameState.h"

class MainFrame : public TMainFrame
{
    public:
        MainFrame(wxFrame *frame, const wxString& title);
        ~MainFrame();

    private:                                  	        
	virtual void doActivate(wxActivateEvent& event);
	virtual void doPaint(wxPaintEvent& event);	
	virtual void doNewGame(wxCommandEvent& event);
	virtual void doExit(wxCommandEvent& event);
	virtual void doResize(wxSizeEvent& event);
	virtual void doBoardResize(wxSizeEvent& event);		
	
	GameState m_State;
};