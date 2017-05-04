///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
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
	EVT_CLOSE( TMainFrame::_wxFB_doClose )
	EVT_KEY_DOWN( TMainFrame::_wxFB_doKeyDown )
	EVT_PAINT( TMainFrame::_wxFB_doPaint )
	EVT_SIZE( TMainFrame::_wxFB_doResize )
	EVT_MENU( ID_NEWGAME, TMainFrame::_wxFB_doNewGame )
	EVT_MENU( ID_NEWRATED, TMainFrame::_wxFB_doNewRatedGame )
	EVT_MENU( ID_RATEDSIZE, TMainFrame::_wxFB_doSetRatedSize )
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
	EVT_MENU( ID_SETHOME, TMainFrame::_wxFB_doSetMainline )
	EVT_MENU( ID_MAINLINE, TMainFrame::_wxFB_doMainLine )
	EVT_MENU( ID_ANALYSISWINDOWTOGGLE, TMainFrame::_wxFB_doShowHideAnalysisWindow )
	EVT_MENU( ID_MOVE_PROBABILITIES, TMainFrame::_wxFB_doToggleProbabilities )
	EVT_MENU( ID_BEST_MOVES, TMainFrame::_wxFB_doToggleBestMoves )
	EVT_MENU( ID_SHOWTERRITORY, TMainFrame::_wxFB_doToggleTerritory )
	EVT_MENU( ID_SHOWMOYO, TMainFrame::_wxFB_doToggleMoyo )
	EVT_MENU( ID_SETTINGS_MENU, TMainFrame::_wxFB_doSettingsDialog )
	EVT_MENU( ID_ADJUSTCLOCKS, TMainFrame::_wxFB_doAdjustClocks )
	EVT_MENU( ID_HELPRULES, TMainFrame::_wxFB_doGoRules )
	EVT_MENU( ID_HOMEPAGE, TMainFrame::_wxFB_doHomePage )
	EVT_MENU( ID_HELPABOUT, TMainFrame::_wxFB_doHelpAbout )
END_EVENT_TABLE()

TMainFrame::TMainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxFrame( parent, id, title, pos, size, style, name )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	m_panelBoard = new TBoardPanel( this, ID_BOARDPANEL, wxDefaultPosition, wxSize( -1,-1 ), wxFULL_REPAINT_ON_RESIZE|wxTAB_TRAVERSAL|wxWANTS_CHARS );
	bSizer2->Add( m_panelBoard, 1, wxEXPAND | wxALL, 1 );
	
	
	this->SetSizer( bSizer2 );
	this->Layout();
	m_statusBar = this->CreateStatusBar( 2, wxST_SIZEGRIP|wxWANTS_CHARS, ID_DEFAULT );
	m_menubar1 = new wxMenuBar( 0 );
	m_menu1 = new wxMenu();
	wxMenuItem* menuItemNewGame;
	menuItemNewGame = new wxMenuItem( m_menu1, ID_NEWGAME, wxString( _("&New Game...") ) + wxT('\t') + wxT("Ctrl-N"), _("Start a new game"), wxITEM_NORMAL );
	m_menu1->Append( menuItemNewGame );
	
	wxMenuItem* menuItemNewRated;
	menuItemNewRated = new wxMenuItem( m_menu1, ID_NEWRATED, wxString( _("New &Rated Game") ) + wxT('\t') + wxT("Ctrl-R"), _("Starts a new rated game"), wxITEM_NORMAL );
	m_menu1->Append( menuItemNewRated );
	
	wxMenuItem* m_menuItemRatedSize;
	m_menuItemRatedSize = new wxMenuItem( m_menu1, ID_RATEDSIZE, wxString( _("Set Rated &Board Size...") ) + wxT('\t') + wxT("Ctrl-B"), _("Change the board size for rated games"), wxITEM_NORMAL );
	m_menu1->Append( m_menuItemRatedSize );
	
	m_menu1->AppendSeparator();
	
	wxMenuItem* menuItem11;
	menuItem11 = new wxMenuItem( m_menu1, ID_OPEN, wxString( _("&Open Game...") ) + wxT('\t') + wxT("Ctrl-O"), _("Opens a game from disk"), wxITEM_NORMAL );
	m_menu1->Append( menuItem11 );
	
	wxMenuItem* menuItem12;
	menuItem12 = new wxMenuItem( m_menu1, ID_SAVE, wxString( _("&Save Game...") ) + wxT('\t') + wxT("Ctrl-S"), _("Save a game to disk"), wxITEM_NORMAL );
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
	menuItem131 = new wxMenuItem( m_menu2, ID_BACK10, wxString( _("Go &Back 10 Moves") ) + wxT('\t') + wxT("Alt-B"), _("Undo 10 moves"), wxITEM_NORMAL );
	m_menu2->Append( menuItem131 );
	
	wxMenuItem* menuItem141;
	menuItem141 = new wxMenuItem( m_menu2, ID_FWD10, wxString( _("Go For&ward 10 Moves") ) + wxT('\t') + wxT("Alt-F"), _("Forward 10 moves"), wxITEM_NORMAL );
	m_menu2->Append( menuItem141 );
	
	m_menu2->AppendSeparator();
	
	wxMenuItem* menuItem18;
	menuItem18 = new wxMenuItem( m_menu2, ID_FORCE, wxString( _("Force &Computer Move") ) + wxT('\t') + wxT("Ctrl-F"), _("Force the computer to move now"), wxITEM_NORMAL );
	m_menu2->Append( menuItem18 );
	
	m_menu2->AppendSeparator();
	
	wxMenuItem* m_menuItem24;
	m_menuItem24 = new wxMenuItem( m_menu2, ID_PASS, wxString( _("&Pass") ) + wxT('\t') + wxT("Alt-P"), wxEmptyString, wxITEM_NORMAL );
	m_menu2->Append( m_menuItem24 );
	
	wxMenuItem* menuItem20;
	menuItem20 = new wxMenuItem( m_menu2, ID_RESIGN, wxString( _("&Resign") ) + wxT('\t') + wxT("Alt-R"), _("Resign the game"), wxITEM_NORMAL );
	m_menu2->Append( menuItem20 );
	
	m_menu2->AppendSeparator();
	
	wxMenuItem* menuItem5;
	menuItem5 = new wxMenuItem( m_menu2, ID_SCORE, wxString( _("&Score Game") ) + wxT('\t') + wxT("Alt-S"), _("Score the position"), wxITEM_NORMAL );
	m_menu2->Append( menuItem5 );
	
	m_menubar1->Append( m_menu2, _("&Game") ); 
	
	m_menuAnalyze = new wxMenu();
	wxMenuItem* menuItemAnalyze;
	menuItemAnalyze = new wxMenuItem( m_menuAnalyze, ID_ANALYZE, wxString( _("Start/Stop &Analysis") ) + wxT('\t') + wxT("F2"), _("Start analyzing"), wxITEM_NORMAL );
	m_menuAnalyze->Append( menuItemAnalyze );
	
	m_menuAnalyze->AppendSeparator();
	
	wxMenuItem* m_menuItemStoreMainline;
	m_menuItemStoreMainline = new wxMenuItem( m_menuAnalyze, ID_SETHOME, wxString( _("&Store Mainline") ) + wxT('\t') + wxT("Ctrl-M"), _("Store this variation as the mainline"), wxITEM_NORMAL );
	m_menuAnalyze->Append( m_menuItemStoreMainline );
	
	wxMenuItem* m_menuItemMainline;
	m_menuItemMainline = new wxMenuItem( m_menuAnalyze, ID_MAINLINE, wxString( _("Revert to &Mainline") ) + wxT('\t') + wxT("Alt-M"), _("Revert board position to mainline"), wxITEM_NORMAL );
	m_menuAnalyze->Append( m_menuItemMainline );
	
	m_menuAnalyze->AppendSeparator();
	
	wxMenuItem* m_menuItemAnalysisWindow;
	m_menuItemAnalysisWindow = new wxMenuItem( m_menuAnalyze, ID_ANALYSISWINDOWTOGGLE, wxString( _("Analysis &Window") ) + wxT('\t') + wxT("Ctrl-A"), wxEmptyString, wxITEM_CHECK );
	m_menuAnalyze->Append( m_menuItemAnalysisWindow );
	
	m_menubar1->Append( m_menuAnalyze, _("&Analyze") ); 
	
	m_menuTools = new wxMenu();
	wxMenuItem* m_menuItemMoveProbabilities;
	m_menuItemMoveProbabilities = new wxMenuItem( m_menuTools, ID_MOVE_PROBABILITIES, wxString( _("Show Network &Probabilities") ) + wxT('\t') + wxT("F3"), _("Show the likelihood of each move being played by a professional player"), wxITEM_CHECK );
	m_menuTools->Append( m_menuItemMoveProbabilities );
	
	wxMenuItem* m_menuItemBestMoves;
	m_menuItemBestMoves = new wxMenuItem( m_menuTools, ID_BEST_MOVES, wxString( _("Show &Best Moves") ) + wxT('\t') + wxT("F4"), _("Color the best moves on the board"), wxITEM_CHECK );
	m_menuTools->Append( m_menuItemBestMoves );
	
	wxMenuItem* menuItem15;
	menuItem15 = new wxMenuItem( m_menuTools, ID_SHOWTERRITORY, wxString( _("Show &Territory") ) + wxT('\t') + wxT("F5"), _("Show Territory"), wxITEM_CHECK );
	m_menuTools->Append( menuItem15 );
	
	wxMenuItem* menuItem16;
	menuItem16 = new wxMenuItem( m_menuTools, ID_SHOWMOYO, wxString( _("Show &Moyo") ) + wxT('\t') + wxT("F6"), _("Show Moyo"), wxITEM_CHECK );
	m_menuTools->Append( menuItem16 );
	
	m_menuTools->AppendSeparator();
	
	wxMenuItem* m_menuItem28;
	m_menuItem28 = new wxMenuItem( m_menuTools, ID_SETTINGS_MENU, wxString( _("S&ettings...") ) + wxT('\t') + wxT("Ctrl-E"), wxEmptyString, wxITEM_NORMAL );
	m_menuTools->Append( m_menuItem28 );
	
	m_menuTools->AppendSeparator();
	
	wxMenuItem* m_menuItemAdjustClocks;
	m_menuItemAdjustClocks = new wxMenuItem( m_menuTools, ID_ADJUSTCLOCKS, wxString( _("&Adjust Clocks...") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuTools->Append( m_menuItemAdjustClocks );
	
	m_menubar1->Append( m_menuTools, _("&Tools") ); 
	
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
	m_tool1 = m_toolBar1->AddTool( ID_NEWGAME, _("New Game"), wxBitmap( wxT("IDB_NEWGAME"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Start a new game"), _("Start a new game"), NULL ); 
	
	m_tool12 = m_toolBar1->AddTool( ID_NEWRATED, _("New Rated Game"), wxBitmap( wxT("IDB_NEWRATED"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Start a new rated game"), _("Start a new rated game"), NULL ); 
	
	m_tool4 = m_toolBar1->AddTool( ID_OPEN, _("Load Game"), wxBitmap( wxT("IDB_OPEN"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Load a game"), _("Load a game"), NULL ); 
	
	m_tool5 = m_toolBar1->AddTool( ID_SAVE, _("Save"), wxBitmap( wxT("IDB_SAVEAS"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Save the game"), _("Save the game"), NULL ); 
	
	m_toolBar1->AddSeparator(); 
	
	m_tool10 = m_toolBar1->AddTool( ID_BACK10, _("Go back 10 moves"), wxBitmap( wxT("IDB_BACKWARD"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Go back 10 moves"), _("Go back 10 moves"), NULL ); 
	
	m_tool13 = m_toolBar1->AddTool( ID_UNDO, _("Undo"), wxBitmap( wxT("IDB_UNDO"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Take back one move"), _("Take back one move"), NULL ); 
	
	m_tool15 = m_toolBar1->AddTool( ID_REDO, _("Forward"), wxBitmap( wxT("IDB_REDO"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Go forward one move"), _("Go forward one move"), NULL ); 
	
	m_tool9 = m_toolBar1->AddTool( ID_FWD10, _("Forward 10"), wxBitmap( wxT("IDB_FORWARD"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Go forward 10 moves"), _("Go forward 10 moves"), NULL ); 
	
	m_toolBar1->AddSeparator(); 
	
	m_toolForce = m_toolBar1->AddTool( ID_FORCE, _("Force computer move"), wxBitmap( wxT("IDB_FORCE"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Force computer move"), _("Force computer move"), NULL ); 
	
	m_toolSetHome = m_toolBar1->AddTool( ID_SETHOME, _("Store Mainline"), wxBitmap( wxT("IDB_SETHOME"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Stores this variation as the mainline"), _("Stores this variation as the mainline"), NULL ); 
	
	m_toolMainline = m_toolBar1->AddTool( ID_MAINLINE, _("Revert to mainline"), wxBitmap( wxT("IDB_PARENT"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Revert to mainline"), _("Revert to mainline"), NULL ); 
	
	m_toolAnalyze = m_toolBar1->AddTool( ID_ANALYZE, _("tool"), wxBitmap( wxT("IDB_ANALYZE"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Start/Stop analysis"), _("Start/Stop analysis"), NULL ); 
	
	m_toolBar1->AddSeparator(); 
	
	m_tool2 = m_toolBar1->AddTool( ID_PASS, _("tool"), wxBitmap( wxT("IDB_PASS"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Pass"), _("Pass"), NULL ); 
	
	m_tool3 = m_toolBar1->AddTool( ID_SCORE, _("tool"), wxBitmap( wxT("IDB_SCORE"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Score the game"), _("Score the game"), NULL ); 
	
	m_tool131 = m_toolBar1->AddTool( ID_RESIGN, _("tool"), wxBitmap( wxT("IDB_RESIGN"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Resign the game"), _("Resign the game"), NULL ); 
	
	m_toolBar1->AddSeparator(); 
	
	m_tool11 = m_toolBar1->AddTool( ID_EXIT, _("Exit"), wxBitmap( wxT("IDB_QUIT"), wxBITMAP_TYPE_RESOURCE ), wxNullBitmap, wxITEM_NORMAL, _("Exit the program"), _("Exit the program"), NULL ); 
	
	m_toolBar1->Realize(); 
	
}

TMainFrame::~TMainFrame()
{
}

BEGIN_EVENT_TABLE( TNewGameDialog, wxDialog )
	EVT_INIT_DIALOG( TNewGameDialog::_wxFB_doInit )
	EVT_RADIOBOX( wxID_ANY, TNewGameDialog::_wxFB_doRadioBox )
	EVT_SPINCTRL( ID_HANDICAPSPIN, TNewGameDialog::_wxFB_doHandicapUpdate )
	EVT_BUTTON( wxID_CANCEL, TNewGameDialog::_wxFB_doCancel )
	EVT_BUTTON( wxID_OK, TNewGameDialog::_wxFB_doOK )
END_EVENT_TABLE()

TNewGameDialog::TNewGameDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );
	
	wxString m_radioBoxBoardSizeChoices[] = { _("7 x 7"), _("9 x 9"), _("13 x 13"), _("17 x 17"), _("19 x 19"), _("25 x 25") };
	int m_radioBoxBoardSizeNChoices = sizeof( m_radioBoxBoardSizeChoices ) / sizeof( wxString );
	m_radioBoxBoardSize = new wxRadioBox( this, wxID_ANY, _("Board size"), wxDefaultPosition, wxDefaultSize, m_radioBoxBoardSizeNChoices, m_radioBoxBoardSizeChoices, 3, wxRA_SPECIFY_ROWS );
	m_radioBoxBoardSize->SetSelection( 4 );
	bSizer12->Add( m_radioBoxBoardSize, 0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 5 );
	
	
	bSizer9->Add( bSizer12, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Komi (+0.5)") ), wxHORIZONTAL );
	
	m_spinCtrlKomi = new wxSpinCtrl( sbSizer2->GetStaticBox(), ID_KOMISPIN, wxT("7"), wxDefaultPosition, wxSize( 100,-1 ), wxSP_ARROW_KEYS, 0, 15, 0 );
	sbSizer2->Add( m_spinCtrlKomi, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticText2 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, _("Komi"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticText2->Wrap( -1 );
	sbSizer2->Add( m_staticText2, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer9->Add( sbSizer2, 0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 5 );
	
	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Handicap") ), wxHORIZONTAL );
	
	m_spinCtrlHandicap = new wxSpinCtrl( sbSizer3->GetStaticBox(), ID_HANDICAPSPIN, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), wxSP_ARROW_KEYS, 0, 100, 0 );
	sbSizer3->Add( m_spinCtrlHandicap, 0, wxALIGN_CENTER|wxALL, 5 );
	
	m_staticText3 = new wxStaticText( sbSizer3->GetStaticBox(), wxID_ANY, _("Handicap"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticText3->Wrap( -1 );
	sbSizer3->Add( m_staticText3, 0, wxALIGN_CENTER|wxALL, 5 );
	
	
	bSizer9->Add( sbSizer3, 0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 5 );
	
	wxStaticBoxSizer* sbSizer5;
	sbSizer5 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Time for game") ), wxHORIZONTAL );
	
	m_spinCtrlTime = new wxSpinCtrl( sbSizer5->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), wxSP_ARROW_KEYS, 1, 720, 90 );
	sbSizer5->Add( m_spinCtrlTime, 0, wxALIGN_CENTER|wxALL, 5 );
	
	m_staticText13 = new wxStaticText( sbSizer5->GetStaticBox(), wxID_ANY, _("Minutes"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticText13->Wrap( -1 );
	sbSizer5->Add( m_staticText13, 0, wxALIGN_CENTER|wxALL, 5 );
	
	
	bSizer9->Add( sbSizer5, 0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 5 );
	
	
	bSizer11->Add( bSizer9, 0, wxALL|wxEXPAND, 5 );
	
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
	m_radioBoxLevel->SetSelection( 6 );
	bSizer10->Add( m_radioBoxLevel, 0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 5 );
	
	wxStaticBoxSizer* sbSizerEngineSettings;
	sbSizerEngineSettings = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Engine settings (19 x 19)") ), wxVERTICAL );
	
	m_checkNeuralNet = new wxCheckBox( sbSizerEngineSettings->GetStaticBox(), wxID_ANY, _("Use Neural Network"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkNeuralNet->SetValue(true); 
	sbSizerEngineSettings->Add( m_checkNeuralNet, 0, wxALL, 5 );
	
	
	bSizer10->Add( sbSizerEngineSettings, 0, wxEXPAND, 5 );
	
	
	bSizer11->Add( bSizer10, 0, wxEXPAND, 5 );
	
	
	bSizer7->Add( bSizer11, 1, wxEXPAND, 5 );
	
	m_sdbSizer1 = new wxStdDialogButtonSizer();
	m_sdbSizer1OK = new wxButton( this, wxID_OK );
	m_sdbSizer1->AddButton( m_sdbSizer1OK );
	m_sdbSizer1Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer1->AddButton( m_sdbSizer1Cancel );
	m_sdbSizer1->Realize();
	
	bSizer7->Add( m_sdbSizer1, 0, wxALIGN_LEFT|wxALL, 2 );
	
	
	this->SetSizer( bSizer7 );
	this->Layout();
	bSizer7->Fit( this );
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
	
	m_staticTextVersion = new wxStaticText( this, wxID_ANY, _("Leela version 0.9.1"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticTextVersion->Wrap( -1 );
	m_staticTextVersion->SetFont( wxFont( 11, 70, 90, 92, false, wxEmptyString ) );
	
	bSizer9->Add( m_staticTextVersion, 0, wxALL|wxEXPAND, 10 );
	
	m_staticTextEngine = new wxStaticText( this, wxID_ANY, _("OpenCL/BLAS Engine goes here and can be a very long string"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticTextEngine->Wrap( 400 );
	bSizer9->Add( m_staticTextEngine, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, _("Copyright (C) 2007-2017 Gian-Carlo Pascutto"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticText5->Wrap( -1 );
	bSizer9->Add( m_staticText5, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText9 = new wxStaticText( this, wxID_ANY, _("gcp@sjeng.org"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticText9->Wrap( -1 );
	bSizer9->Add( m_staticText9, 0, wxALL|wxEXPAND, 5 );
	
	m_hyperlink3 = new wxHyperlinkCtrl( this, wxID_ANY, _("https://sjeng.org/leela"), wxT("https://www.sjeng.org/leela"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );
	bSizer9->Add( m_hyperlink3, 0, wxALIGN_CENTER|wxALL, 5 );
	
	m_button1 = new wxButton( this, wxID_OK, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer9->Add( m_button1, 0, wxALIGN_CENTER|wxALL, 5 );
	
	
	this->SetSizer( bSizer9 );
	this->Layout();
	bSizer9->Fit( this );
}

TAboutDialog::~TAboutDialog()
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
	
	m_spinCtrlBlackMins = new wxSpinCtrl( sbSizer4->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxSP_ARROW_KEYS, 0, 999, 30 );
	sbSizer4->Add( m_spinCtrlBlackMins, 1, wxALL|wxEXPAND, 5 );
	
	m_spinCtrlBlackSecs = new wxSpinCtrl( sbSizer4->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 59, 0 );
	sbSizer4->Add( m_spinCtrlBlackSecs, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer9->Add( sbSizer4, 0, wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer6;
	sbSizer6 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("White clock (minutes:seconds)") ), wxHORIZONTAL );
	
	m_spinCtrlWhiteMins = new wxSpinCtrl( sbSizer6->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxSP_ARROW_KEYS, 0, 999, 30 );
	sbSizer6->Add( m_spinCtrlWhiteMins, 1, wxALL|wxEXPAND, 5 );
	
	m_spinCtrlWhiteSecs = new wxSpinCtrl( sbSizer6->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 59, 0 );
	sbSizer6->Add( m_spinCtrlWhiteSecs, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer9->Add( sbSizer6, 0, wxALL|wxEXPAND, 5 );
	
	m_sdbSizer3 = new wxStdDialogButtonSizer();
	m_sdbSizer3OK = new wxButton( this, wxID_OK );
	m_sdbSizer3->AddButton( m_sdbSizer3OK );
	m_sdbSizer3Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer3->AddButton( m_sdbSizer3Cancel );
	m_sdbSizer3->Realize();
	
	bSizer9->Add( m_sdbSizer3, 0, wxALIGN_CENTER|wxALL, 5 );
	
	
	this->SetSizer( bSizer9 );
	this->Layout();
	bSizer9->Fit( this );
}

TClockAdjustDialog::~TClockAdjustDialog()
{
}

BEGIN_EVENT_TABLE( TRatedSizeDialog, wxDialog )
	EVT_BUTTON( ID_SIZE9, TRatedSizeDialog::_wxFB_doSize9 )
	EVT_BUTTON( ID_SIZE19, TRatedSizeDialog::_wxFB_doSize19 )
END_EVENT_TABLE()

TRatedSizeDialog::TRatedSizeDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonSize9 = new wxButton( this, ID_SIZE9, _("9 x 9"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonSize9->SetDefault(); 
	bSizer10->Add( m_buttonSize9, 0, wxALL, 5 );
	
	m_buttonSize19 = new wxButton( this, ID_SIZE19, _("19 x 19"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer10->Add( m_buttonSize19, 0, wxALL, 5 );
	
	
	this->SetSizer( bSizer10 );
	this->Layout();
	bSizer10->Fit( this );
}

TRatedSizeDialog::~TRatedSizeDialog()
{
}

TCalculateDialog::TCalculateDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	m_staticTextCalculating = new wxStaticText( this, wxID_ANY, _("Calculating, please hold..."), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticTextCalculating->Wrap( -1 );
	bSizer11->Add( m_staticTextCalculating, 1, wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer11 );
	this->Layout();
}

TCalculateDialog::~TCalculateDialog()
{
}

BEGIN_EVENT_TABLE( TAnalysisWindow, wxFrame )
	EVT_CLOSE( TAnalysisWindow::_wxFB_doClose )
	EVT_GRID_CELL_LEFT_CLICK( TAnalysisWindow::_wxFB_doLeftClick )
	EVT_GRID_CELL_LEFT_DCLICK( TAnalysisWindow::_wxFB_doDeselect )
	EVT_GRID_CELL_RIGHT_CLICK( TAnalysisWindow::_wxFB_doDeselect )
END_EVENT_TABLE()

TAnalysisWindow::TAnalysisWindow( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );
	
	m_panel3 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer121;
	bSizer121 = new wxBoxSizer( wxVERTICAL );
	
	m_moveGrid = new wxGrid( m_panel3, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	m_moveGrid->CreateGrid( 8, 6 );
	m_moveGrid->EnableEditing( false );
	m_moveGrid->EnableGridLines( true );
	m_moveGrid->EnableDragGridSize( false );
	m_moveGrid->SetMargins( 0, 0 );
	
	// Columns
	m_moveGrid->AutoSizeColumns();
	m_moveGrid->EnableDragColMove( false );
	m_moveGrid->EnableDragColSize( true );
	m_moveGrid->SetColLabelSize( 30 );
	m_moveGrid->SetColLabelValue( 0, _("Move") );
	m_moveGrid->SetColLabelValue( 1, _("Effort%") );
	m_moveGrid->SetColLabelValue( 2, _("Simulations") );
	m_moveGrid->SetColLabelValue( 3, _("Win%") );
	m_moveGrid->SetColLabelValue( 4, _("Net Prob%") );
	m_moveGrid->SetColLabelValue( 5, _("PV") );
	m_moveGrid->SetColLabelAlignment( wxALIGN_LEFT, wxALIGN_CENTRE );
	
	// Rows
	m_moveGrid->AutoSizeRows();
	m_moveGrid->EnableDragRowSize( false );
	m_moveGrid->SetRowLabelSize( 0 );
	m_moveGrid->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	m_moveGrid->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer121->Add( m_moveGrid, 1, wxEXPAND, 5 );
	
	
	m_panel3->SetSizer( bSizer121 );
	m_panel3->Layout();
	bSizer121->Fit( m_panel3 );
	bSizer12->Add( m_panel3, 1, wxEXPAND | wxALL, 5 );
	
	
	this->SetSizer( bSizer12 );
	this->Layout();
	
	this->Centre( wxBOTH );
}

TAnalysisWindow::~TAnalysisWindow()
{
}

BEGIN_EVENT_TABLE( TSettingsDialog, wxDialog )
	EVT_INIT_DIALOG( TSettingsDialog::_wxFB_doInit )
	EVT_BUTTON( wxID_CANCEL, TSettingsDialog::_wxFB_doCancel )
	EVT_BUTTON( wxID_OK, TSettingsDialog::_wxFB_doOK )
END_EVENT_TABLE()

TSettingsDialog::TSettingsDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxVERTICAL );
	
	m_panel4 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer7;
	sbSizer7 = new wxStaticBoxSizer( new wxStaticBox( m_panel4, wxID_ANY, _("Engine Settings") ), wxVERTICAL );
	
	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 0, 2, 0, 0 );
	
	m_checkBoxPasses = new wxCheckBox( sbSizer7->GetStaticBox(), ID_PASSTOGGLE, _("Allow Passes"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBoxPasses->SetValue(true); 
	gSizer1->Add( m_checkBoxPasses, 0, wxALL, 5 );
	
	m_checkBoxPondering = new wxCheckBox( sbSizer7->GetStaticBox(), ID_PONDERTOGGLE, _("Pondering"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBoxPondering->SetValue(true); 
	gSizer1->Add( m_checkBoxPondering, 0, wxALL, 5 );
	
	m_checkBoxResignations = new wxCheckBox( sbSizer7->GetStaticBox(), ID_RESIGNTOGGLE, _("Resignations"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBoxResignations->SetValue(true); 
	gSizer1->Add( m_checkBoxResignations, 0, wxALL, 5 );
	
	m_checkBoxNeuralNet = new wxCheckBox( sbSizer7->GetStaticBox(), ID_NETWORKTOGGLE, _("Neural Networks"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBoxNeuralNet->SetValue(true); 
	gSizer1->Add( m_checkBoxNeuralNet, 0, wxALL, 5 );
	
	
	sbSizer7->Add( gSizer1, 1, wxEXPAND, 5 );
	
	
	bSizer15->Add( sbSizer7, 0, wxBOTTOM|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer9;
	sbSizer9 = new wxStaticBoxSizer( new wxStaticBox( m_panel4, wxID_ANY, _("Interface Settings") ), wxVERTICAL );
	
	m_checkBoxSound = new wxCheckBox( sbSizer9->GetStaticBox(), ID_SOUNDSWITCH, _("Sound"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBoxSound->SetValue(true); 
	sbSizer9->Add( m_checkBoxSound, 0, wxALL, 5 );
	
	m_checkBoxDPIScaling = new wxCheckBox( sbSizer9->GetStaticBox(), ID_DPISCALING, _("Allow DPI Scaling (needs restart)"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer9->Add( m_checkBoxDPIScaling, 0, wxALL, 5 );
	
	
	bSizer15->Add( sbSizer9, 0, wxBOTTOM|wxEXPAND, 5 );
	
	m_sdbSizer3 = new wxStdDialogButtonSizer();
	m_sdbSizer3OK = new wxButton( m_panel4, wxID_OK );
	m_sdbSizer3->AddButton( m_sdbSizer3OK );
	m_sdbSizer3Cancel = new wxButton( m_panel4, wxID_CANCEL );
	m_sdbSizer3->AddButton( m_sdbSizer3Cancel );
	m_sdbSizer3->Realize();
	
	bSizer15->Add( m_sdbSizer3, 0, wxEXPAND, 5 );
	
	
	m_panel4->SetSizer( bSizer15 );
	m_panel4->Layout();
	bSizer15->Fit( m_panel4 );
	bSizer13->Add( m_panel4, 1, wxEXPAND | wxALL, 5 );
	
	
	this->SetSizer( bSizer13 );
	this->Layout();
	bSizer13->Fit( this );
	
	this->Centre( wxBOTH );
}

TSettingsDialog::~TSettingsDialog()
{
}

BEGIN_EVENT_TABLE( TScoreDialog, wxDialog )
	EVT_BUTTON( wxID_ANY, TScoreDialog::_wxFB_doAccept )
	EVT_BUTTON( wxID_ANY, TScoreDialog::_wxFB_doDispute )
END_EVENT_TABLE()

TScoreDialog::TScoreDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxVERTICAL );
	
	m_panel4 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxVERTICAL );
	
	m_staticTextScore = new wxStaticText( m_panel4, wxID_ANY, _("Final Score:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextScore->Wrap( -1 );
	bSizer17->Add( m_staticTextScore, 1, wxALL|wxEXPAND, 5 );
	
	m_staticTextMessage = new wxStaticText( m_panel4, wxID_ANY, _("Black wins by 0.0"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticTextMessage->Wrap( -1 );
	bSizer17->Add( m_staticTextMessage, 1, wxALL|wxEXPAND, 5 );
	
	m_staticTextConfidence = new wxStaticText( m_panel4, wxID_ANY, _("I'm fairly sure I scored this correctly."), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextConfidence->Wrap( -1 );
	bSizer17->Add( m_staticTextConfidence, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer16->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonOK = new wxButton( m_panel4, wxID_ANY, _("&Accept"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonOK->SetDefault(); 
	bSizer16->Add( m_buttonOK, 0, wxALL|wxEXPAND, 5 );
	
	m_buttonDispute = new wxButton( m_panel4, wxID_ANY, _("&Play On"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer16->Add( m_buttonDispute, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer17->Add( bSizer16, 1, wxALL|wxEXPAND, 5 );
	
	
	m_panel4->SetSizer( bSizer17 );
	m_panel4->Layout();
	bSizer17->Fit( m_panel4 );
	bSizer15->Add( m_panel4, 1, wxEXPAND | wxALL, 5 );
	
	
	this->SetSizer( bSizer15 );
	this->Layout();
	
	this->Centre( wxBOTH );
}

TScoreDialog::~TScoreDialog()
{
}
