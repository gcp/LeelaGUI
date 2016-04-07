!if "${NSIS_PACKEDVERSION}" >= 0x3000000
Unicode true
!endif

; create ver.vbs and extract version number from the leela.exe binary
!system 'echo set args = WScript.Arguments>ver.vbs'
!system 'echo Set fso = CreateObject("Scripting.FileSystemObject")>>ver.vbs'
!system 'echo WScript.Echo "ver: " + fso.GetFileVersion(args(0))>>ver.vbs'
!system 'echo Wscript.Quit>>ver.vbs'
!system 'cscript.exe //nologo ver.vbs "bin\Leela.exe">ver.tmp'

!searchparse /file ver.tmp "ver: " V1 . V2 . V3 . V4
!delfile ver.vbs
!delfile ver.tmp

!define VERSION "${V1}.${V2}.${V3}.${V4}"

!if ${V4} != 0
!define VERSIONNAME "${VERSION}"
!else if ${V3} != 0
!define VERSIONNAME "${V1}.${V2}.${V3}"
!else
!define VERSIONNAME "${V1}.${V2}"
!endif

;
; General options
;
  Name                    "Leela ${VERSIONNAME}"
	CRCCheck                on
	SetCompress             auto
	SetDatablockOptimize    on
	InstallColors           /windows
	AutoCloseWindow         false
	SetDateSave             on
	WindowIcon              on
	XPStyle                 on
	BrandingText            "Leela ${VERSIONNAME}"
	UninstallCaption        "Leela ${VERSIONNAME} Uninstall"
	ShowUninstDetails       hide
	ShowInstDetails         hide
	RequestExecutionLevel   user
	ManifestDPIAware        true

  !if ${V4} != 0
	OutFile "setupLeela${V1}${V2}${V3}${V4}.exe"
  !else if ${V3} != 0
	OutFile "setupLeela${V1}${V2}${V3}.exe"
  !else
	OutFile "setupLeela${V1}${V2}.exe"
  !endif

!include MUI.nsh

;
; File info options
;
	VIProductVersion "${VERSION}"
	VIAddVersionKey "FileDescription" "Leela installer"
	VIAddVersionKey "ProductName" "Leela"
	VIAddVersionKey "CompanyName" "Sjeng.Org"
	VIAddVersionKey "LegalCopyright" "© Gian-Carlo Pascutto. All rights reserved."
	VIAddVersionKey "FileVersion" "${VERSION}"

;Variables

	Var MUI_TEMP
	Var STARTMENU_FOLDER

;
;Get installation folder from registry if available
;
	InstallDirRegKey HKCU "Software\Leela" ""
	InstallDir "$LOCALAPPDATA\Programs\Leela"

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

  !define MUI_WELCOMEPAGE_TEXT "This wizard will guide you through the installation of Leela - the Go program.$\r$\n$\r$\n$\r$\nClick Next to continue."

;
; Welcome page
;
	!insertmacro MUI_PAGE_WELCOME
    !insertmacro MUI_PAGE_LICENSE license.rtf
	!insertmacro MUI_PAGE_DIRECTORY

;
;Start Menu Folder Page Configuration
;
  !define MUI_STARTMENUPAGE_DEFAULTFOLDER "Leela"
	!define MUI_STARTMENUPAGE_REGISTRY_ROOT "HKCU"
	!define MUI_STARTMENUPAGE_REGISTRY_KEY "Software\Leela"
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

Section "-Leela Installation"
  SetShellVarContext current
	SetOutPath $INSTDIR

	File "bin\Leela.exe"
	File "bin\Leela Homepage.url"

	;create desktop shortcut
	CreateShortCut "$DESKTOP\Leela.lnk" "$INSTDIR\Leela.exe" ""

  ;store installation folder
	WriteRegStr HKCU "Software\Leela" "" $INSTDIR

	;create uninstaller
	WriteUninstaller "$INSTDIR\Uninstall.exe"

	!insertmacro MUI_STARTMENU_WRITE_BEGIN Application

	;create shortcuts
	CreateDirectory "$SMPROGRAMS\$STARTMENU_FOLDER"
	CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\Leela.lnk" "$INSTDIR\Leela.exe"
	CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\Leela Homepage.lnk" "$INSTDIR\Leela Homepage.url" \
	                "" "" 0 SW_SHOWNORMAL \
                    "" "http://www.sjeng.org/leela"
	CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\Uninstall.lnk" "$INSTDIR\Uninstall.exe"

	!insertmacro MUI_STARTMENU_WRITE_END

	WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela" \
	                  "DisplayName" "Leela - the Go Program"
	WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela" \
	                  "DisplayIcon" "$INSTDIR\Leela.exe,0"
	WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela" \
	                 "UninstallString" "$INSTDIR\Uninstall.exe"
	WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela" \
	                 "InstallLocation" "$INSTDIR"
	WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela" \
	                 "Publisher" "Sjeng.Org"
	WriteRegDWORD HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela" \
	                   "EstimatedSize" 2781
	WriteRegDWORD HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela" \
	                   "NoModify" 1
	WriteRegDWORD HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela" \
	                   "NoRepair" 1
	WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela" \
	                 "HelpLink" "http://www.sjeng.org"
	WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela" \
	                 "URLInfoAbout" "http://www.sjeng.org"

	;Quit
SectionEnd

;--------------------------------
;Uninstaller Section
Section "Uninstall"
  SetShellVarContext current

	;Delete Files
	Delete "$INSTDIR\Leela.exe"
	Delete "$INSTDIR\Leela Homepage.url"
	Delete "$INSTDIR\Uninstall.exe"

	;Remove the installation directory
	RMDir "$INSTDIR"

	Delete "$DESKTOP\Leela.lnk"

	!insertmacro MUI_STARTMENU_GETFOLDER Application $MUI_TEMP

	Delete "$SMPROGRAMS\$MUI_TEMP\Leela.lnk"
	Delete "$SMPROGRAMS\$MUI_TEMP\Leela Homepage.lnk"
	Delete "$SMPROGRAMS\$MUI_TEMP\Uninstall.lnk"

	;Delete empty start menu parent directories
	StrCpy $MUI_TEMP "$SMPROGRAMS\$MUI_TEMP"

  startMenuDeleteLoop:
	ClearErrors
	RMDir $MUI_TEMP
	GetFullPathName $MUI_TEMP "$MUI_TEMP\.."

	IfErrors startMenuDeleteLoopDone

	StrCmp $MUI_TEMP $SMPROGRAMS startMenuDeleteLoopDone startMenuDeleteLoop

  startMenuDeleteLoopDone:

	DeleteRegKey HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela"
	DeleteRegKey /ifempty HKCU "Software\Leela"
SectionEnd
