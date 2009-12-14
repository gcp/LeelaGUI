///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 16 2008)
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
	EVT_MENU( ID_RESIGN, TMainFrame::_wxFB_doResign )
	EVT_MENU( ID_SCORE, TMainFrame::_wxFB_doScore )
	EVT_MENU( ID_ANALYZE, TMainFrame::_wxFB_doAnalyze )
	EVT_MENU( ID_SHOWTERRITORY, TMainFrame::_wxFB_doToggleTerritory )
	EVT_MENU( ID_SHOWMOYO, TMainFrame::_wxFB_doToggleMoyo )
	EVT_MENU( ID_PASSTOGGLE, TMainFrame::_wxFB_doPassToggle )
	EVT_MENU( ID_RESIGNTOGGLE, TMainFrame::_wxFB_doResignToggle )
	EVT_MENU( ID_PONDERTOGGLE, TMainFrame::_wxFB_doPonderToggle )
	EVT_MENU( ID_SOUNDSWITCH, TMainFrame::_wxFB_doSoundToggle )
	EVT_MENU( wxID_ADJUSTCLOCKS, TMainFrame::_wxFB_doAdjustClocks )
	EVT_MENU( ID_HELPRULES, TMainFrame::_wxFB_doGoRules )
	EVT_MENU( ID_HOMEPAGE, TMainFrame::_wxFB_doHomePage )
	EVT_MENU( ID_HELPABOUT, TMainFrame::_wxFB_doHelpAbout )
END_EVENT_TABLE()

TMainFrame::TMainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxFrame( parent, id, title, pos, size, style, name )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	m_panelBoard = new TBoardPanel( this, ID_BOARDPANEL, wxDefaultPosition, wxSize( -1,-1 ), wxFULL_REPAINT_ON_RESIZE|wxTAB_TRAVERSAL );
	bSizer2->Add( m_panelBoard, 1, wxEXPAND | wxALL, 1 );
	
	this->SetSizer( bSizer2 );
	this->Layout();
	m_statusBar = this->CreateStatusBar( 2, wxST_SIZEGRIP, ID_DEFAULT );
	m_menubar1 = new wxMenuBar( 0 );
	m_menu1 = new wxMenu();
	wxMenuItem* menuItemNewGame;
	menuItemNewGame = new wxMenuItem( m_menu1, ID_NEWGAME, wxString( _("&New game...") ) + wxT('\t') + wxT("Ctrl-N"), _("Start a new game"), wxITEM_NORMAL );
	m_menu1->Append( menuItemNewGame );
	
	wxMenuItem* menuItemNewRated;
	menuItemNewRated = new wxMenuItem( m_menu1, ID_NEWRATED, wxString( _("New &rated game") ) + wxT('\t') + wxT("Ctrl-R"), _("Starts a new rated game"), wxITEM_NORMAL );
	m_menu1->Append( menuItemNewRated );
	
	m_menu1->AppendSeparator();
	
	wxMenuItem* menuItem11;
	menuItem11 = new wxMenuItem( m_menu1, ID_OPEN, wxString( _("&Open game...") ) + wxT('\t') + wxT("Ctrl-O"), _("Opens a game from disk"), wxITEM_NORMAL );
	m_menu1->Append( menuItem11 );
	
	wxMenuItem* menuItem12;
	menuItem12 = new wxMenuItem( m_menu1, ID_SAVE, wxString( _("&Save game...") ) + wxT('\t') + wxT("Ctrl-S"), _("Save a game to disk"), wxITEM_NORMAL );
	m_menu1->Append( menuItem12 );
	
	m_menu1->AppendSeparator();
	
	wxMenuItem* menuItemExit;
	menuItemExit = new wxMenuItem( m_menu1, ID_EXIT, wxString( _("E&xit") ) + wxT('\t') + wxT("Alt-F4"), _("Exit the program"), wxITEM_NORMAL );
	m_menu1->Append( menuItemExit );
	
	m_menubar1->Append( m_menu1, _("&File") );
	
	m_menu2 = new wxMenu();
	wxMenuItem* menuItem9;
	menuItem9 = new wxMenuItem( m_menu2, ID_UNDO, wxString( _("&Undo") ) + wxT('\t') + wxT("Ctrl-Z"), wxEmptyString, wxITEM_NORMAL );
	m_menu2->Append( menuItem9 );
	
	wxMenuItem* menuItem8;
	menuItem8 = new wxMenuItem( m_menu2, ID_REDO, wxString( _("&Forward") ) + wxT('\t') + wxT("Ctrl-Y"), wxEmptyString, wxITEM_NORMAL );
	m_menu2->Append( menuItem8 );
	
	m_menu2->AppendSeparator();
	
	wxMenuItem* menuItem131;
	menuItem131 = new wxMenuItem( m_menu2, ID_BACK10, wxString( _("Go &back 10 moves") ) + wxT('\t') + wxT("Alt-B"), _("Undo 10 moves"), wxITEM_NORMAL );
	m_menu2->Append( menuItem131 );
	
	wxMenuItem* menuItem141;
	menuItem141 = new wxMenuItem( m_menu2, ID_FWD10, wxString( _("Go for&ward 10 moves") ) + wxT('\t') + wxT("Alt-F"), _("Forward 10 moves"), wxITEM_NORMAL );
	m_menu2->Append( menuItem141 );
	
	m_menu2->AppendSeparator();
	
	wxMenuItem* menuItem18;
	menuItem18 = new wxMenuItem( m_menu2, ID_FORCE, wxString( _("Force &computer move") ) + wxT('\t') + wxT("Ctrl-F"), _("Force the computer to move now"), wxITEM_NORMAL );
	m_menu2->Append( menuItem18 );
	
	m_menu2->AppendSeparator();
	
	wxMenuItem* menuItem6;
	menuItem6 = new wxMenuItem( m_menu2, ID_PASS, wxString( _("&Pass") ) + wxT('\t') + wxT("Alt-P"), _("Pass"), wxITEM_NORMAL );
	m_menu2->Append( menuItem6 );
	
	wxMenuItem* menuItem20;
	menuItem20 = new wxMenuItem( m_menu2, ID_RESIGN, wxString( _("&Resign") ) + wxT('\t') + wxT("Alt-R"), _("Resign the game"), wxITEM_NORMAL );
	m_menu2->Append( menuItem20 );
	
	m_menu2->AppendSeparator();
	
	wxMenuItem* menuItem5;
	menuItem5 = new wxMenuItem( m_menu2, ID_SCORE, wxString( _("&Score game") ) + wxT('\t') + wxT("Alt-S"), _("Score the position"), wxITEM_NORMAL );
	m_menu2->Append( menuItem5 );
	
	m_menubar1->Append( m_menu2, _("&Game") );
	
	m_menuAnalyze = new wxMenu();
	wxMenuItem* menuItemAnalyze;
	menuItemAnalyze = new wxMenuItem( m_menuAnalyze, ID_ANALYZE, wxString( _("&Start/Stop analysis") ) + wxT('\t') + wxT("Ctrl-A"), _("Start analyzing"), wxITEM_NORMAL );
	m_menuAnalyze->Append( menuItemAnalyze );
	
	m_menubar1->Append( m_menuAnalyze, _("&Analyze") );
	
	m_menuSettings = new wxMenu();
	wxMenuItem* menuItem15;
	menuItem15 = new wxMenuItem( m_menuSettings, ID_SHOWTERRITORY, wxString( _("Show &Territory") ) + wxT('\t') + wxT("Ctrl-T"), _("Show Territory"), wxITEM_CHECK );
	m_menuSettings->Append( menuItem15 );
	
	wxMenuItem* menuItem16;
	menuItem16 = new wxMenuItem( m_menuSettings, ID_SHOWMOYO, wxString( _("Show &Moyo") ) + wxT('\t') + wxT("Ctrl-M"), _("Show Moyo"), wxITEM_CHECK );
	m_menuSettings->Append( menuItem16 );
	
	m_menuSettings->AppendSeparator();
	
	wxMenuItem* m_menuPassToggle;
	m_menuPassToggle = new wxMenuItem( m_menuSettings, ID_PASSTOGGLE, wxString( _("Engine &passes") ) , _("Allows the engine to pass"), wxITEM_CHECK );
	m_menuSettings->Append( m_menuPassToggle );
	m_menuPassToggle->Check( true );
	
	wxMenuItem* menuItemResignToggle;
	menuItemResignToggle = new wxMenuItem( m_menuSettings, ID_RESIGNTOGGLE, wxString( _("Engine &resigns") ) , _("Allows the engine to resign or not"), wxITEM_CHECK );
	m_menuSettings->Append( menuItemResignToggle );
	menuItemResignToggle->Check( true );
	
	wxMenuItem* m_menuItemPonder;
	m_menuItemPonder = new wxMenuItem( m_menuSettings, ID_PONDERTOGGLE, wxString( _("Engine &ponders") ) , _("Allows the engine to think during the opponents time"), wxITEM_CHECK );
	m_menuSettings->Append( m_menuItemPonder );
	m_menuItemPonder->Check( true );
	
	wxMenuItem* menuItemSound;
	menuItemSound = new wxMenuItem( m_menuSettings, ID_SOUNDSWITCH, wxString( _("&Sound") ) , _("Enable or disable sound"), wxITEM_CHECK );
	m_menuSettings->Append( menuItemSound );
	menuItemSound->Check( true );
	
	m_menuSettings->AppendSeparator();
	
	wxMenuItem* m_menuItemAdjustClocks;
	m_menuItemAdjustClocks = new wxMenuItem( m_menuSettings, wxID_ADJUSTCLOCKS, wxString( _("&Adjust clocks...") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuSettings->Append( m_menuItemAdjustClocks );
	
	m_menubar1->Append( m_menuSettings, _("&Settings") );
	
	m_menu3 = new wxMenu();
	wxMenuItem* menuItem13;
	menuItem13 = new wxMenuItem( m_menu3, ID_HELPRULES, wxString( _("&Go Rules") ) + wxT('\t') + wxT("F1"), _("Explanation of the rules of Go"), wxITEM_NORMAL );
	m_menu3->Append( menuItem13 );
	
	wxMenuItem* menuItem10;
	menuItem10 = new wxMenuItem( m_menu3, ID_HOMEPAGE, wxString( _("Leela Homepage") ) + wxT('\t') + wxT("Ctrl-H"), wxEmptyString, wxITEM_NORMAL );
	m_menu3->Append( menuItem10 );
	
	m_menu3->AppendSeparator();
	
	wxMenuItem* menuItem7;
	menuItem7 = new wxMenuItem( m_menu3, ID_HELPABOUT, wxString( _("&About...") ) , _("Information about the program"), wxITEM_NORMAL );
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
	m_toolBar1->AddTool( ID_ANALYZE, _("tool"), wxBitmap( wxT("IDB_ANALYZE"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Start/Stop analysis"), _("Start/Stop analysis") );
	m_toolBar1->AddSeparator();
	m_toolBar1->AddTool( ID_PASS, _("tool"), wxBitmap( wxT("IDB_PASS"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Pass"), _("Pass") );
	m_toolBar1->AddTool( ID_SCORE, _("tool"), wxBitmap( wxT("IDB_SCORE"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Score the game"), _("Score the game") );
	m_toolBar1->AddTool( ID_RESIGN, _("tool"), wxBitmap( wxT("IDB_RESIGN"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Resign the game"), _("Resign the game") );
	m_toolBar1->AddSeparator();
	m_toolBar1->AddTool( ID_EXIT, _("Exit"), wxBitmap( wxT("IDB_QUIT"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Exit the program"), _("Exit the program") );
	m_toolBar1->Realize();
	
}

TMainFrame::~TMainFrame()
{
}

BEGIN_EVENT_TABLE( TNewGameDialog, wxDialog )
	EVT_INIT_DIALOG( TNewGameDialog::_wxFB_doInit )
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
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Komi (+0.5)") ), wxHORIZONTAL );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, _("Komi"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticText2->Wrap( -1 );
	sbSizer2->Add( m_staticText2, 1, wxALIGN_CENTER, 5 );
	
	m_spinCtrlKomi = new wxSpinCtrl( this, ID_KOMISPIN, wxT("7"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 15, 0 );
	sbSizer2->Add( m_spinCtrlKomi, 1, wxALIGN_CENTER, 5 );
	
	bSizer9->Add( sbSizer2, 0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 5 );
	
	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Handicap") ), wxHORIZONTAL );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, _("Handicap"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticText3->Wrap( -1 );
	sbSizer3->Add( m_staticText3, 1, wxALIGN_CENTER, 5 );
	
	m_spinCtrlHandicap = new wxSpinCtrl( this, ID_HANDICAPSPIN, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 9, 0 );
	sbSizer3->Add( m_spinCtrlHandicap, 1, wxALIGN_CENTER, 5 );
	
	bSizer9->Add( sbSizer3, 0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 5 );
	
	wxStaticBoxSizer* sbSizer5;
	sbSizer5 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Time for game") ), wxHORIZONTAL );
	
	m_staticText13 = new wxStaticText( this, wxID_ANY, _("Minutes"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticText13->Wrap( -1 );
	sbSizer5->Add( m_staticText13, 1, wxALIGN_CENTER, 5 );
	
	m_spinCtrlTime = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 720, 30 );
	sbSizer5->Add( m_spinCtrlTime, 1, wxALIGN_CENTER, 5 );
	
	bSizer9->Add( sbSizer5, 0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 5 );
	
	bSizer11->Add( bSizer9, 4, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );
	
	wxString m_radioBoxColorChoices[] = { _("Black"), _("White") };
	int m_radioBoxColorNChoices = sizeof( m_radioBoxColorChoices ) / sizeof( wxString );
	m_radioBoxColor = new wxRadioBox( this, wxID_ANY, _("Your color"), wxDefaultPosition, wxDefaultSize, m_radioBoxColorNChoices, m_radioBoxColorChoices, 1, wxRA_SPECIFY_ROWS );
	m_radioBoxColor->SetSelection( 0 );
	bSizer10->Add( m_radioBoxColor, 0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 5 );
	
	wxString m_radioBoxLevelChoices[] = { _("100 simulations"), _("500 simulations"), _("1000 simulations"), _("5000 simulations"), _("10000 simulations"), _("20000 simulations"), _("Unlimited") };
	int m_radioBoxLevelNChoices = sizeof( m_radioBoxLevelChoices ) / sizeof( wxString );
	m_radioBoxLevel = new wxRadioBox( this, wxID_ANY, _("Engine max level"), wxDefaultPosition, wxDefaultSize, m_radioBoxLevelNChoices, m_radioBoxLevelChoices, 1, wxRA_SPECIFY_COLS );
	m_radioBoxLevel->SetSelection( 1 );
	bSizer10->Add( m_radioBoxLevel, 0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 5 );
	
	bSizer11->Add( bSizer10, 5, wxEXPAND, 5 );
	
	bSizer7->Add( bSizer11, 4, wxEXPAND, 5 );
	
	m_sdbSizer1 = new wxStdDialogButtonSizer();
	m_sdbSizer1OK = new wxButton( this, wxID_OK );
	m_sdbSizer1->AddButton( m_sdbSizer1OK );
	m_sdbSizer1Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer1->AddButton( m_sdbSizer1Cancel );
	m_sdbSizer1->Realize();
	bSizer7->Add( m_sdbSizer1, 0, wxALL|wxEXPAND, 2 );
	
	this->SetSizer( bSizer7 );
	this->Layout();
}

TNewGameDialog::~TNewGameDialog()
{
}

BEGIN_EVENT_TABLE( TAboutDialog, wxDialog )
	EVT_INIT_DIALOG( TAboutDialog::_wxFB_doInit )
END_EVENT_TABLE()

TAboutDialog::TAboutDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );
	
	m_staticTextVersion = new wxStaticText( this, wxID_ANY, _("Leela version 0.3.15"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticTextVersion->Wrap( -1 );
	m_staticTextVersion->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer9->Add( m_staticTextVersion, 0, wxALL|wxEXPAND, 10 );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, _("Copyright (C) 2007-2008 Gian-Carlo Pascutto"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	bSizer9->Add( m_staticText5, 0, wxALIGN_CENTER|wxALL, 5 );
	
	m_staticText9 = new wxStaticText( this, wxID_ANY, _("gcp@sjeng.org"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	bSizer9->Add( m_staticText9, 0, wxALIGN_CENTER|wxALL, 5 );
	
	m_hyperlink3 = new wxHyperlinkCtrl( this, wxID_ANY, _("http://www.sjeng.org/leela"), wxT("http://www.sjeng.org/leela"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );
	bSizer9->Add( m_hyperlink3, 0, wxALIGN_CENTER|wxALL, 5 );
	
	m_button1 = new wxButton( this, wxID_OK, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer9->Add( m_button1, 0, wxALIGN_CENTER|wxALL, 5 );
	
	this->SetSizer( bSizer9 );
	this->Layout();
}

TAboutDialog::~TAboutDialog()
{
}

BEGIN_EVENT_TABLE( TNagDialog, wxDialog )
	EVT_INIT_DIALOG( TNagDialog::_wxFB_doInit )
	EVT_BUTTON( wxID_OK, TNagDialog::_wxFB_doOK )
END_EVENT_TABLE()

TNagDialog::TNagDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText8 = new wxStaticText( this, wxID_ANY, _("If you like Leela, you might also like:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	bSizer10->Add( m_staticText8, 0, wxALL, 5 );
	
	m_staticText9 = new wxStaticText( this, wxID_ANY, _("Leela - full version"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	m_staticText9->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer10->Add( m_staticText9, 0, wxALIGN_CENTER|wxALL, 5 );
	
	m_staticText81 = new wxStaticText( this, wxID_ANY, _("including 19 x 19 and top levels"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticText81->Wrap( -1 );
	m_staticText81->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer10->Add( m_staticText81, 0, wxALIGN_CENTER|wxALL, 5 );
	
	m_hyperlink1 = new wxHyperlinkCtrl( this, wxID_ANY, wxEmptyString, wxT("http://www.sjeng.org/leela"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );
	m_hyperlink1->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	bSizer10->Add( m_hyperlink1, 0, wxALIGN_CENTER|wxALL, 5 );
	
	m_staticText10 = new wxStaticText( this, wxID_ANY, _("Deep Sjeng - the chess program"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	m_staticText10->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer10->Add( m_staticText10, 0, wxALIGN_CENTER|wxALL, 5 );
	
	m_hyperlink2 = new wxHyperlinkCtrl( this, wxID_ANY, wxEmptyString, wxT("http://www.sjeng.org/deepsjeng3"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );
	m_hyperlink2->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	bSizer10->Add( m_hyperlink2, 0, wxALIGN_CENTER|wxALL, 5 );
	
	m_button2 = new wxButton( this, wxID_OK, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer10->Add( m_button2, 0, wxALIGN_CENTER|wxALL, 5 );
	
	this->SetSizer( bSizer10 );
	this->Layout();
	
	this->Centre( wxBOTH );
}

TNagDialog::~TNagDialog()
{
}

BEGIN_EVENT_TABLE( TCopyProtectionDialog, wxDialog )
	EVT_BUTTON( wxID_OK, TCopyProtectionDialog::_wxFB_doOK )
END_EVENT_TABLE()

TCopyProtectionDialog::TCopyProtectionDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText12 = new wxStaticText( this, wxID_ANY, _("Please enter your name and serial number:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	bSizer10->Add( m_staticText12, 0, wxALL|wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer1->AddGrowableCol( 0 );
	fgSizer1->AddGrowableCol( 1 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText14 = new wxStaticText( this, wxID_ANY, _("Name"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticText14->Wrap( -1 );
	fgSizer1->Add( m_staticText14, 0, wxALIGN_CENTER|wxALL|wxEXPAND, 5 );
	
	m_textCtrlName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( m_textCtrlName, 1, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL|wxEXPAND, 5 );
	
	m_staticText15 = new wxStaticText( this, wxID_ANY, _("Code"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticText15->Wrap( -1 );
	fgSizer1->Add( m_staticText15, 0, wxALIGN_RIGHT|wxALL|wxEXPAND, 5 );
	
	m_textCtrlCode = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( m_textCtrlCode, 2, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL|wxEXPAND, 5 );
	
	bSizer10->Add( fgSizer1, 1, wxALL|wxEXPAND, 5 );
	
	m_sdbSizer2 = new wxStdDialogButtonSizer();
	m_sdbSizer2OK = new wxButton( this, wxID_OK );
	m_sdbSizer2->AddButton( m_sdbSizer2OK );
	m_sdbSizer2Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer2->AddButton( m_sdbSizer2Cancel );
	m_sdbSizer2->Realize();
	bSizer10->Add( m_sdbSizer2, 0, wxALL|wxEXPAND, 5 );
	
	this->SetSizer( bSizer10 );
	this->Layout();
}

TCopyProtectionDialog::~TCopyProtectionDialog()
{
}

BEGIN_EVENT_TABLE( TClockAdjustDialog, wxDialog )
	EVT_INIT_DIALOG( TClockAdjustDialog::_wxFB_doInit )
	EVT_BUTTON( wxID_CANCEL, TClockAdjustDialog::_wxFB_doCancel )
	EVT_BUTTON( wxID_OK, TClockAdjustDialog::_wxFB_doOK )
END_EVENT_TABLE()

TClockAdjustDialog::TClockAdjustDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Black clock (minutes:seconds)") ), wxHORIZONTAL );
	
	m_spinCtrlBlackMins = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 999, 30 );
	sbSizer4->Add( m_spinCtrlBlackMins, 1, wxALL|wxEXPAND, 5 );
	
	m_spinCtrlBlackSecs = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 59, 0 );
	sbSizer4->Add( m_spinCtrlBlackSecs, 1, wxALL|wxEXPAND, 5 );
	
	bSizer9->Add( sbSizer4, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer6;
	sbSizer6 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("White clock (minutes:seconds)") ), wxHORIZONTAL );
	
	m_spinCtrlWhiteMins = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 999, 30 );
	sbSizer6->Add( m_spinCtrlWhiteMins, 1, wxALL|wxEXPAND, 5 );
	
	m_spinCtrlWhiteSecs = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 59, 0 );
	sbSizer6->Add( m_spinCtrlWhiteSecs, 1, wxALL|wxEXPAND, 5 );
	
	bSizer9->Add( sbSizer6, 1, wxEXPAND, 5 );
	
	m_sdbSizer3 = new wxStdDialogButtonSizer();
	m_sdbSizer3OK = new wxButton( this, wxID_OK );
	m_sdbSizer3->AddButton( m_sdbSizer3OK );
	m_sdbSizer3Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer3->AddButton( m_sdbSizer3Cancel );
	m_sdbSizer3->Realize();
	bSizer9->Add( m_sdbSizer3, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer9 );
	this->Layout();
}

TClockAdjustDialog::~TClockAdjustDialog()
{
}
