#include "stdafx.h"
#include "CopyProtectionDialog.h"

CopyProtectionDialog::CopyProtectionDialog( wxWindow* parent )
:
TCopyProtectionDialog( parent )
{

}

void CopyProtectionDialog::doOK( wxCommandEvent& event ) {
    m_Name = m_textCtrlName->GetLineText(0);
    m_Code = m_textCtrlCode->GetLineText(0);
    event.Skip();
}

wxString CopyProtectionDialog::getName() {
    return m_Name;
}
wxString CopyProtectionDialog::getCode() {
    return m_Code;
}