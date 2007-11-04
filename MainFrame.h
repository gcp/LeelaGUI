#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "stdafx.h"
#include "GUI.h"
#include "FastBoard.h"
#include "GameState.h"

DECLARE_EVENT_TYPE(EVT_NEW_MOVE, -1)

class MainFrame : public TMainFrame {
    public:
        MainFrame(wxFrame *frame, const wxString& title);
        ~MainFrame();

    private:                                  	        
	virtual void doActivate(wxActivateEvent& event);
	virtual void doPaint(wxPaintEvent& event);	
	virtual void doNewGame(wxCommandEvent& event);
	virtual void doNewMove(wxCommandEvent& event);
	virtual void doExit(wxCommandEvent& event);
	virtual void doResize(wxSizeEvent& event);
	virtual void doBoardResize(wxSizeEvent& event);		
	
	GameState m_State;
	FastBoard::square_t m_playerColor;
	wxSemaphore m_engineRunning;
};

#endif