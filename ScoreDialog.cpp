#include "ScoreDialog.h"

ScoreDialog::ScoreDialog( wxWindow* parent, wxString message,
                          wxString confidence )
:
TScoreDialog( parent )
{
    m_staticTextMessage->SetLabel(message);
    m_staticTextConfidence->SetLabel(confidence);
    this->Layout();
}

void ScoreDialog::doAccept( wxCommandEvent& event )
{
    mAccepts = true;
    Destroy();
}

void ScoreDialog::doDispute( wxCommandEvent& event )
{
    mAccepts = false;
    Destroy();
}
