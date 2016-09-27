///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUI_H__
#define __GUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
class TBoardPanel;

#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/statusbr.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/toolbar.h>
#include <wx/frame.h>
#include <wx/radiobox.h>
#include <wx/spinctrl.h>
#include <wx/stattext.h>
#include <wx/statbox.h>
#include <wx/checkbox.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/hyperlink.h>
#include <wx/grid.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class TMainFrame
///////////////////////////////////////////////////////////////////////////////
class TMainFrame : public wxFrame 
{
	DECLARE_EVENT_TABLE()
	private:
		
		// Private event handlers
		void _wxFB_doActivate( wxActivateEvent& event ){ doActivate( event ); }
		void _wxFB_doClose( wxCloseEvent& event ){ doClose( event ); }
		void _wxFB_doKeyDown( wxKeyEvent& event ){ doKeyDown( event ); }
		void _wxFB_doPaint( wxPaintEvent& event ){ doPaint( event ); }
		void _wxFB_doResize( wxSizeEvent& event ){ doResize( event ); }
		void _wxFB_doNewGame( wxCommandEvent& event ){ doNewGame( event ); }
		void _wxFB_doNewRatedGame( wxCommandEvent& event ){ doNewRatedGame( event ); }
		void _wxFB_doSetRatedSize( wxCommandEvent& event ){ doSetRatedSize( event ); }
		void _wxFB_doOpenSGF( wxCommandEvent& event ){ doOpenSGF( event ); }
		void _wxFB_doSaveSGF( wxCommandEvent& event ){ doSaveSGF( event ); }
		void _wxFB_doExit( wxCommandEvent& event ){ doExit( event ); }
		void _wxFB_doUndo( wxCommandEvent& event ){ doUndo( event ); }
		void _wxFB_doForward( wxCommandEvent& event ){ doForward( event ); }
		void _wxFB_doBack10( wxCommandEvent& event ){ doBack10( event ); }
		void _wxFB_doForward10( wxCommandEvent& event ){ doForward10( event ); }
		void _wxFB_doForceMove( wxCommandEvent& event ){ doForceMove( event ); }
		void _wxFB_doResign( wxCommandEvent& event ){ doResign( event ); }
		void _wxFB_doScore( wxCommandEvent& event ){ doScore( event ); }
		void _wxFB_doAnalyze( wxCommandEvent& event ){ doAnalyze( event ); }
		void _wxFB_doShowHideAnalysisWindow( wxCommandEvent& event ){ doShowHideAnalysisWindow( event ); }
		void _wxFB_doToggleTerritory( wxCommandEvent& event ){ doToggleTerritory( event ); }
		void _wxFB_doToggleMoyo( wxCommandEvent& event ){ doToggleMoyo( event ); }
		void _wxFB_doNetToggle( wxCommandEvent& event ){ doNetToggle( event ); }
		void _wxFB_doPassToggle( wxCommandEvent& event ){ doPassToggle( event ); }
		void _wxFB_doResignToggle( wxCommandEvent& event ){ doResignToggle( event ); }
		void _wxFB_doPonderToggle( wxCommandEvent& event ){ doPonderToggle( event ); }
		void _wxFB_doSoundToggle( wxCommandEvent& event ){ doSoundToggle( event ); }
		void _wxFB_doAdjustClocks( wxCommandEvent& event ){ doAdjustClocks( event ); }
		void _wxFB_doGoRules( wxCommandEvent& event ){ doGoRules( event ); }
		void _wxFB_doHomePage( wxCommandEvent& event ){ doHomePage( event ); }
		void _wxFB_doHelpAbout( wxCommandEvent& event ){ doHelpAbout( event ); }
		
	
	protected:
		enum
		{
			ID_DEFAULT = wxID_ANY, // Default
			ID_MAINFRAME = 1000,
			ID_BOARDPANEL,
			ID_NEWGAME,
			ID_NEWRATED,
			ID_RATEDSIZE,
			ID_OPEN,
			ID_SAVE,
			ID_EXIT,
			ID_UNDO,
			ID_REDO,
			ID_BACK10,
			ID_FWD10,
			ID_FORCE,
			ID_RESIGN,
			ID_SCORE,
			ID_ANALYZE,
			ID_ANALYSISWINDOWTOGGLE,
			ID_SHOWTERRITORY,
			ID_SHOWMOYO,
			ID_NETWORKTOGGLE,
			ID_PASSTOGGLE,
			ID_RESIGNTOGGLE,
			ID_PONDERTOGGLE,
			ID_SOUNDSWITCH,
			ID_ADJUSTCLOCKS,
			ID_HELPRULES,
			ID_HOMEPAGE,
			ID_HELPABOUT,
			ID_PASS
		};
		
		TBoardPanel* m_panelBoard;
		wxStatusBar* m_statusBar;
		wxMenuBar* m_menubar1;
		wxMenu* m_menu1;
		wxMenu* m_menu2;
		wxMenu* m_menuAnalyze;
		wxMenu* m_menuSettings;
		wxMenu* m_menu3;
		wxToolBar* m_toolBar1;
		wxToolBarToolBase* m_tool1; 
		wxToolBarToolBase* m_tool12; 
		wxToolBarToolBase* m_tool4; 
		wxToolBarToolBase* m_tool5; 
		wxToolBarToolBase* m_tool10; 
		wxToolBarToolBase* m_tool13; 
		wxToolBarToolBase* m_tool15; 
		wxToolBarToolBase* m_tool9; 
		wxToolBarToolBase* m_toolForce; 
		wxToolBarToolBase* m_toolAnalyze; 
		wxToolBarToolBase* m_tool2; 
		wxToolBarToolBase* m_tool3; 
		wxToolBarToolBase* m_tool131; 
		wxToolBarToolBase* m_tool11; 
		
		// Virtual event handlers, overide them in your derived class
		virtual void doActivate( wxActivateEvent& event ) { event.Skip(); }
		virtual void doClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void doKeyDown( wxKeyEvent& event ) { event.Skip(); }
		virtual void doPaint( wxPaintEvent& event ) { event.Skip(); }
		virtual void doResize( wxSizeEvent& event ) { event.Skip(); }
		virtual void doNewGame( wxCommandEvent& event ) { event.Skip(); }
		virtual void doNewRatedGame( wxCommandEvent& event ) { event.Skip(); }
		virtual void doSetRatedSize( wxCommandEvent& event ) { event.Skip(); }
		virtual void doOpenSGF( wxCommandEvent& event ) { event.Skip(); }
		virtual void doSaveSGF( wxCommandEvent& event ) { event.Skip(); }
		virtual void doExit( wxCommandEvent& event ) { event.Skip(); }
		virtual void doUndo( wxCommandEvent& event ) { event.Skip(); }
		virtual void doForward( wxCommandEvent& event ) { event.Skip(); }
		virtual void doBack10( wxCommandEvent& event ) { event.Skip(); }
		virtual void doForward10( wxCommandEvent& event ) { event.Skip(); }
		virtual void doForceMove( wxCommandEvent& event ) { event.Skip(); }
		virtual void doResign( wxCommandEvent& event ) { event.Skip(); }
		virtual void doScore( wxCommandEvent& event ) { event.Skip(); }
		virtual void doAnalyze( wxCommandEvent& event ) { event.Skip(); }
		virtual void doShowHideAnalysisWindow( wxCommandEvent& event ) { event.Skip(); }
		virtual void doToggleTerritory( wxCommandEvent& event ) { event.Skip(); }
		virtual void doToggleMoyo( wxCommandEvent& event ) { event.Skip(); }
		virtual void doNetToggle( wxCommandEvent& event ) { event.Skip(); }
		virtual void doPassToggle( wxCommandEvent& event ) { event.Skip(); }
		virtual void doResignToggle( wxCommandEvent& event ) { event.Skip(); }
		virtual void doPonderToggle( wxCommandEvent& event ) { event.Skip(); }
		virtual void doSoundToggle( wxCommandEvent& event ) { event.Skip(); }
		virtual void doAdjustClocks( wxCommandEvent& event ) { event.Skip(); }
		virtual void doGoRules( wxCommandEvent& event ) { event.Skip(); }
		virtual void doHomePage( wxCommandEvent& event ) { event.Skip(); }
		virtual void doHelpAbout( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		TMainFrame( wxWindow* parent, wxWindowID id = ID_MAINFRAME, const wxString& title = _("Leela"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 520,630 ), long style = wxDEFAULT_FRAME_STYLE|wxWANTS_CHARS, const wxString& name = wxT("LeelaGUI") );
		
		~TMainFrame();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class TNewGameDialog
///////////////////////////////////////////////////////////////////////////////
class TNewGameDialog : public wxDialog 
{
	DECLARE_EVENT_TABLE()
	private:
		
		// Private event handlers
		void _wxFB_doInit( wxInitDialogEvent& event ){ doInit( event ); }
		void _wxFB_doHandicapUpdate( wxSpinEvent& event ){ doHandicapUpdate( event ); }
		void _wxFB_doCancel( wxCommandEvent& event ){ doCancel( event ); }
		void _wxFB_doOK( wxCommandEvent& event ){ doOK( event ); }
		
	
	protected:
		enum
		{
			ID_NEWGAME = 1000,
			ID_KOMISPIN,
			ID_HANDICAPSPIN
		};
		
		wxRadioBox* m_radioBoxBoardSize;
		wxSpinCtrl* m_spinCtrlKomi;
		wxStaticText* m_staticText2;
		wxSpinCtrl* m_spinCtrlHandicap;
		wxStaticText* m_staticText3;
		wxSpinCtrl* m_spinCtrlTime;
		wxStaticText* m_staticText13;
		wxRadioBox* m_radioBoxColor;
		wxRadioBox* m_radioBoxLevel;
		wxCheckBox* m_checkNeuralNet;
		wxStdDialogButtonSizer* m_sdbSizer1;
		wxButton* m_sdbSizer1OK;
		wxButton* m_sdbSizer1Cancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void doInit( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void doHandicapUpdate( wxSpinEvent& event ) { event.Skip(); }
		virtual void doCancel( wxCommandEvent& event ) { event.Skip(); }
		virtual void doOK( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		TNewGameDialog( wxWindow* parent, wxWindowID id = ID_NEWGAME, const wxString& title = _("New Game"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxCLOSE_BOX|wxDEFAULT_DIALOG_STYLE ); 
		~TNewGameDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class TAboutDialog
///////////////////////////////////////////////////////////////////////////////
class TAboutDialog : public wxDialog 
{
	DECLARE_EVENT_TABLE()
	private:
		
		// Private event handlers
		void _wxFB_doInit( wxInitDialogEvent& event ){ doInit( event ); }
		
	
	protected:
		wxStaticText* m_staticTextVersion;
		wxStaticText* m_staticTextEngine;
		wxStaticText* m_staticText5;
		wxStaticText* m_staticText9;
		wxHyperlinkCtrl* m_hyperlink3;
		wxButton* m_button1;
		
		// Virtual event handlers, overide them in your derived class
		virtual void doInit( wxInitDialogEvent& event ) { event.Skip(); }
		
	
	public:
		
		TAboutDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("About"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~TAboutDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class TClockAdjustDialog
///////////////////////////////////////////////////////////////////////////////
class TClockAdjustDialog : public wxDialog 
{
	DECLARE_EVENT_TABLE()
	private:
		
		// Private event handlers
		void _wxFB_doInit( wxInitDialogEvent& event ){ doInit( event ); }
		void _wxFB_doCancel( wxCommandEvent& event ){ doCancel( event ); }
		void _wxFB_doOK( wxCommandEvent& event ){ doOK( event ); }
		
	
	protected:
		wxSpinCtrl* m_spinCtrlBlackMins;
		wxSpinCtrl* m_spinCtrlBlackSecs;
		wxSpinCtrl* m_spinCtrlWhiteMins;
		wxSpinCtrl* m_spinCtrlWhiteSecs;
		wxStdDialogButtonSizer* m_sdbSizer3;
		wxButton* m_sdbSizer3OK;
		wxButton* m_sdbSizer3Cancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void doInit( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void doCancel( wxCommandEvent& event ) { event.Skip(); }
		virtual void doOK( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		TClockAdjustDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Adjust clocks"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~TClockAdjustDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class TRatedSizeDialog
///////////////////////////////////////////////////////////////////////////////
class TRatedSizeDialog : public wxDialog 
{
	DECLARE_EVENT_TABLE()
	private:
		
		// Private event handlers
		void _wxFB_doSize9( wxCommandEvent& event ){ doSize9( event ); }
		void _wxFB_doSize19( wxCommandEvent& event ){ doSize19( event ); }
		
	
	protected:
		enum
		{
			ID_SIZE9 = 1000,
			ID_SIZE19
		};
		
		wxButton* m_buttonSize9;
		wxButton* m_buttonSize19;
		
		// Virtual event handlers, overide them in your derived class
		virtual void doSize9( wxCommandEvent& event ) { event.Skip(); }
		virtual void doSize19( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		TRatedSizeDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Select board size"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~TRatedSizeDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class TCalculateDialog
///////////////////////////////////////////////////////////////////////////////
class TCalculateDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticTextCalculating;
	
	public:
		
		TCalculateDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Calculation in progress"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~TCalculateDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class TAnalysisWindow
///////////////////////////////////////////////////////////////////////////////
class TAnalysisWindow : public wxFrame 
{
	DECLARE_EVENT_TABLE()
	private:
		
		// Private event handlers
		void _wxFB_doClose( wxCloseEvent& event ){ doClose( event ); }
		void _wxFB_doSelectCell( wxGridEvent& event ){ doSelectCell( event ); }
		
	
	protected:
		wxPanel* m_panel3;
		wxGrid* m_moveGrid;
		
		// Virtual event handlers, overide them in your derived class
		virtual void doClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void doSelectCell( wxGridEvent& event ) { event.Skip(); }
		
	
	public:
		
		TAnalysisWindow( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Analysis"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~TAnalysisWindow();
	
};

#endif //__GUI_H__
