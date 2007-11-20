#include "stdafx.h"
#include "NewGameDialog.h"
#include "UCTSearch.h"

NewGameDialog::NewGameDialog( wxWindow* parent )
:
TNewGameDialog( parent )
{
    //m_radioBoxBoardSize->Enable(2, false);
}

void NewGameDialog::doCancel( wxCommandEvent& event ) {
    event.Skip();
}

void NewGameDialog::doOK( wxCommandEvent& event ) {
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
        return UCTSearch::MAX_TREE_SIZE * 100;
    }
    
    throw std::exception("Invalid simulations level selection");
}

int NewGameDialog::getPlayerColor() {
    int color = m_radioBoxColor->GetSelection();
    
    return color;
}

void NewGameDialog::doHandicapUpdate( wxSpinEvent& event ) {    
    m_spinCtrlKomi->SetValue(0);
}