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
    void setShowOwner(bool val);
    void setShowMoyo(bool val);
    void setShowTerritory(bool val);
    void setShowProbabilities(bool val);
    void setShowBestMoves(bool val);
    bool getShowOwner();
    bool getShowMoyo();
    bool getShowProbabilities();
    bool getShowBestMoves();
    void doTerritory(bool disputing);
    void lockState();
    void unlockState();
    bool isLockedState() const {
        return m_stateLock;
    }
    void clearViz();

private:
    DECLARE_EVENT_TABLE()
    
    void doPaint(wxPaintEvent& event);
    void doErase(wxEraseEvent& event);
    void doLeftMouse(wxMouseEvent& event);
    void doKeyDown(wxKeyEvent& event);
    void doDisplayMainline(wxCommandEvent& event);
    void doBestMovesUpdate(wxCommandEvent& event);
    void doMoyo();
    void doOwner();
    void doProbabilities();

    GameState * m_State;
    bool m_stateLock;
    wxBitmap m_tileFull;  
    wxImage m_whiteStone;
    wxImage m_blackStone;      
    int m_cellDim;
    int m_playerColor;
    int m_analysisColor;
    bool m_showTerritory;   // on game end
    bool m_showOwner;
    bool m_showMoyo;
    bool m_showProbabilities;
    bool m_showBestMoves;
    uint64_t m_DisplayedStateHash;
    std::vector<int> m_Hatch;
    std::vector<int> m_PV;
    std::vector<float> m_Owner;
    std::vector<float> m_Probabilities;
    float m_MaxProbability;
};

#endif