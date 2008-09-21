#include "stdafx.h"
#include "ClockAdjustDialog.h"
#include "TimeControl.h"
#include "FastBoard.h"

ClockAdjustDialog::ClockAdjustDialog( wxWindow* parent )
:
TClockAdjustDialog( parent )
{

}

void ClockAdjustDialog::doCancel( wxCommandEvent& event ) {
    event.Skip();
}

void ClockAdjustDialog::doOK( wxCommandEvent& event ) {
    int tleftmins = m_spinCtrlBlackMins->GetValue();
    int tleftsecs = m_spinCtrlBlackSecs->GetValue();
    m_tc.adjust_time(FastBoard::BLACK, (tleftmins * 60 + tleftsecs) * 100, 25);

    tleftmins = m_spinCtrlWhiteMins->GetValue();
    tleftsecs = m_spinCtrlWhiteSecs->GetValue();
    m_tc.adjust_time(FastBoard::WHITE, (tleftmins * 60 + tleftsecs) * 100, 25);
    event.Skip();
}

void ClockAdjustDialog::doInit( wxInitDialogEvent& event ) {
    int mins, secs;
    mins = (m_tc.get_remaining_time(FastBoard::BLACK) / 100) / 60;
    secs = (m_tc.get_remaining_time(FastBoard::BLACK) / 100) % 60;
    m_spinCtrlBlackMins->SetValue(mins);
    m_spinCtrlBlackSecs->SetValue(secs);
    mins = (m_tc.get_remaining_time(FastBoard::WHITE) / 100) / 60;
    secs = (m_tc.get_remaining_time(FastBoard::WHITE) / 100) % 60;
    m_spinCtrlWhiteMins->SetValue(mins);
    m_spinCtrlWhiteSecs->SetValue(secs);    
}

void ClockAdjustDialog::setTimeControl(TimeControl tc) {
    m_tc = tc;
}

TimeControl ClockAdjustDialog::getTimeControl(void) {
    return m_tc;
}