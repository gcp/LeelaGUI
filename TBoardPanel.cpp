#include "stdafx.h"
#include "TBoardPanel.h"

BEGIN_EVENT_TABLE(TBoardPanel, wxPanel)	
    EVT_PAINT(TBoardPanel::doPaint)	
END_EVENT_TABLE()

void TBoardPanel::doPaint(wxPaintEvent& event) {
    wxPaintDC dc(this); 
        
    wxSize sz = GetClientSize();
    
    wxBitmap woodTile("IDB_BITMAPWOOD", wxBITMAP_TYPE_BMP_RESOURCE);
    int srcWidth = woodTile.GetWidth();
    int srcHeight = woodTile.GetHeight();
    
    ::wxLogDebug("width: %d height: %d", sz.GetWidth(), sz.GetHeight());
    
    // generate all orientations
    /*wxImage tileNorm = woodTile.ConvertToImage();
    wxImage tileHoriz = tileNorm.Mirror(true);
    wxImage tileVertic = tileNorm.Mirror(false);
    wxImage tileInvert = tileNorm.Mirror(true).Mirror(false);
    
    wxBitmap tileN(tileNorm);
    wxBitmap tileH(tileHoriz);
    wxBitmap tileV(tileVertic);
    wxBitmap tileI(tileInvert);    
    
    // 2 x 2 tile
    wxBitmap tileFull(srcWidth * 2, srcHeight * 2);
    wxMemoryDC dcTile, dcSrc;
    dcTile.SelectObject(tileFull);
    
    dcSrc.SelectObject(tileN);    
    dcTile.Blit(0, 0, srcWidth, srcHeight, &dcSrc, 0, 0, wxCOPY, false);
    dcSrc.SelectObject(tileH);
    dcTile.Blit(srcWidth, 0, srcWidth, srcHeight, &dcSrc, 0, 0, wxCOPY, false);
        
    dc.DrawBitmap(tileFull, 0, 0, false);      */         
    dc.DrawBitmap(woodTile, 0, 0, false);         
    event.Skip();
};