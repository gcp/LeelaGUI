///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep 26 2007)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "GUI.h"

///////////////////////////////////////////////////////////////////////////

TMainFrame::TMainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	m_splitter1 = new wxSplitterWindow( this, ID_DEFAULT, wxDefaultPosition, wxDefaultSize, wxSP_BORDER );
	m_splitter1->SetSashGravity( 0.650000 );
	m_splitter1->Connect( wxEVT_IDLE, wxIdleEventHandler( TMainFrame::m_splitter1OnIdle ), NULL, this );
	m_panel61 = new wxPanel( m_splitter1, ID_DEFAULT, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );
	
	m_panel7 = new wxPanel( m_panel61, ID_DEFAULT, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer7->Add( m_panel7, 1, wxEXPAND | wxALL, 5 );
	
	m_staticline1 = new wxStaticLine( m_panel61, ID_DEFAULT, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer7->Add( m_staticline1, 0, wxALIGN_RIGHT|wxEXPAND, 5 );
	
	m_panel61->SetSizer( bSizer7 );
	m_panel61->Layout();
	bSizer7->Fit( m_panel61 );
	m_panel6 = new wxPanel( m_splitter1, ID_DEFAULT, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	m_notebook1 = new wxNotebook( m_panel6, ID_DEFAULT, wxDefaultPosition, wxDefaultSize, 0 );
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
	m_notebook1->AddPage( m_panel5, _("UCT"), false );
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
	
	bSizer8->Add( m_notebook1, 1, wxEXPAND | wxALL, 5 );
	
	m_panel6->SetSizer( bSizer8 );
	m_panel6->Layout();
	bSizer8->Fit( m_panel6 );
	m_splitter1->SplitVertically( m_panel61, m_panel6, 0 );
	bSizer2->Add( m_splitter1, 1, wxALL|wxEXPAND, 1 );
	
	this->SetSizer( bSizer2 );
	this->Layout();
	m_statusBar = this->CreateStatusBar( 3, wxST_SIZEGRIP, ID_DEFAULT );
	m_menubar1 = new wxMenuBar( 0 );
	m_menu1 = new wxMenu();
	wxMenuItem* menuItemExit = new wxMenuItem( m_menu1, ID_DEFAULT, wxString( _("Exit") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( menuItemExit );
	m_menubar1->Append( m_menu1, _("File") );
	
	this->SetMenuBar( m_menubar1 );
	
	
	// Connect Events
	this->Connect( menuItemExit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( TMainFrame::doExit ) );
}
