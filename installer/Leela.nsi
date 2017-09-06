!define LEELABIN  "Leela0110.exe"
!define LEELAOCL  "Leela0110_OpenCL.exe"
!define VERSION   "0.11.0"

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

!addplugindir ".\installer"
!addincludedir ".\installer"

!include "MUI2.nsh"
!include "Sections.nsh"
!include "FileFunc.nsh"
!include "UAC.nsh"

Var install_for_all
;
; File info options
;
  !searchparse "ver: ${VERSION}.0.0.0." "ver: " V1 . V2 . V3 . V4 .
  VIProductVersion "${V1}.${V2}.${V3}.${V4}"
  VIAddVersionKey "FileDescription" "Leela installer"
  VIAddVersionKey "ProductName" "Leela"
  VIAddVersionKey "CompanyName" "Sjeng.Org"
  VIAddVersionKey "LegalCopyright" "� Gian-Carlo Pascutto. All rights reserved."
  VIAddVersionKey "FileVersion" "${VERSION}"

;Variables

  Var MUI_TEMP
  Var STARTMENU_FOLDER

;
;Default install dir here is just a placeholder. Proper defaults are initialized in .onInit
;
  InstallDir "-\Leela"

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
  !define MUI_CUSTOMFUNCTION_GUIINIT onGuiInit

  !define MUI_WELCOMEPAGE_TEXT "This wizard will guide you through the installation of Leela - the Go program.$\r$\n$\r$\n$\r$\nClick Next to continue."

;
; Welcome page
;
  !insertmacro MUI_PAGE_WELCOME
  !insertmacro MUI_PAGE_LICENSE license.rtf
  Page custom ModeSelectionPageCreate ModeSelectionPageLeave
  !define MUI_PAGE_CUSTOMFUNCTION_PRE PreDir
  !insertmacro MUI_PAGE_DIRECTORY
  !define MUI_PAGE_CUSTOMFUNCTION_PRE CheckSettings
  !insertmacro MUI_PAGE_COMPONENTS

;
;Start Menu Folder Page Configuration
;
  !define MUI_STARTMENUPAGE_DEFAULTFOLDER "Leela"
  !define MUI_STARTMENUPAGE_REGISTRY_ROOT "SHCTX"
  !define MUI_STARTMENUPAGE_REGISTRY_KEY "Software\Sjeng.Org\Leela"
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
  !insertmacro UAC_PageElevation_OnInit

  StrCpy $install_for_all 0
  ReadRegStr $0 HKLM "Software\Sjeng.Org\Leela" "InstallDir"
  ${If} $0 != ""
    StrCpy $install_for_all 1
  ${EndIf}

  ${If} $STARTMENU_FOLDER == ""
    ReadRegStr $STARTMENU_FOLDER HKCU "Software\Leela" "Start Menu Folder"
  ${EndIf}
  ${If} $INSTDIR == "-\Leela"
    ReadRegStr $INSTDIR HKLM "Software\Sjeng.Org\Leela" "InstallDir"
    ${If} $INSTDIR == ""
      ReadRegStr $INSTDIR HKCU "Software\Sjeng.Org\Leela" "InstallDir"
    ${EndIf}
    ${If} $INSTDIR == ""
      ReadRegStr $INSTDIR HKCU "Software\Leela" "" ; old version used this registry key
    ${EndIf}
  ${EndIf}

  ${If} ${UAC_IsInnerInstance}
    ${IfNot} ${UAC_IsAdmin}
      SetErrorLevel 0x666666 ; special return value for outer instance so it knows we did not have admin rights
      Quit
    ${EndIf}
    StrCpy $install_for_all 1
  ${EndIf}

  System::Call 'Kernel32::SetEnvironmentVariable(t, t) i("SEE_MASK_NOZONECHECKS", "1").r0' ; prevent internet zone warnings from popping up twice

  ${If} $install_for_all == 0
    SetShellVarContext current
  ${Else}
    SetShellVarContext all
  ${EndIf}
  ReadRegStr $0 SHCTX "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela" "UninstallString"
  ReadRegStr $1 SHCTX "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela" "DisplayVersion"
  ${If} $0 == ""
  ${OrIf} "$1" == "${VERSIONNAME}"
  ${OrIfNot} ${FileExists} $0
    Call RemoveCleanup
  ${EndIf}
FunctionEnd

Function onGuiInit
  !insertmacro UAC_PageElevation_OnGuiInit
FunctionEnd

Var HWND_mode_allusers
Var HWND_mode_currentuser
!ifndef BCM_SETSHIELD
!define BCM_SETSHIELD 5644
!endif

Function ModeSelectionPageCreate
  ${If} ${UAC_IsInnerInstance}
  ${AndIf} ${UAC_IsAdmin}
    Call RemoveShieldIcon
    SendMessage $HWNDPARENT "0x408" "1" ""
    Abort
  ${EndIf}
  !insertmacro MUI_HEADER_TEXT_PAGE "Choose Install Type" "Install for all users or only for the current user."

  GetDlgItem $9 $HWNDPARENT 1

  nsDialogs::Create /NOUNLOAD 1018
  Pop $0

  ${NSD_CreateRadioButton} 0 25u 50% 10u "Install for current user"
  Pop $HWND_mode_currentuser
  ${NSD_AddStyle} $HWND_mode_currentuser ${WS_GROUP}

  ${NSD_CreateRadioButton} 0 75u 50% 10u "Install for all users"
  Pop $HWND_mode_allusers

  ${NSD_CreateLabel} 12u 40u 90% 20u "Default. No administrative rights required."
  Pop $0

  ${NSD_CreateLabel} 12u 90u 90% 20u "Install Leela for all users of this machine."
  Pop $0

  #CreateFont $0 $(^Font) $(^FontSize) "700"
  CreateFont $0 "Tahoma" $(^FontSize) "700"
  ${If} $0 != ""
    SendMessage $HWND_mode_currentuser ${WM_SETFONT} $0 1
    SendMessage $HWND_mode_allusers ${WM_SETFONT} $0 1
  ${EndIf}

  ${NSD_OnClick} $HWND_mode_currentuser OnCheckboxCur
  ${NSD_OnClick} $HWND_mode_allusers OnCheckboxAll
  ${NSD_OnBack} RemoveShieldIcon

  ${NSD_UnCheck} $HWND_mode_currentuser
  ${NSD_UnCheck} $HWND_mode_allusers

  ${If} $install_for_all == 0
    ${NSD_Check} $HWND_mode_currentuser
    SendMessage $9 ${BCM_SETSHIELD} 0 0
    ${NSD_SetFocus} $HWND_mode_currentuser
  ${Else}
    ${NSD_Check} $HWND_mode_allusers
    SendMessage $9 ${BCM_SETSHIELD} 0 1
    ${NSD_SetFocus} $HWND_mode_allusers
  ${EndIf}

  nsDialogs::Show
FunctionEnd

Function RemoveShieldIcon
  GetDlgItem $9 $HWNDPARENT 1
  SendMessage $9 ${BCM_SETSHIELD} 0 0
FunctionEnd

Function OnCheckboxCur
  Pop $0
  GetDlgItem $9 $HWNDPARENT 1
  SendMessage $9 ${BCM_SETSHIELD} 0 0
  StrCpy $install_for_all 0
FunctionEnd

Function OnCheckboxAll
  Pop $0
  GetDlgItem $9 $HWNDPARENT 1
  SendMessage $9 ${BCM_SETSHIELD} 0 1
  StrCpy $install_for_all 1
FunctionEnd

Function ModeSelectionPageLeave
  ${If} $install_for_all <> 0
  ${AndIfNot} ${UAC_IsAdmin}
    GetDlgItem $9 $HWNDPARENT 1
    System::Call user32::GetFocus()i.s
    EnableWindow $9 0
    !insertmacro UAC_RunElevated
    GetDlgItem $9 $HWNDPARENT 1
    EnableWindow $9 1
    System::Call user32::SetFocus(is)
    ${If} $2 = 0x666666 ;our special return, the new process was not admin after all
      MessageBox MB_ICONEXCLAMATION "You need to login with administrative rights to continue..." /SD IDOK
      Abort
    ${ElseIf} $0 = 1223 ;cancel
      Abort
    ${EndIf}
    Quit ;We now have a new process, the install will continue there, we have nothing left to do here
  ${EndIf}
  Call RemoveShieldIcon
FunctionEnd

Function PreDir
  GetDlgItem $0 $HWNDPARENT 3 ; Back
  EnableWindow $0 0
  ${If} $install_for_all == 0
    SetShellVarContext current
  ${Else}
    SetShellVarContext all
  ${EndIf}
  ${If} $install_for_all == 1
    ReadRegStr $0 HKCU "Software\Sjeng.Org\Leela" "InstallDir"
    ${If} $0 == ""
      ReadRegStr $0 HKCU "Software\Leela" ""
    ${EndIf}
    ${If} $INSTDIR == "$LOCALAPPDATA\Programs\Leela"
    ${OrIf} $INSTDIR == $0
      StrCpy $INSTDIR ""
    ${EndIf}
  ${Else}
    ReadRegStr $0 HKLM "Software\Sjeng.Org\Leela" "InstallDir"
    ${If} $INSTDIR == "$PROGRAMFILES\Leela"
    ${OrIf} $INSTDIR == $0
      StrCpy $INSTDIR ""
    ${EndIf}
  ${EndIf}
  ${If} $INSTDIR == ""
    ReadRegStr $INSTDIR SHCTX "Software\Sjeng.Org\Leela" "InstallDir"
    ${If} $INSTDIR == ""
      ${If} $install_for_all == 0
        StrCpy $INSTDIR "$LOCALAPPDATA\Programs\Leela"
      ${Else}
        StrCpy $INSTDIR "$PROGRAMFILES\Leela"
      ${EndIf}
    ${EndIf}
  ${EndIf}
FunctionEnd

Var size

Section "Uninstall previous version" cleanup
  ReadRegStr $0 SHCTX "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela" "UninstallString"
  ${If} $0 != ""
  ${AndIf} ${FileExists} $0
    ExecWait '"$0" /S /update' $1
  ${EndIf}
SectionEnd

Section "Leela" leela
  SectionIn RO
  SetOutPath $INSTDIR

  File "bin\${LEELABIN}"
  ;;File "bin\libgcc_s_dw2-1.dll"
  ;;File "bin\libopenblas.dll"
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
  WriteRegStr SHCTX "Software\Sjeng.Org\Leela" "InstallDir" $INSTDIR

  ;create uninstaller
  AddSize 73
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

  WriteRegStr SHCTX "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela" \
                    "DisplayName" "Leela - the Go Program"
  WriteRegStr SHCTX "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela" \
                    "DisplayVersion" "${VERSIONNAME}"
  WriteRegStr SHCTX "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela" \
                    "DisplayIcon" "$INSTDIR\${LEELABIN},0"
  WriteRegStr SHCTX "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela" \
                   "UninstallString" "$INSTDIR\Uninstall.exe"
  WriteRegStr SHCTX "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela" \
                   "InstallLocation" "$INSTDIR"
  WriteRegStr SHCTX "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela" \
                   "Publisher" "Sjeng.Org"
  WriteRegDWORD SHCTX "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela" \
                     "EstimatedSize" $size
  WriteRegDWORD SHCTX "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela" \
                     "NoModify" 1
  WriteRegDWORD SHCTX "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela" \
                     "NoRepair" 1
  WriteRegStr SHCTX "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela" \
                   "HelpLink" "https://www.sjeng.org"
  WriteRegStr SHCTX "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela" \
                   "URLInfoAbout" "https://www.sjeng.org"
SectionEnd

Function RemoveCleanup
  !insertmacro UnselectSection ${cleanup}
  SectionSetInstTypes ${cleanup} 0
  SectionSetText ${cleanup} ""
FunctionEnd

Function CheckSettings
  ${If} ${FileExists} "$INSTDIR\OpenCL.dll"
    !insertmacro SelectSection ${leela_ocl}
  ${EndIf}
FunctionEnd

;--------------------------------
;Uninstaller Section

Var updating

Function un.onInit
  StrCpy $install_for_all 0
  ReadRegStr $0 HKLM "Software\Sjeng.Org\Leela" "InstallDir"
  ${If} $0 != ""
    StrCpy $install_for_all 1
  ${EndIf}

  StrCpy $updating 0
  ${GetParameters} $9
  ${GetOptions} $9 "/update" $0
  ${IfNot} ${Errors}
    StrCpy $updating 1
  ${EndIf}

  ${If} $install_for_all == 0
    SetShellVarContext current
  ${Else}
    SetShellVarContext all
  ${EndIf}

  ${If} $install_for_all <> 0
    !insertmacro UAC_RunElevated
    StrCmp $0 1223 UAC_ElevationAborted
    StrCmp $0 0 0 UAC_Err
    StrCmp $1 1 0 UAC_Done
    Quit

    UAC_Err:
    MessageBox MB_ICONEXCLAMATION "You need to login with administrative rights to continue..." /SD IDOK
    Abort

    UAC_ElevationAborted:
    Abort

    UAC_done:
    ${IfNot} ${UAC_IsAdmin}
      Goto UAC_Err
    ${EndIf}
  ${EndIf}
FunctionEnd

Section "Uninstall"
  ;Delete Files
  Delete "$INSTDIR\${LEELABIN}"
  Delete "$INSTDIR\${LEELAOCL}"
  ;;Delete "$INSTDIR\libgcc_s_dw2-1.dll"
  ;;Delete "$INSTDIR\libopenblas.dll"
  ;;Delete "$INSTDIR\libgfortran-3.dll"
  ;;Delete "$INSTDIR\libquadmath-0.dll"
  Delete "$INSTDIR\OpenCL.dll"
  Delete "$INSTDIR\Leela Homepage.url"
  Delete "$INSTDIR\license.rtf"
  Delete "$INSTDIR\Uninstall.exe"

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

  DeleteRegKey SHCTX "Software\Microsoft\Windows\CurrentVersion\Uninstall\Leela"
  ${If} $install_for_all <> 0
    DeleteRegKey SHCTX "Software\Sjeng.Org\Leela"
    DeleteRegKey /ifempty SHCTX "Software\Sjeng.Org"
  ${EndIf}
  ${If} $updating == 0
    DeleteRegKey HKCU "Software\Sjeng.Org\Leela"
    DeleteRegKey /ifempty HKCU "Software\Sjeng.Org"
  ${EndIf}

  ;Remove the installation directory (if empty)
  RMDir "$INSTDIR"
SectionEnd
