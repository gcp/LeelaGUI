///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep 26 2007)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "TBoardPanel.h"

#include "GUI.h"

///////////////////////////////////////////////////////////////////////////
BEGIN_EVENT_TABLE( TMainFrame, wxFrame )
	EVT_ACTIVATE( TMainFrame::_wxFB_doActivate )
	EVT_PAINT( TMainFrame::_wxFB_doPaint )
	EVT_SIZE( TMainFrame::_wxFB_doResize )
	EVT_MENU( ID_NEWGAME9, TMainFrame::_wxFB_doNewGame9x9 )
	EVT_MENU( ID_NEWGAME13, TMainFrame::_wxFB_doNewGame13x13 )
	EVT_MENU( ID_NEWGAME19, TMainFrame::_wxFB_doNewGame19x19 )
	EVT_MENU( ID_EXIT, TMainFrame::_wxFB_doExit )
	EVT_MENU( ID_PASS, TMainFrame::_wxFB_doPass )
	EVT_MENU( ID_SCORE, TMainFrame::_wxFB_doScore )
END_EVENT_TABLE()

TMainFrame::TMainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxFrame( parent, id, title, pos, size, style, name )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	m_splitter1 = new wxSplitterWindow( this, ID_BOARDSASH, wxDefaultPosition, wxDefaultSize, 0 );
	m_splitter1->SetSashGravity( 0.65 );
	m_splitter1->SetMinimumPaneSize( 1 );
	m_splitter1->Connect( wxEVT_IDLE, wxIdleEventHandler( TMainFrame::m_splitter1OnIdle ), NULL, this );
	m_panelBoard = new TBoardPanel( m_splitter1, ID_BOARDPANEL, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE|wxTAB_TRAVERSAL );
	m_panel6 = new wxPanel( m_splitter1, ID_DEFAULT, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticline1 = new wxStaticLine( m_panel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer8->Add( m_staticline1, 0, wxEXPAND | wxALL, 0 );
	
	m_notebook1 = new wxNotebook( m_panel6, ID_DEFAULT, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_panel4 = new wxPanel( m_notebook1, ID_DEFAULT, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	m_logText = new wxTextCtrl( m_panel4, ID_DEFAULT, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_AUTO_URL|wxTE_MULTILINE|wxTE_READONLY );
	bSizer5->Add( m_logText, 1, wxALL|wxEXPAND, 5 );
	
	m_panel4->SetSizer( bSizer5 );
	m_panel4->Layout();
	bSizer5->Fit( m_panel4 );
	m_notebook1->AddPage( m_panel4, _("Console"), true );
	m_panel5 = new wxPanel( m_notebook1, ID_DEFAULT, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	m_UCTTree = new wxTreeCtrl( m_panel5, ID_DEFAULT, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE );
	bSizer4->Add( m_UCTTree, 1, wxALL|wxEXPAND, 5 );
	
	m_panel5->SetSizer( bSizer4 );
	m_panel5->Layout();
	bSizer4->Fit( m_panel5 );
	m_notebook1->AddPage( m_panel5, _("Tree"), false );
	m_panel51 = new wxPanel( m_notebook1, ID_DEFAULT, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer51;
	bSizer51 = new wxBoxSizer( wxVERTICAL );
	
	m_moveList = new wxListCtrl( m_panel51, ID_DEFAULT, wxDefaultPosition, wxDefaultSize, wxLC_LIST|wxLC_VRULES );
	bSizer51->Add( m_moveList, 1, wxALL|wxEXPAND, 5 );
	
	m_panel51->SetSizer( bSizer51 );
	m_panel51->Layout();
	bSizer51->Fit( m_panel51 );
	m_notebook1->AddPage( m_panel51, _("Moves"), false );
	m_panel71 = new wxPanel( m_notebook1, ID_DEFAULT, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer71;
	bSizer71 = new wxBoxSizer( wxVERTICAL );
	
	m_htmlWin1 = new wxHtmlWindow( m_panel71, ID_DEFAULT, wxDefaultPosition, wxDefaultSize, wxHW_SCROLLBAR_AUTO|wxSUNKEN_BORDER );
	bSizer71->Add( m_htmlWin1, 1, wxALL|wxEXPAND, 5 );
	
	m_panel71->SetSizer( bSizer71 );
	m_panel71->Layout();
	bSizer71->Fit( m_panel71 );
	m_notebook1->AddPage( m_panel71, _("Notation"), false );
	
	bSizer8->Add( m_notebook1, 1, wxALL|wxEXPAND, 2 );
	
	m_panel6->SetSizer( bSizer8 );
	m_panel6->Layout();
	bSizer8->Fit( m_panel6 );
	m_splitter1->SplitVertically( m_panelBoard, m_panel6, 378 );
	bSizer2->Add( m_splitter1, 1, wxALL|wxEXPAND, 0 );
	
	this->SetSizer( bSizer2 );
	this->Layout();
	m_statusBar = this->CreateStatusBar( 3, wxST_SIZEGRIP, ID_DEFAULT );
	m_menubar1 = new wxMenuBar( 0 );
	m_menu1 = new wxMenu();
	wxMenuItem* menuItemNewGame = new wxMenuItem( m_menu1, ID_NEWGAME9, wxString( _("New game 9x9") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( menuItemNewGame );
	wxMenuItem* menuItem3 = new wxMenuItem( m_menu1, ID_NEWGAME13, wxString( _("New game 13x13") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( menuItem3 );
	wxMenuItem* menuItem4 = new wxMenuItem( m_menu1, ID_NEWGAME19, wxString( _("New game 19x19") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( menuItem4 );
	
	m_menu1->AppendSeparator();
	wxMenuItem* menuItemExit = new wxMenuItem( m_menu1, ID_EXIT, wxString( _("Exit") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( menuItemExit );
	m_menubar1->Append( m_menu1, _("File") );
	
	m_menu2 = new wxMenu();
	wxMenuItem* menuItem6 = new wxMenuItem( m_menu2, ID_PASS, wxString( _("Pass") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu2->Append( menuItem6 );
	wxMenuItem* menuItem5 = new wxMenuItem( m_menu2, ID_SCORE, wxString( _("Score") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu2->Append( menuItem5 );
	m_menubar1->Append( m_menu2, _("Score") );
	
	this->SetMenuBar( m_menubar1 );
	
}
