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
	EVT_MENU( ID_NEWGAME, TMainFrame::_wxFB_doNewGame )
	EVT_MENU( ID_NEWRATED, TMainFrame::_wxFB_doNewRatedGame )
	EVT_MENU( ID_OPEN, TMainFrame::_wxFB_doOpenSGF )
	EVT_MENU( ID_SAVE, TMainFrame::_wxFB_doSaveSGF )
	EVT_MENU( ID_EXIT, TMainFrame::_wxFB_doExit )
	EVT_MENU( ID_UNDO, TMainFrame::_wxFB_doUndo )
	EVT_MENU( ID_REDO, TMainFrame::_wxFB_doForward )
	EVT_MENU( ID_BACK10, TMainFrame::_wxFB_doBack10 )
	EVT_MENU( ID_FWD10, TMainFrame::_wxFB_doForward10 )
	EVT_MENU( ID_FORCE, TMainFrame::_wxFB_doForceMove )
	EVT_MENU( ID_PASS, TMainFrame::_wxFB_doPass )
	EVT_MENU( ID_SCORE, TMainFrame::_wxFB_doScore )
	EVT_MENU( ID_SHOWTERRITORY, TMainFrame::_wxFB_doToggleTerritory )
	EVT_MENU( ID_SHOWMOYO, TMainFrame::_wxFB_doToggleMoyo )
	EVT_MENU( ID_SOUNDSWITCH, TMainFrame::_wxFB_doSoundToggle )
	EVT_MENU( ID_HELPRULES, TMainFrame::_wxFB_doGoRules )
	EVT_MENU( ID_HOMEPAGE, TMainFrame::_wxFB_doHomePage )
	EVT_MENU( ID_HELPABOUT, TMainFrame::_wxFB_doHelpAbout )
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
	wxMenuItem* menuItemNewGame = new wxMenuItem( m_menu1, ID_NEWGAME, wxString( _("&New game...") ) + wxT('\t') + wxT("Ctrl-N"), _("Start a new game"), wxITEM_NORMAL );
	m_menu1->Append( menuItemNewGame );
	wxMenuItem* menuItemNewRated = new wxMenuItem( m_menu1, ID_NEWRATED, wxString( _("New &rated game") ) + wxT('\t') + wxT("Ctrl-R"), _("Starts a new rated game"), wxITEM_NORMAL );
	m_menu1->Append( menuItemNewRated );
	
	m_menu1->AppendSeparator();
	wxMenuItem* menuItem11 = new wxMenuItem( m_menu1, ID_OPEN, wxString( _("&Open game...") ) + wxT('\t') + wxT("Ctrl-O"), _("Opens a game from disk"), wxITEM_NORMAL );
	m_menu1->Append( menuItem11 );
	wxMenuItem* menuItem12 = new wxMenuItem( m_menu1, ID_SAVE, wxString( _("&Save game...") ) + wxT('\t') + wxT("Ctrl-S"), _("Save a game to disk"), wxITEM_NORMAL );
	m_menu1->Append( menuItem12 );
	
	m_menu1->AppendSeparator();
	wxMenuItem* menuItemExit = new wxMenuItem( m_menu1, ID_EXIT, wxString( _("E&xit") ) + wxT('\t') + wxT("Alt-F4"), _("Exit the program"), wxITEM_NORMAL );
	m_menu1->Append( menuItemExit );
	m_menubar1->Append( m_menu1, _("&File") );
	
	m_menu2 = new wxMenu();
	wxMenuItem* menuItem9 = new wxMenuItem( m_menu2, ID_UNDO, wxString( _("&Undo") ) + wxT('\t') + wxT("Ctrl-Z"), wxEmptyString, wxITEM_NORMAL );
	m_menu2->Append( menuItem9 );
	wxMenuItem* menuItem8 = new wxMenuItem( m_menu2, ID_REDO, wxString( _("&Forward") ) + wxT('\t') + wxT("Ctrl-Y"), wxEmptyString, wxITEM_NORMAL );
	m_menu2->Append( menuItem8 );
	
	m_menu2->AppendSeparator();
	wxMenuItem* menuItem131 = new wxMenuItem( m_menu2, ID_BACK10, wxString( _("Go &back 10 moves") ) + wxT('\t') + wxT("Alt-B"), _("Undo 10 moves"), wxITEM_NORMAL );
	m_menu2->Append( menuItem131 );
	wxMenuItem* menuItem141 = new wxMenuItem( m_menu2, ID_FWD10, wxString( _("Go for&ward 10 moves") ) + wxT('\t') + wxT("Alt-F"), _("Forward 10 moves"), wxITEM_NORMAL );
	m_menu2->Append( menuItem141 );
	
	m_menu2->AppendSeparator();
	wxMenuItem* menuItem18 = new wxMenuItem( m_menu2, ID_FORCE, wxString( _("Force &computer move") ) + wxT('\t') + wxT("Ctrl-F"), _("Force the computer to move now"), wxITEM_NORMAL );
	m_menu2->Append( menuItem18 );
	wxMenuItem* menuItem6 = new wxMenuItem( m_menu2, ID_PASS, wxString( _("&Pass") ) + wxT('\t') + wxT("Alt-P"), _("Pass"), wxITEM_NORMAL );
	m_menu2->Append( menuItem6 );
	wxMenuItem* menuItem5 = new wxMenuItem( m_menu2, ID_SCORE, wxString( _("&Score") ) + wxT('\t') + wxT("Alt-S"), _("Score the position"), wxITEM_NORMAL );
	m_menu2->Append( menuItem5 );
	m_menubar1->Append( m_menu2, _("&Game") );
	
	m_menuSettings = new wxMenu();
	wxMenuItem* menuItem15 = new wxMenuItem( m_menuSettings, ID_SHOWTERRITORY, wxString( _("Show &Territory") ) + wxT('\t') + wxT("Ctrl-T"), _("Show Territory"), wxITEM_CHECK );
	m_menuSettings->Append( menuItem15 );
	wxMenuItem* menuItem16 = new wxMenuItem( m_menuSettings, ID_SHOWMOYO, wxString( _("Show &Moyo") ) + wxT('\t') + wxT("Ctrl-M"), _("Show Moyo"), wxITEM_CHECK );
	m_menuSettings->Append( menuItem16 );
	
	m_menuSettings->AppendSeparator();
	wxMenuItem* menuItemSound = new wxMenuItem( m_menuSettings, ID_SOUNDSWITCH, wxString( _("Sound") ) , _("Enable or disable sound"), wxITEM_CHECK );
	m_menuSettings->Append( menuItemSound );
	menuItemSound->Check( true );
	
	m_menubar1->Append( m_menuSettings, _("&Settings") );
	
	m_menu3 = new wxMenu();
	wxMenuItem* menuItem13 = new wxMenuItem( m_menu3, ID_HELPRULES, wxString( _("&Go Rules") ) + wxT('\t') + wxT("F1"), _("Explanation of the rules of Go"), wxITEM_NORMAL );
	m_menu3->Append( menuItem13 );
	wxMenuItem* menuItem10 = new wxMenuItem( m_menu3, ID_HOMEPAGE, wxString( _("Leela Homepage") ) + wxT('\t') + wxT("Ctrl-H"), wxEmptyString, wxITEM_NORMAL );
	m_menu3->Append( menuItem10 );
	wxMenuItem* menuItem7 = new wxMenuItem( m_menu3, ID_HELPABOUT, wxString( _("&About...") ) , _("Information about the program"), wxITEM_NORMAL );
	m_menu3->Append( menuItem7 );
	m_menubar1->Append( m_menu3, _("&Help") );
	
	this->SetMenuBar( m_menubar1 );
	
	m_toolBar1 = this->CreateToolBar( wxTB_FLAT|wxTB_HORIZONTAL, wxID_ANY ); 
	m_toolBar1->AddTool( ID_NEWGAME, _("New Game"), wxBitmap( wxT("IDB_NEWGAME"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Start a new game"), _("Start a new game") );
	m_toolBar1->AddTool( ID_NEWRATED, _("New Rated Game"), wxBitmap( wxT("IDB_NEWRATED"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Start a new rated game"), _("Start a new rated game") );
	m_toolBar1->AddTool( ID_OPEN, _("Load Game"), wxBitmap( wxT("IDB_OPEN"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Load a game"), _("Load a game") );
	m_toolBar1->AddTool( ID_SAVE, _("Save"), wxBitmap( wxT("IDB_SAVEAS"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Save the game"), _("Save the game") );
	m_toolBar1->AddSeparator();
	m_toolBar1->AddTool( ID_BACK10, _("Go back 10 moves"), wxBitmap( wxT("IDB_BACKWARD"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Go back 10 moves"), _("Go back 10 moves") );
	m_toolBar1->AddTool( ID_UNDO, _("Undo"), wxBitmap( wxT("IDB_UNDO"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Take back one move"), _("Take back one move") );
	m_toolBar1->AddTool( ID_REDO, _("Forward"), wxBitmap( wxT("IDB_REDO"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Go forward one move"), _("Go forward one move") );
	m_toolBar1->AddTool( ID_FWD10, _("Forward 10"), wxBitmap( wxT("IDB_FORWARD"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Go forward 10 moves"), _("Go forward 10 moves") );
	m_toolBar1->AddSeparator();
	m_toolBar1->AddTool( ID_FORCE, _("Force computer move"), wxBitmap( wxT("IDB_FORCE"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Force computer move"), _("Force computer move") );
	m_toolBar1->AddTool( ID_PASS, _("tool"), wxBitmap( wxT("IDB_PASS"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Pass"), _("Pass") );
	m_toolBar1->AddTool( ID_SCORE, _("tool"), wxBitmap( wxT("IDB_SCORE"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Score the game"), _("Score the game") );
	m_toolBar1->AddSeparator();
	m_toolBar1->AddTool( ID_EXIT, _("Exit"), wxBitmap( wxT("IDB_QUIT"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Exits the program"), wxEmptyString );
	m_toolBar1->Realize();
	
}
BEGIN_EVENT_TABLE( TNewGameDialog, wxDialog )
	EVT_SPINCTRL( ID_HANDICAPSPIN, TNewGameDialog::_wxFB_doHandicapUpdate )
	EVT_BUTTON( wxID_CANCEL, TNewGameDialog::_wxFB_doCancel )
	EVT_BUTTON( wxID_OK, TNewGameDialog::_wxFB_doOK )
END_EVENT_TABLE()

TNewGameDialog::TNewGameDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );
	
	bSizer7->SetMinSize( wxSize( 260,250 ) ); 
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );
	
	wxString m_radioBoxBoardSizeChoices[] = { _("9 x 9"), _("13 x 13"), _("19 x 19") };
	int m_radioBoxBoardSizeNChoices = sizeof( m_radioBoxBoardSizeChoices ) / sizeof( wxString );
	m_radioBoxBoardSize = new wxRadioBox( this, wxID_ANY, _("Board size"), wxDefaultPosition, wxDefaultSize, m_radioBoxBoardSizeNChoices, m_radioBoxBoardSizeChoices, 1, wxRA_SPECIFY_COLS );
	m_radioBoxBoardSize->SetSelection( 0 );
	bSizer9->Add( m_radioBoxBoardSize, 0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 5 );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( this, -1, _("Komi (+0.5)") ), wxHORIZONTAL );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, _("Komi"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticText2->Wrap( -1 );
	sbSizer2->Add( m_staticText2, 1, wxALIGN_CENTER, 5 );
	
	m_spinCtrlKomi = new wxSpinCtrl( this, ID_KOMISPIN, wxT("7"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 15, 0 );
	sbSizer2->Add( m_spinCtrlKomi, 1, wxALIGN_CENTER, 5 );
	
	bSizer9->Add( sbSizer2, 0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 5 );
	
	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( this, -1, _("Handicap") ), wxHORIZONTAL );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, _("Handicap"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticText3->Wrap( -1 );
	sbSizer3->Add( m_staticText3, 1, wxALIGN_CENTER, 5 );
	
	m_spinCtrlHandicap = new wxSpinCtrl( this, ID_HANDICAPSPIN, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 9, 0 );
	sbSizer3->Add( m_spinCtrlHandicap, 1, wxALIGN_CENTER, 5 );
	
	bSizer9->Add( sbSizer3, 0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 5 );
	
	bSizer11->Add( bSizer9, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );
	
	wxString m_radioBoxColorChoices[] = { _("Black"), _("White") };
	int m_radioBoxColorNChoices = sizeof( m_radioBoxColorChoices ) / sizeof( wxString );
	m_radioBoxColor = new wxRadioBox( this, wxID_ANY, _("Your Color"), wxDefaultPosition, wxDefaultSize, m_radioBoxColorNChoices, m_radioBoxColorChoices, 1, wxRA_SPECIFY_ROWS );
	m_radioBoxColor->SetSelection( 0 );
	bSizer10->Add( m_radioBoxColor, 0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 5 );
	
	wxString m_radioBoxLevelChoices[] = { _("100 simulations"), _("500 simulations"), _("1000 simulations"), _("5000 simulations"), _("10000 simulations"), _("Unlimited") };
	int m_radioBoxLevelNChoices = sizeof( m_radioBoxLevelChoices ) / sizeof( wxString );
	m_radioBoxLevel = new wxRadioBox( this, wxID_ANY, _("Engine Max Level"), wxDefaultPosition, wxDefaultSize, m_radioBoxLevelNChoices, m_radioBoxLevelChoices, 1, wxRA_SPECIFY_COLS );
	m_radioBoxLevel->SetSelection( 2 );
	bSizer10->Add( m_radioBoxLevel, 0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 5 );
	
	bSizer11->Add( bSizer10, 1, wxEXPAND, 5 );
	
	bSizer7->Add( bSizer11, 1, wxEXPAND, 5 );
	
	m_sdbSizer1 = new wxStdDialogButtonSizer();
	m_sdbSizer1OK = new wxButton( this, wxID_OK );
	m_sdbSizer1->AddButton( m_sdbSizer1OK );
	m_sdbSizer1Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer1->AddButton( m_sdbSizer1Cancel );
	m_sdbSizer1->Realize();
	bSizer7->Add( m_sdbSizer1, 0, wxEXPAND|wxFIXED_MINSIZE, 1 );
	
	this->SetSizer( bSizer7 );
	this->Layout();
}
BEGIN_EVENT_TABLE( TAboutDialog, wxDialog )
	EVT_INIT_DIALOG( TAboutDialog::_wxFB_doInit )
END_EVENT_TABLE()

TAboutDialog::TAboutDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );
	
	m_staticTextVersion = new wxStaticText( this, wxID_ANY, _("Leela lite version 0.2.7"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticTextVersion->Wrap( -1 );
	bSizer9->Add( m_staticTextVersion, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, _("Copyright (C) 2007 Gian-Carlo Pascutto"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	bSizer9->Add( m_staticText5, 0, wxALIGN_CENTER|wxALL, 5 );
	
	m_hyperlink3 = new wxHyperlinkCtrl( this, wxID_ANY, _("http://www.sjeng.org"), wxT("http://www.sjeng.org"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );
	bSizer9->Add( m_hyperlink3, 0, wxALIGN_CENTER|wxALL, 5 );
	
	m_button1 = new wxButton( this, wxID_OK, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer9->Add( m_button1, 0, wxALIGN_CENTER|wxALL, 5 );
	
	this->SetSizer( bSizer9 );
	this->Layout();
}
BEGIN_EVENT_TABLE( TNagDialog, wxDialog )
	EVT_INIT_DIALOG( TNagDialog::_wxFB_doInit )
	EVT_BUTTON( wxID_OK, TNagDialog::_wxFB_doOK )
END_EVENT_TABLE()

TNagDialog::TNagDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->Centre( wxBOTH );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText8 = new wxStaticText( this, wxID_ANY, _("If you like Leela, you might also like:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	bSizer10->Add( m_staticText8, 0, wxALL, 5 );
	
	m_staticText9 = new wxStaticText( this, wxID_ANY, _("Leela - Full Version"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	m_staticText9->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer10->Add( m_staticText9, 0, wxALIGN_CENTER|wxALL, 5 );
	
	m_hyperlink1 = new wxHyperlinkCtrl( this, wxID_ANY, wxEmptyString, wxT("http://www.sjeng.org/leela"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );
	bSizer10->Add( m_hyperlink1, 0, wxALIGN_CENTER|wxALL, 5 );
	
	m_staticText10 = new wxStaticText( this, wxID_ANY, _("Deep Sjeng - The chess program"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	m_staticText10->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer10->Add( m_staticText10, 0, wxALIGN_CENTER|wxALL, 5 );
	
	m_hyperlink2 = new wxHyperlinkCtrl( this, wxID_ANY, wxEmptyString, wxT("http://www.sjeng.org/deepsjeng2"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );
	bSizer10->Add( m_hyperlink2, 0, wxALIGN_CENTER|wxALL, 5 );
	
	m_button2 = new wxButton( this, wxID_OK, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer10->Add( m_button2, 0, wxALIGN_CENTER|wxALL, 5 );
	
	this->SetSizer( bSizer10 );
	this->Layout();
}
