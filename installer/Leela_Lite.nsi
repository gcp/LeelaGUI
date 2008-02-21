!define VERSION "0.3.8.0"
!define VERSIONNAME "0.3.8"

;
; General options
;
	CRCCheck                on
	SetCompressor           zlib
	SetCompress             auto
	SetDatablockOptimize    on
	InstallColors           /windows
	AutoCloseWindow         false
	SetDateSave             on
	WindowIcon              on
	XPStyle                 on
	BrandingText            "Leela lite ${VERSIONNAME}"
	UninstallCaption        "Leela lite ${VERSIONNAME} Uninstall"
	ShowUninstDetails       hide
	ShowInstDetails         hide
	RequestExecutionLevel   highest

;
; includes
;
!include LogicLib.nsh
!include MUI.nsh
!include WinVer.nsh
!include x64.nsh

;
; Main settings
;
	Name "Leela lite"
	OutFile "setupLeelaLite.exe"

;
; File info options
;
	VIProductVersion "${VERSION}"
	VIAddVersionKey "FileDescription" "Leela lite installer"
	VIAddVersionKey "ProductName" "Leela lite"
	VIAddVersionKey "CompanyName" "Sjeng.Org"
	VIAddVersionKey "LegalCopyright" "© Gian-Carlo Pascutto. All rights reserved."
	VIAddVersionKey "FileVersion" "${VERSION}"
 
;
; Modern UI options
;
	!define MUI_PRODUCT "Leela lite"
	!define MUI_FILE "LeelaLite"

;Variables

	Var MUI_TEMP
	Var STARTMENU_FOLDER
	Var ADMINRIGHTS		
		
;
;Get installation folder from registry if available
;
	InstallDirRegKey HKCU "Software\Leelalite" ""
	InstallDir "$PROGRAMFILES\${MUI_PRODUCT}"

;
;Define page settings
;
	!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\modern-install-full.ico"
	!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall-full.ico"
	
	!define MUI_INSTALLCOLORS /windows
	!define MUI_LICENSEBKCOLOR /windows
	!define MUI_PROGRESSBAR smooth
	!define MUI_ABORTWARNING
	!define MUI_UNINSTALLER
	!define MUI_UNCONFIRMPAGE
	!define MUI_FINISHPAGE  
	!define MUI_DIRECTORYPAGE
	
; 
; Welcome page
;
	!insertmacro MUI_PAGE_WELCOME
	!insertmacro MUI_PAGE_LICENSE license_lite.rtf
	!insertmacro MUI_PAGE_DIRECTORY

;
;Start Menu Folder Page Configuration
;
	!define MUI_STARTMENUPAGE_REGISTRY_ROOT "HKCU" 
	!define MUI_STARTMENUPAGE_REGISTRY_KEY "Software\Leelalite" 
	!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "Start Menu Folder"
	  
	!insertmacro MUI_PAGE_STARTMENU Application $STARTMENU_FOLDER

;
;Remaining steps
;
	!insertmacro MUI_PAGE_INSTFILES
	!insertmacro MUI_PAGE_FINISH
	!insertmacro MUI_UNPAGE_CONFIRM
	!insertmacro MUI_UNPAGE_INSTFILES

;
; Language files
;
	!insertmacro MUI_LANGUAGE "English"


Function .onInit
	;
	; First, check our permissions
	;

	ClearErrors	
	UserInfo::GetAccountType
	IfErrors use_program_files  # Win9x
	Pop $1
	StrCmp $1 "Admin" use_program_files
	StrCmp $1 "Power" use_program_files
	StrCmp $1 ""      use_program_files
	StrCmp $1 "User"  use_user_dir	
	StrCmp $1 "Guest" use_user_dir	

  use_user_dir:
    StrCpy $INSTDIR "$DOCUMENTS\${MUI_PRODUCT}"    
    SetShellVarContext current
    StrCpy $ADMINRIGHTS "No"
    Goto end_checks

  use_program_files:    
    SetShellVarContext all
    StrCpy $ADMINRIGHTS "Yes"    

  end_checks:

FunctionEnd

Function un.onInit
	;
	; First, check our permissions
	;

	ClearErrors	
	UserInfo::GetAccountType
	IfErrors use_program_files  # Win9x
	Pop $1
	StrCmp $1 "Admin" use_program_files
	StrCmp $1 "Power" use_program_files
	StrCmp $1 ""      use_program_files
	StrCmp $1 "User"  use_user_dir	
	StrCmp $1 "Guest" use_user_dir	

  use_user_dir:
    StrCpy $INSTDIR "$DOCUMENTS\${MUI_PRODUCT}"    
    SetShellVarContext current
    StrCpy $ADMINRIGHTS "No"
    Goto end_checks

  use_program_files:    
    SetShellVarContext all
    StrCpy $ADMINRIGHTS "Yes"    

  end_checks:
FunctionEnd

!include "Sections.nsh"  
    
Section "-Leela lite Installation" 		  			

	SetOutPath $INSTDIR
	
	File "bin\${MUI_FILE}.exe"  	
		  		  		
	File "bin\Leela Homepage.url"  		
	
	;create desktop shortcut
	CreateShortCut "$DESKTOP\${MUI_PRODUCT}.lnk" "$INSTDIR\${MUI_FILE}.exe" ""
	
	 ;Store installation folder
	WriteRegStr HKCU "Software\Leelalite" "" $INSTDIR
	
	;Create uninstaller
	WriteUninstaller "$INSTDIR\Uninstall.exe"
	
	!insertmacro MUI_STARTMENU_WRITE_BEGIN Application
	
	;Create shortcuts
	CreateDirectory "$SMPROGRAMS\$STARTMENU_FOLDER"
	CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\${MUI_PRODUCT}.lnk" "$INSTDIR\${MUI_FILE}.exe"  
	CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\Leela Homepage.lnk" "$INSTDIR\Leela Homepage.url" \
	                "" "" 0 SW_SHOWNORMAL \
                    "" "http://www.sjeng.org/leela"
	CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\Uninstall.lnk" "$INSTDIR\Uninstall.exe"
	
	!insertmacro MUI_STARTMENU_WRITE_END			
	
	WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela lite ${VERSIONNAME}" \
	                  "DisplayName" "Leela lite - the Go Program"
	WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela lite ${VERSIONNAME}" \
	                 "UninstallString" "$INSTDIR\Uninstall.exe"
	WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela lite ${VERSIONNAME}" \
	                 "InstallLocation" "$INSTDIR"                         
	WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela lite ${VERSIONNAME}" \
	                 "Publisher" "Sjeng.Org"                         
	WriteRegDWORD HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela lite ${VERSIONNAME}" \
	                   "EstimatedSize" 647
	WriteRegDWORD HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela lite ${VERSIONNAME}" \
	                   "NoModify" 1                         
	WriteRegDWORD HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela lite ${VERSIONNAME}" \
	                   "NoRepair" 1                         
	WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela lite ${VERSIONNAME}" \
	                 "HelpLink" "http://www.sjeng.org"                         
	WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela lite ${VERSIONNAME}" \
	                 "URLInfoAbout" "http://www.sjeng.org"        
	                 
  	  
	MessageBox MB_OK|MB_ICONINFORMATION "Setup has completed."
	
	;Quit
	
SectionEnd

;--------------------------------    
;Uninstaller Section  
Section "Uninstall"	
   
	;Delete Files 
	RMDir /r "$INSTDIR\*.*"    
	
	;Remove the installation directory
	
	Delete "$INSTDIR\Uninstall.exe"
	RMDir "$INSTDIR"
	
	Delete "$DESKTOP\${MUI_PRODUCT}.lnk"
	
	!insertmacro MUI_STARTMENU_GETFOLDER Application $MUI_TEMP
	
	Delete "$SMPROGRAMS\$MUI_TEMP\${MUI_PRODUCT}.lnk"  
	Delete "$SMPROGRAMS\$MUI_TEMP\Leela Homepage.lnk"
	Delete "$SMPROGRAMS\$MUI_TEMP\Uninstall.lnk"
	
	;Delete empty start menu parent diretories
	StrCpy $MUI_TEMP "$SMPROGRAMS\$MUI_TEMP"
	
  startMenuDeleteLoop:
	ClearErrors
	RMDir $MUI_TEMP
	GetFullPathName $MUI_TEMP "$MUI_TEMP\.."
	
	IfErrors startMenuDeleteLoopDone
	
	StrCmp $MUI_TEMP $SMPROGRAMS startMenuDeleteLoopDone startMenuDeleteLoop

  startMenuDeleteLoopDone:
	
	DeleteRegKey HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela lite ${VERSIONNAME}"	
	DeleteRegKey /ifempty HKCU "Software\Leelalite"       		
  
SectionEnd

Function un.onUninstSuccess
  MessageBox MB_OK "You have successfully uninstalled ${MUI_PRODUCT}."
FunctionEnd

