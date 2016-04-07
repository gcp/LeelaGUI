#include "stdafx.h"
#include "RatedSizeDialog.h"

RatedSizeDialog::RatedSizeDialog( wxWindow* parent )
:
TRatedSizeDialog( parent )
{
    m_sizeSelected = 9;
}

void RatedSizeDialog::doSize9( wxCommandEvent& event )
{
    m_sizeSelected = 9;
    Destroy();
}

void RatedSizeDialog::doSize19( wxCommandEvent& event )
{
    m_sizeSelected = 19;
    Destroy();
}

int RatedSizeDialog::getSizeSelected(void) {
    return m_sizeSelected;
}