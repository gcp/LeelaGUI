#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "stdafx.h"
#include "GUI.h"
#include "FastBoard.h"
#include "GameState.h"
#include "EngineThread.h"

DECLARE_EVENT_TYPE(EVT_NEW_MOVE, wxID_ANY)
DECLARE_EVENT_TYPE(EVT_BOARD_UPDATE, wxID_ANY)
DECLARE_EVENT_TYPE(EVT_STATUS_UPDATE, wxID_ANY)

class MainFrame : public TMainFrame {
    public:
        MainFrame(wxFrame *frame, const wxString& title);
        ~MainFrame();
        void SetStatusBar(wxString mess, int pos);

    private:                                  	        
	virtual void doActivate(wxActivateEvent& event);
	virtual void doPaint(wxPaintEvent& event);		
	virtual void doNewMove(wxCommandEvent& event);
	virtual void doBoardUpdate(wxCommandEvent& event);
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
	virtual void doSoundToggle(wxCommandEvent& event);
	virtual void doForceMove(wxCommandEvent& event);
	virtual void doToggleTerritory(wxCommandEvent& event);
	virtual void doToggleMoyo(wxCommandEvent& event);
	virtual void doResignToggle(wxCommandEvent& event);
	virtual void doStatusUpdate(wxCommandEvent& event);
	virtual void doResign(wxCommandEvent& event);
	virtual void doAnalyze(wxCommandEvent& event);
	
	void startEngine();
	void stopEngine();
	// true = user accepts score
	bool scoreDialog(float komi, float score, float prekomi);
	void scoreGame(bool & won, float & komi, float & score, float & prescore);
	void ratedGameEnd(bool won);
	wxString rankToString(int rank);
	void updateStatusBar(char *str);	
	
	GameState m_State;
	int m_playerColor;
	int m_visitLimit;
	bool m_soundEnabled;
	bool m_resignEnabled;
	bool m_ratedGame;		
	wxSemaphore m_engineRunning;
	TEngineThread * m_engineThread;
};

#endif