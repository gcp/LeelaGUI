#include "SettingsDialog.h"

SettingsDialog::SettingsDialog( wxWindow* parent )
:
TSettingsDialog( parent )
{

}

void SettingsDialog::doInit(wxInitDialogEvent& event) {
    bool passEnabled = wxConfig::Get()->Read(wxT("passEnabled"), 1);
    m_checkBoxPasses->SetValue(passEnabled);

    bool resignEnabled = wxConfig::Get()->Read(wxT("resignEnabled"), 1);
    m_checkBoxResignations->SetValue(resignEnabled);

    bool ponderEnabled = wxConfig::Get()->Read(wxT("ponderEnabled"), 1);
    m_checkBoxPondering->SetValue(ponderEnabled);

    bool netsEnabled = wxConfig::Get()->Read(wxT("netsEnabled"), 1);
    m_checkBoxNeuralNet->SetValue(netsEnabled);

    bool soundEnabled = wxConfig::Get()->Read(wxT("soundEnabled"), 1);
    m_checkBoxSound->SetValue(soundEnabled);

    bool dpiEnabled = wxConfig::Get()->Read(wxT("dpiscaleEnabled"), (long)0);
    m_checkBoxDPIScaling->SetValue(dpiEnabled);

#ifdef __WXGTK__
    m_checkBoxDPIScaling->Disable();
#elif defined(__WXMAC__)
    m_checkBoxDPIScaling->Disable();
    m_checkBoxSound->Disable();
#else
#endif
}

void SettingsDialog::doCancel(wxCommandEvent& event) {
    event.Skip();
}

void SettingsDialog::doOK(wxCommandEvent& event) {
    bool passEnabled = m_checkBoxPasses->GetValue();
    wxConfig::Get()->Write(wxT("passEnabled"), passEnabled);

    bool resignEnabled = m_checkBoxResignations->GetValue();
    wxConfig::Get()->Write(wxT("resignEnabled"), resignEnabled);

    bool ponderEnabled = m_checkBoxPondering->GetValue();
    wxConfig::Get()->Write(wxT("ponderEnabled"), ponderEnabled);

    bool netsEnabled = m_checkBoxNeuralNet->GetValue();
    wxConfig::Get()->Write(wxT("netsEnabled"), netsEnabled);

    bool soundEnabled = m_checkBoxSound->GetValue();
    wxConfig::Get()->Write(wxT("soundEnabled"), soundEnabled);

    bool dpiEnabled = m_checkBoxDPIScaling->GetValue();
    wxConfig::Get()->Write(wxT("dpiscaleEnabled"), dpiEnabled);

    event.Skip();
}
