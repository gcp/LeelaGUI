///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep 26 2007)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUI__
#define __GUI__

#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/statline.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/treectrl.h>
#include <wx/listctrl.h>
#include <wx/html/htmlwin.h>
#include <wx/notebook.h>
#include <wx/splitter.h>
#include <wx/statusbr.h>
#include <wx/menu.h>
#include <wx/frame.h>

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
		void _wxFB_doPaint( wxPaintEvent& event ){ doPaint( event ); }
		void _wxFB_doResize( wxSizeEvent& event ){ doResize( event ); }
		void _wxFB_doNewGame( wxCommandEvent& event ){ doNewGame( event ); }
		void _wxFB_doExit( wxCommandEvent& event ){ doExit( event ); }
		
	
	protected:
		enum
		{
			ID_DEFAULT = wxID_ANY, // Default
			ID_NEWGAME = 1000,
			ID_EXIT,
		};
		
		wxSplitterWindow* m_splitter1;
		wxPanel* m_panelBoard;
		wxPanel* m_panel6;
		wxStaticLine* m_staticline1;
		wxNotebook* m_notebook1;
		wxPanel* m_panel4;
		wxTextCtrl* m_logText;
		wxPanel* m_panel5;
		wxTreeCtrl* m_UCTTree;
		wxPanel* m_panel51;
		wxListCtrl* m_moveList;
		wxPanel* m_panel71;
		wxHtmlWindow* m_htmlWin1;
		wxStatusBar* m_statusBar;
		wxMenuBar* m_menubar1;
		wxMenu* m_menu1;
		
		// Virtual event handlers, overide them in your derived class
		virtual void doActivate( wxActivateEvent& event ){ event.Skip(); }
		virtual void doPaint( wxPaintEvent& event ){ event.Skip(); }
		virtual void doResize( wxSizeEvent& event ){ event.Skip(); }
		virtual void doNewGame( wxCommandEvent& event ){ event.Skip(); }
		virtual void doExit( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		TMainFrame( wxWindow* parent, wxWindowID id = ID_DEFAULT, const wxString& title = _("Leela"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 700,450 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL, const wxString& name = wxT("LeelaGUI") );
		void m_splitter1OnIdle( wxIdleEvent& )
		{
		m_splitter1->SetSashPosition( 373 );
		m_splitter1->Disconnect( wxEVT_IDLE, wxIdleEventHandler( TMainFrame::m_splitter1OnIdle ), NULL, this );
		}
		
	
};

#endif //__GUI__
