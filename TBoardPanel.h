#include "stdafx.h"

class TBoardPanel : public wxPanel {    
public:
    TBoardPanel(wxWindow *parent,
               wxWindowID winid = wxID_ANY,
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxDefaultSize,
               long style = wxTAB_TRAVERSAL | wxNO_BORDER,
               const wxString& name = wxPanelNameStr);
                                  
private:
    DECLARE_EVENT_TABLE()
    
    void doPaint(wxPaintEvent& event);    
    
    int m_boardSize;
    wxBitmap m_tileFull;        
};
