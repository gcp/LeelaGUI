!define LEELABIN  "Leela070.exe"
!define LEELAOCL  "Leela070_OpenCL.exe"
!define VERSION   "0.7.0"

!if "${NSIS_PACKEDVERSION}" >= 0x3000000
Unicode true
ManifestDPIAware true
!endif

!searchparse "ver: ${VERSION}...." "ver: " V1 . V2 . V3 . V4 .

!if "${V4}" != ""
!define VERSIONNAME "${VERSION}"
!else if "${V3}" != ""
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

	!if "${V4}" != ""
	OutFile "setupLeela${V1}${V2}${V3}${V4}.exe"
	!else if "${V3}" != ""
	OutFile "setupLeela${V1}${V2}${V3}.exe"
	!else
	OutFile "setupLeela${V1}${V2}.exe"
	!endif

!include "MUI2.nsh"
!include "Sections.nsh"

;
; File info options
;
	!searchparse "ver: ${VERSION}.0.0.0." "ver: " V1 . V2 . V3 . V4 .
	VIProductVersion "${V1}.${V2}.${V3}.${V4}"
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
	!define MUI_COMPONENTSPAGE_NODESC

	!define MUI_WELCOMEPAGE_TEXT "This wizard will guide you through the installation of Leela - the Go program.$\r$\n$\r$\n$\r$\nClick Next to continue."

;
; Welcome page
;
	!insertmacro MUI_PAGE_WELCOME
	!insertmacro MUI_PAGE_LICENSE license.rtf
	!insertmacro MUI_PAGE_DIRECTORY
	!define MUI_PAGE_CUSTOMFUNCTION_PRE CheckSettings
	!insertmacro MUI_PAGE_COMPONENTS

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

Var size

Section "Uninstall previous version" cleanup
	ReadRegStr $0 HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela" "UninstallString"
	${If} $0 != ""
	${AndIf} ${FileExists} $0
		ExecWait '"$0" /S' $1
	${EndIf}
SectionEnd

Section "Leela" leela
	SectionIn RO
	SetOutPath $INSTDIR

	File "bin\${LEELABIN}"
	File "bin\libgcc_s_dw2-1.dll"
	File "bin\libopenblas.dll"
	;File "bin\libgfortran-3.dll"
	;File "bin\libquadmath-0.dll"
	File "license.rtf"

	;create desktop shortcut
	CreateShortCut "$DESKTOP\Leela.lnk" "$INSTDIR\${LEELABIN}" ""

	!insertmacro MUI_STARTMENU_WRITE_BEGIN Application
	AddSize 4
	;create start menu shortcut
	CreateDirectory "$SMPROGRAMS\$STARTMENU_FOLDER"
	CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\Leela.lnk" "$INSTDIR\${LEELABIN}"
	!insertmacro MUI_STARTMENU_WRITE_END

	SectionGetSize ${leela} $0
	IntOp $size $size + $0
SectionEnd

Section /o "Leela (GPU accelerated)" leela_ocl
	File "bin\${LEELAOCL}"
	File "bin\OpenCL.dll"

	;create desktop shortcut
	CreateShortCut "$DESKTOP\Leela (GPU accelerated).lnk" "$INSTDIR\${LEELAOCL}" ""

	!insertmacro MUI_STARTMENU_WRITE_BEGIN Application
	AddSize 4
	;create start menu shortcut
	CreateDirectory "$SMPROGRAMS\$STARTMENU_FOLDER"
	CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\Leela (GPU accelerated).lnk" "$INSTDIR\${LEELAOCL}"
	!insertmacro MUI_STARTMENU_WRITE_END

	SectionGetSize ${leela_ocl} $0
	IntOp $size $size + $0
SectionEnd

Section "-common" common
	File "bin\Leela Homepage.url"

	;store installation folder
	WriteRegStr HKCU "Software\Leela" "" $INSTDIR

	;create uninstaller
	AddSize 65
	WriteUninstaller "$INSTDIR\Uninstall.exe"

	!insertmacro MUI_STARTMENU_WRITE_BEGIN Application
	AddSize 8
	;create start menu shortcuts
	CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\Leela Homepage.lnk" "$INSTDIR\Leela Homepage.url" \
									"" "" 0 SW_SHOWNORMAL \
									"" "https://www.sjeng.org/leela"
	CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\Uninstall.lnk" "$INSTDIR\Uninstall.exe"
	!insertmacro MUI_STARTMENU_WRITE_END

	SectionGetSize ${common} $0
	IntOp $size $size + $0

	WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela" \
										"DisplayName" "Leela - the Go Program"
	WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela" \
										"DisplayVersion" "${VERSIONNAME}"
	WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela" \
										"DisplayIcon" "$INSTDIR\${LEELABIN},0"
	WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela" \
									 "UninstallString" "$INSTDIR\Uninstall.exe"
	WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela" \
									 "InstallLocation" "$INSTDIR"
	WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela" \
									 "Publisher" "Sjeng.Org"
	WriteRegDWORD HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela" \
										 "EstimatedSize" $size
	WriteRegDWORD HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela" \
										 "NoModify" 1
	WriteRegDWORD HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela" \
										 "NoRepair" 1
	WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela" \
									 "HelpLink" "https://www.sjeng.org"
	WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela" \
									 "URLInfoAbout" "https://www.sjeng.org"
SectionEnd

Function .onInit
	SetShellVarContext current
	ReadRegStr $0 HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela" "UninstallString"
	ReadRegStr $1 HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela" "DisplayVersion"
	${If} $0 == ""
	${OrIf} "$1" == "${VERSIONNAME}"
	${OrIfNot} ${FileExists} $0
		!insertmacro UnselectSection ${cleanup}
		SectionSetInstTypes ${cleanup} 0
		SectionSetText ${cleanup} ""
	${EndIf}
FunctionEnd

Function CheckSettings
	${If} ${FileExists} "$INSTDIR\OpenCL.dll"
		!insertmacro SelectSection ${leela_ocl}
	${EndIf}
FunctionEnd

;--------------------------------
;Uninstaller Section
Section "Uninstall"
	SetShellVarContext current

	;Delete Files
	Delete "$INSTDIR\${LEELABIN}"
	Delete "$INSTDIR\${LEELAOCL}"
	Delete "$INSTDIR\libgcc_s_dw2-1.dll"
	Delete "$INSTDIR\libopenblas.dll"
	;Delete "$INSTDIR\libgfortran-3.dll"
	;Delete "$INSTDIR\libquadmath-0.dll"
	Delete "$INSTDIR\OpenCL.dll"
	Delete "$INSTDIR\Leela Homepage.url"
	Delete "$INSTDIR\license.rtf"
	Delete "$INSTDIR\Uninstall.exe"

	;Remove the installation directory
	RMDir "$INSTDIR"

	Delete "$DESKTOP\Leela.lnk"
	Delete "$DESKTOP\Leela (GPU accelerated).lnk"

	!insertmacro MUI_STARTMENU_GETFOLDER Application $MUI_TEMP

	Delete "$SMPROGRAMS\$MUI_TEMP\Leela.lnk"
	Delete "$SMPROGRAMS\$MUI_TEMP\Leela (GPU accelerated).lnk"
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
