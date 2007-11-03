#include "stdafx.h"

class TBoardPanel : public wxPanel {    
public:
    TBoardPanel(wxWindow *parent,
               wxWindowID winid = wxID_ANY,
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxDefaultSize,
               long style = wxTAB_TRAVERSAL | wxNO_BORDER,
               const wxString& name = wxPanelNameStr)
               : wxPanel(parent, winid, pos, size, style, name){};
private:
    DECLARE_EVENT_TABLE()    
    
    void doPaint(wxPaintEvent& event);
};
