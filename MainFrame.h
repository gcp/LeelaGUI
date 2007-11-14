#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "stdafx.h"
#include "GUI.h"
#include "FastBoard.h"
#include "GameState.h"
#include "EngineThread.h"

DECLARE_EVENT_TYPE(EVT_NEW_MOVE, -1)

class MainFrame : public TMainFrame {
    public:
        MainFrame(wxFrame *frame, const wxString& title);
        ~MainFrame();

    private:                                  	        
	virtual void doActivate(wxActivateEvent& event);
	virtual void doPaint(wxPaintEvent& event);		
	virtual void doNewMove(wxCommandEvent& event);
	virtual void doExit(wxCommandEvent& event);
	virtual void doResize(wxSizeEvent& event);
	virtual void doBoardResize(wxSizeEvent& event);		
	virtual void doNewGame(wxCommandEvent& event);
	virtual void doScore(wxCommandEvent& event);
	virtual void doPass(wxCommandEvent& event);	
	virtual void doNewRatedGame(wxCommandEvent& event);
	virtual void doUndo(wxCommandEvent& event);
	virtual void doForward(wxCommandEvent& event);
	virtual void doGoRules(wxCommandEvent& event);
	virtual void doHelpAbout(wxCommandEvent& event);	
	virtual void doHomePage(wxCommandEvent& event);
	virtual void doOpenSGF(wxCommandEvent& event);
        virtual void doSaveSGF(wxCommandEvent& event);
        virtual void doBack10(wxCommandEvent& event);
	virtual void doForward10(wxCommandEvent& event);
	
	GameState m_State;
	int m_playerColor;
	wxSemaphore m_engineRunning;
	TEngineThread * m_engineThread;
};

#endif