#include "stdafx.h"
#include "GUI.h"
#include "MainFrame.h"

MainFrame::MainFrame(wxFrame *frame, const wxString& title)
          :TMainFrame(frame, wxID_ANY, title) {   
    delete wxLog::SetActiveTarget(new wxLogTextCtrl(m_logText));
    Center();  
}

MainFrame::~MainFrame() {
    delete wxLog::SetActiveTarget(new wxLogStderr(NULL));    
}

void MainFrame::doNewGame(wxCommandEvent & event) {
}

void MainFrame::doExit(wxCommandEvent & event) {
    Close();
}

void MainFrame::doPaint(wxPaintEvent& event) {    
    wxPaintDC tmp(this);        
    wxPaintDC dc(m_panelBoard); 
        
    wxSize sz = m_panelBoard->GetClientSize();
    
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
}

void MainFrame::doActivate(wxActivateEvent& event) {  
    Refresh();                  
}

void MainFrame::doResize(wxSizeEvent& event) {
    // force full redraw if board area changes size
    Refresh();   
    event.Skip();    
}
