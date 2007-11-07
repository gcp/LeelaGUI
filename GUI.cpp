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
	wxMenuItem* menuItemNewGame = new wxMenuItem( m_menu1, ID_NEWGAME9, wxString( _("New game &9x9") ) , _("Start a new 9x9 game"), wxITEM_NORMAL );
	m_menu1->Append( menuItemNewGame );
	wxMenuItem* menuItem3 = new wxMenuItem( m_menu1, ID_NEWGAME13, wxString( _("New game 1&3x13") ) , _("Start a new 13x13 game"), wxITEM_NORMAL );
	m_menu1->Append( menuItem3 );
	wxMenuItem* menuItem4 = new wxMenuItem( m_menu1, ID_NEWGAME19, wxString( _("New game &19x19") ) , _("Start a new 19x19 game"), wxITEM_NORMAL );
	m_menu1->Append( menuItem4 );
	
	m_menu1->AppendSeparator();
	wxMenuItem* menuItemExit = new wxMenuItem( m_menu1, ID_EXIT, wxString( _("E&xit") ) + wxT('\t') + wxT("Alt-F4"), _("Exit the program"), wxITEM_NORMAL );
	m_menu1->Append( menuItemExit );
	m_menubar1->Append( m_menu1, _("&File") );
	
	m_menu2 = new wxMenu();
	wxMenuItem* menuItem6 = new wxMenuItem( m_menu2, ID_PASS, wxString( _("&Pass") ) + wxT('\t') + wxT("Alt-P"), _("Pass"), wxITEM_NORMAL );
	m_menu2->Append( menuItem6 );
	wxMenuItem* menuItem5 = new wxMenuItem( m_menu2, ID_SCORE, wxString( _("&Score") ) + wxT('\t') + wxT("Alt-S"), _("Score the position"), wxITEM_NORMAL );
	m_menu2->Append( menuItem5 );
	m_menubar1->Append( m_menu2, _("&Score") );
	
	m_menu3 = new wxMenu();
	wxMenuItem* menuItem7 = new wxMenuItem( m_menu3, wxID_ANY, wxString( _("&About") ) , _("Information about the program"), wxITEM_NORMAL );
	m_menu3->Append( menuItem7 );
	m_menubar1->Append( m_menu3, _("&Help") );
	
	this->SetMenuBar( m_menubar1 );
	
	m_toolBar1 = this->CreateToolBar( wxTB_FLAT|wxTB_HORIZONTAL, wxID_ANY ); 
	m_toolBar1->AddTool( ID_NEWGAME9, _("New Game"), wxBitmap( wxT("IDB_NEWGAME"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Start a new game"), _("Start a new game") );
	m_toolBar1->AddTool( wxID_ANY, _("Load Game"), wxBitmap( wxT("IDB_OPEN"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Load a game from a file"), wxEmptyString );
	m_toolBar1->AddTool( wxID_ANY, _("Save"), wxBitmap( wxT("IDB_SAVE"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Save game to a file"), wxEmptyString );
	m_toolBar1->AddTool( wxID_ANY, _("Save As"), wxBitmap( wxT("IDB_SAVEAS"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Save game under a different name"), wxEmptyString );
	m_toolBar1->AddSeparator();
	m_toolBar1->AddTool( wxID_ANY, _("Undo"), wxBitmap( wxT("IDB_UNDO"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Take back a mve"), wxEmptyString );
	m_toolBar1->AddTool( wxID_ANY, _("Forward"), wxBitmap( wxT("IDB_REDO"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Go forward one move"), wxEmptyString );
	m_toolBar1->AddSeparator();
	m_toolBar1->AddTool( ID_PASS, _("tool"), wxBitmap( wxT("IDB_PASS"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Pass"), _("Pass") );
	m_toolBar1->AddTool( ID_SCORE, _("tool"), wxBitmap( wxT("IDB_SCORE"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Score the game"), _("Score the game") );
	m_toolBar1->AddSeparator();
	m_toolBar1->AddTool( ID_EXIT, _("Exit"), wxBitmap( wxT("IDB_QUIT"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Exits the program"), wxEmptyString );
	m_toolBar1->Realize();
	
}
