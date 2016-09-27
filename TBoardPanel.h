#ifndef TBOARDPANEL_H
#define TBOARDPANEL_H

#include "stdafx.h"

#include "FastBoard.h"
#include "GameState.h"

wxDECLARE_EVENT(wxEVT_DISPLAY_MAINLINE, wxCommandEvent);

class TBoardPanel : public wxPanel {    
public:
    TBoardPanel(wxWindow *parent,
               wxWindowID winid = wxID_ANY,
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxDefaultSize,
               long style = wxNO_BORDER | wxWANTS_CHARS,
               const wxString& name = wxPanelNameStr);
                   
    void setState(GameState * brd);               
    void setPlayerColor(int color);
    void setShowInfluence(bool val);
    void setShowMoyo(bool val);
    void setShowTerritory(bool val);
    bool getShowInfluence();
    bool getShowMoyo();
    void doMoyo();
    void doInfluence();   
    void doTerritory();     
    void lockState();
    void unlockState();
    void clearPV();
                                      
private:
    DECLARE_EVENT_TABLE()
    
    void doPaint(wxPaintEvent& event);
    void doErase(wxEraseEvent& event);
    void doLeftMouse(wxMouseEvent& event);
    void doKeyDown(wxKeyEvent& event);
    void doDisplayMainline(wxCommandEvent& event);
    
    GameState * m_State;
    bool m_stateLock;
    wxBitmap m_tileFull;  
    wxImage m_whiteStone;
    wxImage m_blackStone;      
    int m_cellDim;
    int m_playerColor;
    bool m_showTerritory;   // on game end
    bool m_showInfluence;
    bool m_showMoyo;    
    std::vector<int> m_Hatch;
    std::vector<int> m_PV;
};

#endif