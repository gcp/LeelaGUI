#include "stdafx.h"
#include "AboutDialog.h"
#include "config.h"
#include "Network.h"

AboutDialog::AboutDialog( wxWindow* parent )
:
TAboutDialog( parent )
{
    
}

void AboutDialog::doInit( wxInitDialogEvent& event ) {
    m_staticTextVersion->SetLabel(wxString(_("Leela version ")) + wxString(wxT(PROGRAM_VERSION)));    
    m_staticTextEngine->SetLabel(wxString(Network::get_Network()->get_backend()));
    Fit();
}