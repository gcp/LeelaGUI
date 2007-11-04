#include "stdafx.h"

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
                                  
private:
    DECLARE_EVENT_TABLE()
    
    void doPaint(wxPaintEvent& event);
    void doErase(wxEraseEvent& event);
    void doLeftMouse(wxMouseEvent& event);
    
    GameState * m_State;
    wxBitmap m_tileFull;        
    int m_cellDim;
};
