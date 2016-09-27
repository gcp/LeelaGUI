#include "stdafx.h"
#include "TBoardPanel.h"
#include "MainFrame.h"
#include "SGFTree.h"
#include "MCOTable.h"

wxDEFINE_EVENT(wxEVT_DISPLAY_MAINLINE, wxCommandEvent);

BEGIN_EVENT_TABLE(TBoardPanel, wxPanel)	
    EVT_KEY_DOWN(TBoardPanel::doKeyDown)
    EVT_PAINT(TBoardPanel::doPaint)
    EVT_ERASE_BACKGROUND(TBoardPanel::doErase)
    EVT_LEFT_DOWN(TBoardPanel::doLeftMouse) 
END_EVENT_TABLE()

TBoardPanel::TBoardPanel(wxWindow *parent, wxWindowID winid, const wxPoint& pos,
                         const wxSize& size, long style,const wxString& name)
    : wxPanel(parent, winid, pos, size, style, name) {

    Bind(wxEVT_DISPLAY_MAINLINE, &TBoardPanel::doDisplayMainline, this);

    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
        
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
    
    // stones
    wxBitmap wstone("IDB_WHITESTONE", wxBITMAP_TYPE_BMP_RESOURCE);      
    wstone.SetMask(new wxMask(wstone, *wxRED));    
    
    wxBitmap bstone("IDB_BLACKSTONE", wxBITMAP_TYPE_BMP_RESOURCE);    
    bstone.SetMask(new wxMask(bstone, *wxWHITE));    
    
    m_whiteStone = wstone.ConvertToImage();
    m_blackStone = bstone.ConvertToImage();                
    
    m_cellDim = 0;    
    
    m_showMoyo = false;
    m_showOwner = false;
    m_showTerritory = false;
    m_stateLock = false;
    m_State = NULL;
    m_playerColor = FastBoard::BLACK;    
    m_Hatch.resize(FastBoard::MAXSQ);
    m_PV.resize(FastBoard::MAXSQ);
    
    clearViz();
}

void TBoardPanel::setState(GameState * state) {
    m_State = state;
}

void TBoardPanel::setPlayerColor(int color) {
    m_playerColor = color;
}

void TBoardPanel::doPaint(wxPaintEvent& event) {
    wxAutoBufferedPaintDC dc(this);
        
    PrepareDC(dc);                	
        
    wxSize sz = GetClientSize();
    int tileW = m_tileFull.GetWidth();
    int tileH = m_tileFull.GetHeight();
            
    wxLogDebug("width: %d height: %d", sz.GetWidth(), sz.GetHeight());        
        
    int xc = (sz.GetWidth() / tileW) + 1;
    int yc = (sz.GetHeight() / tileH) + 1;
            
    for (int y = 0; y < yc; y++) {
        for (int x = 0; x < xc; x++) {
            dc.DrawBitmap(m_tileFull, x * tileW, y * tileH, false);             
        }
    }      

    if (m_State == NULL) {
        wxLogDebug("Paint on empty state");
        return;
    }
    
    int boardSize = m_State->board.get_boardsize();
    
    int minDim = std::min(sz.GetWidth(), sz.GetHeight());
    int cellDim = minDim / ((boardSize - 1) + 2);
    
    m_cellDim = cellDim;
    
    wxLogDebug("cell size: %d", cellDim);
            
    wxPen penThick(*wxBLACK, 2, wxSOLID);
    wxPen penThin(*wxBLACK, 1, wxSOLID);
    wxPen penEmpty(*wxBLACK, 0, wxTRANSPARENT);        
    
    // stones
    wxBrush bbrush(*wxBLACK, wxSOLID);
    wxBrush rbrush(*wxRED, wxSOLID);
    int stoneSize = ((cellDim * 19)/ 40);
    int stoneDiam = std::max(1, ((cellDim * 19 * 2)/ 40));

    // bitmaps
    wxBitmap wstone = wxBitmap(m_whiteStone.Scale(stoneDiam, stoneDiam, wxIMAGE_QUALITY_HIGH));
    wxBitmap bstone = wxBitmap(m_blackStone.Scale(stoneDiam, stoneDiam, wxIMAGE_QUALITY_HIGH));

    // emtpy fill
    wxBrush ebrush(*wxBLACK, wxTRANSPARENT);
    
    // board outline
    dc.SetBrush(ebrush);
    dc.SetPen(penThick);
    dc.DrawRectangle(cellDim, cellDim, 
                     cellDim * (boardSize - 1), cellDim * (boardSize - 1));                

    // board lines            
    for (int y = 0; y < boardSize - 1; y++) {
        for (int x = 0; x < boardSize - 1; x++) {
            int xoff = cellDim + x * cellDim;
            int yoff = cellDim + y * cellDim;
            dc.SetPen(penThin);
            dc.SetBrush(ebrush);
            dc.DrawRectangle(xoff - 1, yoff - 1, cellDim + 1, cellDim + 1);
            if (m_State->board.starpoint(boardSize, x, y)) {
                dc.SetPen(penEmpty);
                dc.SetBrush(bbrush);
                dc.DrawCircle(xoff, yoff, std::max(1, (stoneSize/7)+1));
            }
        }
    }  
    
    // board coordinates
    int coordFontSize = cellDim / 4;
    int pvFontSize = (int)(cellDim / 2.5f);
    wxFont cfont(coordFontSize, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    wxFont pvfont(pvFontSize, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    dc.SetFont(cfont);
    dc.SetBackgroundMode(wxTRANSPARENT);
    dc.SetTextForeground(*wxBLACK);
    dc.SetTextBackground(*wxWHITE);
    for (int y = 0; y < boardSize; y++) {
        int x = 0;
        int xoff = cellDim + (x - 1) * cellDim;
        int yoff = cellDim + y  * cellDim;   
        xoff = xoff + cellDim / 2 - coordFontSize;  
        yoff = yoff - coordFontSize; 
        int xoff2 = xoff + cellDim * boardSize;
        wxString text;
        text.Printf("%2d", boardSize - y);
        dc.DrawText(text, xoff, yoff);
        dc.DrawText(text, xoff2, yoff);
    }   
    for (int x = 0; x < boardSize; x++) {
        int y = 0;
        int yoff = cellDim + (y - 1) * cellDim;
        int xoff = cellDim + x  * cellDim;   
        yoff = yoff + cellDim / 2 - coordFontSize;  
        xoff = xoff - coordFontSize; 
        int yoff2 = yoff + cellDim * boardSize;
        wxString text;
        if (x < 25) {
            if (x < 8) {
                text.Printf(" %c", 'a' + x);
            } else {
                text.Printf(" %c", 'a' + x  + 1);
            }
        } else {
            int tmx = x - 25;
            if (tmx < 8) {
                text.Printf(" %c", 'A' + tmx);
            } else {
                text.Printf(" %c", 'A' + tmx  + 1);
            }
        }
        dc.DrawText(text, xoff, yoff);
        dc.DrawText(text, xoff, yoff2);  
    }      
    
    // moyo/territory/influence
    if (!m_showTerritory) {
        if (m_showMoyo) {
            doMoyo();
        } else if (m_showOwner) {
            doOwner();
        }
    }
    
    if (m_showMoyo || m_showTerritory) {
        wxBrush bmbrush(*wxBLACK, wxCROSSDIAG_HATCH);
        wxBrush wmbrush(*wxWHITE, wxCROSSDIAG_HATCH);          
        
        dc.SetPen(penEmpty);                
        
        for (int y = 0; y < boardSize; y++) {
            for (int x = 0; x < boardSize; x++) {           
                // engine board is inverted vertically
                int vtx = m_State->board.get_vertex(x, boardSize - y - 1);
                
                int xoff = (cellDim + x * cellDim) - 1;
                int yoff = (cellDim + y * cellDim) - 1;
                
                int xxoff = (xoff - (stoneDiam/2));
                int yyoff = (yoff - (stoneDiam/2));
                
                if (m_Hatch[vtx] == FastBoard::BLACK) {                               
                    dc.SetBrush(bmbrush);
                    dc.DrawRoundedRectangle(xxoff, yyoff, cellDim, cellDim, 0);
                } else if (m_Hatch[vtx] == FastBoard::WHITE) {                                
                    dc.SetBrush(wmbrush);
                    dc.DrawRoundedRectangle(xxoff, yyoff, cellDim, cellDim, 0);
                }
            }
        }    
    }

    // stones
    dc.SetBrush(rbrush);
    wxPen wDeadPenThick(*wxBLACK, 2, wxSOLID);
    wxPen bDeadPenThick(*wxWHITE, 2, wxSOLID);
    dc.SetFont(pvfont);

    for (int y = 0; y < boardSize; y++) {
        for (int x = 0; x < boardSize; x++) {           
            // engine board is inverted vertically
            int vtx = m_State->board.get_vertex(x, boardSize - y - 1);
            int cell = m_State->board.get_square(vtx);
            
            int xoff = (cellDim + x * cellDim) - 1;
            int yoff = (cellDim + y * cellDim) - 1;
            
            int xxoff = (xoff - (stoneDiam/2));
            int yyoff = (yoff - (stoneDiam/2));                        
            
            dc.SetPen(penThin);
            if (cell == FastBoard::BLACK) {
                dc.DrawBitmap(bstone, xxoff, yyoff, true);
            } else if (cell == FastBoard::WHITE) {
                dc.DrawBitmap(wstone, xxoff, yyoff, true);
            }  else if (m_showOwner) {
                float ratio = 2.0f * fabs(0.5f - m_Owner[vtx]);
                int miniDiam = (stoneDiam * ratio) - 1;
                if (miniDiam >= 3) {
                    int xxxoff = (xoff - (miniDiam/2));
                    int yyyoff = (yoff - (miniDiam/2));

                    wxImage* refStone = nullptr;
                    if (m_Owner[vtx] > 0.5f) {
                        refStone = &m_blackStone;
                    } else {
                        refStone = &m_whiteStone;
                    }
                    wxBitmap mini = wxBitmap(refStone->Scale(miniDiam, miniDiam,
                                                             wxIMAGE_QUALITY_HIGH));
                    dc.DrawBitmap(mini, xxxoff, yyyoff, true);
                }
            }

            if (cell == FastBoard::EMPTY) {
               // Part of the mainline
                if (m_PV[vtx] > 0) {
                    wxString text;
                    text.Printf("%d", m_PV[vtx]);
                    wxRect rect = dc.GetTextExtent(text);
                    int cx = xoff - (rect.GetWidth() / 2);
                    int cy = yoff - (rect.GetHeight() / 2);
                    dc.SetTextForeground(*wxWHITE);                    
                    dc.DrawText(text, cx-1, cy-1);
                    dc.DrawText(text, cx+1, cy+1);
                    dc.DrawText(text, cx-1, cy+1);
                    dc.DrawText(text, cx+1, cy-1);
                    dc.SetTextForeground(*wxBLACK);
                    dc.DrawText(text, cx, cy);
                }
            } else if (cell != FastBoard::EMPTY) {
                if (m_State->get_last_move() == vtx) {
                    dc.DrawCircle(xoff, yoff, stoneSize/3);
                }
            }

            int bxoff = (xoff - (cellDim/2));
            int byoff = (yoff - (cellDim/2));
            
            if (m_showTerritory) {
                // dead stone
                if ((cell == FastBoard::BLACK && m_Hatch[vtx] == FastBoard::WHITE)
                  ||(cell == FastBoard::WHITE && m_Hatch[vtx] == FastBoard::BLACK)) {
                    if (cell == FastBoard::BLACK) {
                        dc.SetPen(bDeadPenThick);  
                    } else {
                        dc.SetPen(wDeadPenThick);  
                    }
                    dc.DrawLine(bxoff, yyoff, bxoff+cellDim, byoff+cellDim);
                    dc.DrawLine(bxoff+cellDim, byoff, bxoff, byoff+cellDim);
                }
            }
        }
    }              
        
    dc.SetBrush(wxNullBrush);
    dc.SetPen(wxNullPen);  
    dc.SetFont(wxNullFont);          
}

void TBoardPanel::doErase(wxEraseEvent& event) {    
    //event.Skip();
}

void TBoardPanel::doLeftMouse(wxMouseEvent& event) {
    int startX = event.GetX();
    int startY = event.GetY();
    
    wxLogDebug("Left down at %d %d", startX, startY);
    
    if (m_State == NULL) {
        wxLogDebug("Click on empty board");
        return;
    }
    
    if (m_State->get_last_move() == FastBoard::RESIGN) {
        wxLogDebug("Game has been resigned");
        return;
    }
    
    if (m_stateLock) {
        wxLogDebug("Click on locked state");
        return;
    } 
    
    if (m_State->get_to_move() == m_playerColor) {    
        int boardSize = m_State->board.get_boardsize();
        
        int corrX = startX - (m_cellDim / 2);
        int corrY = startY - (m_cellDim / 2);
     
        int cellX = corrX / m_cellDim;
        int cellY = corrY / m_cellDim;
        
        if (cellX >= boardSize) cellX = boardSize - 1;
        if (cellY >= boardSize) cellY = boardSize - 1;
        
        // engine board is inverted vertically        
        cellY = boardSize - cellY - 1;
     
        int vtx = m_State->board.get_vertex(cellX, cellY);                
        
        if (m_State->legal_move(vtx)) {
            m_State->play_move(vtx);                                                         
            
            wxCommandEvent event(EVT_NEW_MOVE, GetId());
            event.SetEventObject(this);                        
            ::wxPostEvent(GetEventHandler(), event);
            
            Refresh();
        }                   
        
    } else {        
        wxLogDebug("It's not your move!");
    }
    
    event.Skip();
}

void TBoardPanel::setShowTerritory(bool val) {
    m_showTerritory = val;
    
    Refresh();
}

void TBoardPanel::setShowInfluence(bool val) {
    m_showOwner = val;
    
    Refresh();
}

void TBoardPanel::setShowMoyo(bool val) {
    m_showMoyo = val;
    
    Refresh();
}

bool TBoardPanel::getShowOwner() {
    return m_showOwner;
}

bool TBoardPanel::getShowMoyo() {
    return m_showMoyo;
}

void TBoardPanel::doMoyo() {
    std::vector<int> moyo = m_State->board.moyo();
    
    m_Hatch.resize(FastBoard::MAXSQ);    
    std::fill(m_Hatch.begin(), m_Hatch.end(), FastBoard::EMPTY);
    
    for (int i = 0; i < moyo.size(); i++) {
        if (moyo[i] > 0) {
            m_Hatch[i] = FastBoard::BLACK;
        } else if (moyo[i] < 0) {
            m_Hatch[i] = FastBoard::WHITE;
        }
    }
}

void TBoardPanel::doOwner() {
    if (!MCOwnerTable::get_MCO()->is_primed()) {
        Playout::mc_owner(*m_State, 32);
    }

    m_Owner.resize(FastBoard::MAXSQ);
    std::fill(m_Owner.begin(), m_Owner.end(), 0.5f);

    int boardsize = m_State->board.get_boardsize();

    for (int x = 0; x < boardsize; x++) {
        for (int y = 0; y < boardsize; y++) {
            int vertex = m_State->board.get_vertex(x, y);
            m_Owner[vertex] =
                MCOwnerTable::get_MCO()->get_blackown(FastBoard::BLACK, vertex);
        }
    }
}

void TBoardPanel::doTerritory() {
    std::vector<int> map = m_State->final_score_map();
   
    m_Hatch.resize(FastBoard::MAXSQ);    
    std::fill(m_Hatch.begin(), m_Hatch.end(), FastBoard::EMPTY);
    
    for (int i = 0; i < map.size(); i++) {
        if (map[i] == FastBoard::BLACK) {
            m_Hatch[i] = FastBoard::BLACK;
        } else if (map[i] == FastBoard::WHITE) {
            m_Hatch[i] = FastBoard::WHITE;
        }
    }     
}

void TBoardPanel::lockState() {
    m_stateLock = true;
}

void TBoardPanel::unlockState() {
    m_stateLock = false;
}

void TBoardPanel::doKeyDown(wxKeyEvent& event) {
    auto keycode = event.GetKeyCode();
    if (keycode == WXK_LEFT || keycode == WXK_RIGHT) {
        static_cast<MainFrame*>(GetParent())->doKeyDown(event);
    } else {
        event.Skip();
    }
}

void TBoardPanel::doDisplayMainline(wxCommandEvent& event) {
    wxString pv = event.GetString();

    // Clear past PV
    std::fill(m_PV.begin(), m_PV.end(), 0);
    int pv_move_counter = 0;

    wxStringTokenizer tokenizer(pv);
    while (tokenizer.HasMoreTokens()) {
        pv_move_counter++;

        wxString move = tokenizer.GetNextToken();
        int vertex = m_State->board.text_to_move(move.ToStdString());
        m_PV[vertex] = pv_move_counter;
    }

    Refresh();
}

void TBoardPanel::clearViz() {
    std::fill(m_PV.begin(), m_PV.end(), 0);
    std::fill(m_Hatch.begin(), m_Hatch.end(), FastBoard::EMPTY);
    std::fill(m_Owner.begin(), m_Owner.end(), 0.5f);
}