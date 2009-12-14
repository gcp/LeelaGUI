#include "stdafx.h"
#include "AboutDialog.h"
#include "config.h"

AboutDialog::AboutDialog( wxWindow* parent )
:
TAboutDialog( parent )
{
    
}

void AboutDialog::doInit( wxInitDialogEvent& event ) {
    m_staticTextVersion->SetLabel(wxString(_("Leela lite version ")) + wxString(wxT(VERSION)));    
}