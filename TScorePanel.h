#pragma once
#ifndef TSCOREPANEL_H
#define TSCOREPANEL_H

#include "stdafx.h"

class TScorePanel : public wxPanel {
public:
    TScorePanel(wxWindow *parent,
        wxWindowID winid = wxID_ANY,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxNO_BORDER | wxWANTS_CHARS,
        const wxString& name = wxPanelNameStr);
private:
    DECLARE_EVENT_TABLE()

    int m_CurrentMove{-1};

    void doPaint(wxPaintEvent& event);
    void doErase(wxEraseEvent& event);
    void doMouse(wxMouseEvent& event);
    void doKeyDown(wxKeyEvent& event);
};

#endif