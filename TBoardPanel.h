#ifndef TBOARDPANEL_H
#define TBOARDPANEL_H

#include "stdafx.h"

#include "FastBoard.h"
#include "GameState.h"

class TBoardPanel : public wxPanel {    
public:
    TBoardPanel(wxWindow *parent,
               wxWindowID winid = wxID_ANY,
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxDefaultSize,
               long style = wxTAB_TRAVERSAL | wxNO_BORDER,
               const wxString& name = wxPanelNameStr);
               
    void setState(GameState * brd);               
    void setPlayerColor(int color);
    void setShowTerritory(bool val);
    void setShowMoyo(bool val);
    bool getShowTerritory();
    bool getShowMoyo();
                                      
private:
    DECLARE_EVENT_TABLE()
    
    void doPaint(wxPaintEvent& event);
    void doErase(wxEraseEvent& event);
    void doLeftMouse(wxMouseEvent& event);
    
    GameState * m_State;
    wxBitmap m_tileFull;        
    int m_cellDim;
    int m_playerColor;
    bool m_showTerritory;
    bool m_showMoyo;    
};

#endif