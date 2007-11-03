#include "stdafx.h"
#include "TBoardPanel.h"

BEGIN_EVENT_TABLE(TBoardPanel, wxPanel)	
    EVT_PAINT(TBoardPanel::doPaint)	
END_EVENT_TABLE()

TBoardPanel::TBoardPanel(wxWindow *parent, wxWindowID winid, const wxPoint& pos,
                         const wxSize& size, long style,const wxString& name)
    : wxPanel(parent, winid, pos, size, style, name) {        
        
    wxBitmap woodTile("IDB_BITMAPWOOD", wxBITMAP_TYPE_BMP_RESOURCE);
    int srcWidth = woodTile.GetWidth();
    int srcHeight = woodTile.GetHeight();
    
    // generate all orientations
    wxImage tileNorm = woodTile.ConvertToImage();
    wxImage tileHoriz = tileNorm.Mirror(true);
    wxImage tileVertic = tileNorm.Mirror(false);
    wxImage tileInvert = tileNorm.Mirror(true).Mirror(false);
    
    wxBitmap tileN(tileNorm);    
    wxBitmap tileH(tileHoriz);
    wxBitmap tileV(tileVertic);
    wxBitmap tileI(tileInvert);    
    
    // 2 x 2 tile
    m_tileFull.Create(srcWidth * 2, srcHeight * 2);
    wxMemoryDC dcTile;
    wxMemoryDC dcSrc;
    
    dcTile.SelectObject(m_tileFull);    
    dcSrc.SelectObject(tileN);    
    dcTile.Blit(0, 0, srcWidth, srcHeight, &dcSrc, 0, 0, wxCOPY, false);
    dcSrc.SelectObject(tileH);
    dcTile.Blit(srcWidth, 0, srcWidth, srcHeight, &dcSrc, 0, 0, wxCOPY, false);
    dcSrc.SelectObject(tileV);
    dcTile.Blit(0, srcHeight, srcWidth, srcHeight, &dcSrc, 0, 0, wxCOPY, false);
    dcSrc.SelectObject(tileI);
    dcTile.Blit(srcWidth, srcHeight, srcWidth, srcHeight, &dcSrc, 0, 0, wxCOPY, false);
    
    dcTile.SelectObject(wxNullBitmap);
    dcSrc.SelectObject(wxNullBitmap);
    
    m_boardSize = 9;
}

void TBoardPanel::doPaint(wxPaintEvent& event) {
    wxPaintDC dc(this); 
        
    wxSize sz = GetClientSize();
    int tileW = m_tileFull.GetWidth();
    int tileH = m_tileFull.GetHeight();
            
    ::wxLogDebug("width: %d height: %d", sz.GetWidth(), sz.GetHeight());        
        
    int xc = (sz.GetWidth() / tileW) + 1;
    int yc = (sz.GetHeight() / tileH) + 1;
            
    for (int y = 0; y < yc; y++) {
        for (int x = 0; x < xc; x++) {
            dc.DrawBitmap(m_tileFull, x * tileW, y * tileH, false);             
        }
    }                
};