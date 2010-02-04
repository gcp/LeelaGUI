#include "stdafx.h"
#include "NewGameDialog.h"
#include "UCTSearch.h"

NewGameDialog::NewGameDialog( wxWindow* parent )
:
TNewGameDialog( parent )
{
                  
}

void NewGameDialog::doInit( wxInitDialogEvent& event ) {    
    int size = wxConfig::Get()->Read(wxT("DefaultBoardSize"), (long)0);
    m_radioBoxBoardSize->SetSelection(size);
    
    int handicap = wxConfig::Get()->Read(wxT("DefaultHandicap"), (long)0);
    m_spinCtrlHandicap->SetValue(handicap);
    
    int komi = wxConfig::Get()->Read(wxT("DefaultKomi"), (long)7);
    m_spinCtrlKomi->SetValue(komi);
    
    int simulations = wxConfig::Get()->Read(wxT("DefaultSimulations"), (long)4);
    m_radioBoxLevel->SetSelection(simulations);
    
    int minutes = wxConfig::Get()->Read(wxT("DefaultMinutes"), (long)30);
    m_spinCtrlTime->SetValue(minutes);
    
    int color = wxConfig::Get()->Read(wxT("DefaultColor"), (long)0);
    m_radioBoxColor->SetSelection(color);
        
#ifdef LITEVERSION
    m_radioBoxBoardSize->Enable(2, false);
    m_radioBoxLevel->Enable(5, false);
    m_radioBoxLevel->Enable(6, false);
#endif  
}

void NewGameDialog::doCancel( wxCommandEvent& event ) {
    event.Skip();
}

void NewGameDialog::doOK( wxCommandEvent& event ) {
    // XXX: save settings        
    int size = m_radioBoxBoardSize->GetSelection();
    wxConfig::Get()->Write(wxT("DefaultBoardSize"), size);
    
    int simulations = m_radioBoxLevel->GetSelection();
    wxConfig::Get()->Write(wxT("DefaultSimulations"), simulations);
    
    int color = m_radioBoxColor->GetSelection();
    wxConfig::Get()->Write(wxT("DefaultColor"), color);
    
    int handicap = m_spinCtrlHandicap->GetValue();
    wxConfig::Get()->Write(wxT("DefaultHandicap"), handicap);
    
    int komi = m_spinCtrlKomi->GetValue();
    wxConfig::Get()->Write(wxT("DefaultKomi"), komi);
    
    int minutes = m_spinCtrlTime->GetValue();
    wxConfig::Get()->Write(wxT("DefaultMinutes"), minutes);  
    
    event.Skip();          
}

float NewGameDialog::getKomi() {
    float komi = m_spinCtrlKomi->GetValue();
    return komi + 0.5f;
}

int NewGameDialog::getHandicap() {
    int handicap = m_spinCtrlHandicap->GetValue();
    return handicap;
}

int NewGameDialog::getBoardsize() {
    wxString sboardsize = m_radioBoxBoardSize->GetStringSelection();
    if (sboardsize == "9 x 9") {
        return 9;
    } else if (sboardsize == "13 x 13") {
        return 13;
    } else if (sboardsize == "19 x 19") {
        return 19;
    } else if (sboardsize == "25 x 25") {
        return 25;
    } else if (sboardsize == "29 x 29") {
        return 29;
    } else if (sboardsize == "33 x 33") {
        return 33;
    } else if (sboardsize == "37 x 37") {
        return 37;
    }   
    
    throw std::exception("Invalid board size selection");
}

int NewGameDialog::getSimulations() {
    int simuls = m_radioBoxLevel->GetSelection();    
    
    if (simuls == 0) {
        return 100;
    } else if (simuls == 1) {
        return 500;
    } else if (simuls == 2) {
        return 1000;
    } else if (simuls == 3) {
        return 5000;
    } else if (simuls == 4) {
        return 10000;
    } else if (simuls == 5) {
        return 20000;
    } else if (simuls == 6) {
        return 0;
    }
    
    throw std::exception("Invalid simulations level selection");
}

int NewGameDialog::getPlayerColor() {
    int color = m_radioBoxColor->GetSelection();
    
    return color;
}

int NewGameDialog::getTimeControl() {
    return m_spinCtrlTime->GetValue();
}

void NewGameDialog::doHandicapUpdate( wxSpinEvent& event ) {    
    m_spinCtrlKomi->SetValue(0);
}
