#include "stdafx.h"
#include "TScorePanel.h"
#include "ScoreHistogram.h"
#include "MainFrame.h"

BEGIN_EVENT_TABLE(TScorePanel, wxPanel)
    EVT_KEY_DOWN(TScorePanel::doKeyDown)
    EVT_PAINT(TScorePanel::doPaint)
    EVT_ERASE_BACKGROUND(TScorePanel::doErase)
    EVT_MOUSE_EVENTS(TScorePanel::doMouse)
END_EVENT_TABLE()

TScorePanel::TScorePanel(wxWindow *parent, wxWindowID winid, const wxPoint& pos,
    const wxSize& size, long style,const wxString& name)
    : wxPanel(parent, winid, pos, size, style, name) {

    Bind(wxEVT_SET_MOVENUM, [=](wxCommandEvent& event) {
        m_CurrentMove = event.GetInt();
        Refresh();
    });

    SetBackgroundStyle(wxBG_STYLE_PAINT);
}

using scoretuple_t = std::tuple<int, float, float, float>;

static float tuple_getter(scoretuple_t tuple, int idx) {
    if (idx == 1) {
        return std::get<1>(tuple);
    } else if (idx == 2) {
        return std::get<2>(tuple);
    } else {
        assert(idx == 3);
        return std::get<3>(tuple);
    }
}

void TScorePanel::doPaint(wxPaintEvent& event) {
    wxAutoBufferedPaintDC dc(this);
    PrepareDC(dc);

    wxSize sz = GetClientSize();

    // Get Data
    auto parent = static_cast<ScoreHistogram*>(GetParent());
    auto data = parent->m_scores;
    // Sort by move number
    std::sort(data.begin(), data.end());

    // Create graphics context from it
    wxGraphicsContext *gc = wxGraphicsContext::Create(dc);
    if (gc) {
        wxDouble width = sz.GetWidth(), height = sz.GetHeight();
        // Background
        gc->SetPen(*wxWHITE_PEN);
        gc->SetBrush(*wxWHITE_BRUSH);
        wxGraphicsPath path = gc->CreatePath();
        path.AddRectangle(0, 0, width, height);
        gc->StrokePath(path);
        gc->FillPath(path);

        // Centerline
        wxPen centerPen(*wxGREY_PEN);
        centerPen.SetWidth(2);
        gc->SetPen(centerPen);
        path = gc->CreatePath();
        path.MoveToPoint(0.0, height/2.0);
        path.AddLineToPoint(width, height/2.0);
        gc->StrokePath(path);

        // Score lines
        if (data.size() > 1) {
            double max_move = std::get<0>(data.back());
            auto pen_array = { wxBLACK_PEN, wxBLUE_PEN, wxRED_PEN  };
            int tuple_idx = 1;

            for (auto const& pen : pen_array) {
                gc->SetPen(*pen);
                path = gc->CreatePath();
                // Starting point
                if (tuple_getter(data[0], tuple_idx) >= 0.0) {
                    path.MoveToPoint((std::get<0>(data[0]) / max_move) * width,
                                     (1.0 - tuple_getter(data[0], tuple_idx)) * height);
                } else {
                    // Not valid, assume 0.5 for start
                    path.MoveToPoint((std::get<0>(data[0]) / max_move) * width,
                                     0.5 * height);
                }
                for (auto const& scoretuple: data) {
                    if (tuple_getter(scoretuple, tuple_idx) >= 0.0) {
                        path.AddLineToPoint((std::get<0>(scoretuple) / max_move) * width,
                                            (1.0 - tuple_getter(scoretuple, tuple_idx)) * height);
                    }
                }
                gc->StrokePath(path);
                tuple_idx++;
            }
            // Current move
            if (m_CurrentMove >= 0) {
                double current_x = ((double)m_CurrentMove/max_move) * width;
                gc->SetPen(*wxGREY_PEN);
                path = gc->CreatePath();
                path.MoveToPoint(current_x, 0.0);
                path.AddLineToPoint(current_x, height);
                gc->StrokePath(path);
            }
        }

        // Legend
        wxFont colfont(height / 30.0, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
        wxFont legfont(height / 40.0, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
        gc->SetFont(colfont, *wxBLACK);
        wxDouble fontheight, fontheight2;
        gc->GetTextExtent(_T("WHITE"), NULL, &fontheight);
        gc->DrawText(_T("BLACK"), 0.0, 0.0);
        gc->DrawText(_T("WHITE"), 0.0, height - fontheight);
        gc->SetFont(legfont, *wxBLACK);
        gc->GetTextExtent(_T("Combined"), NULL, &fontheight2);
        gc->DrawText(_T("Combined"), 0.0, fontheight * 1.1);
        gc->SetFont(legfont, *wxBLUE);
        gc->DrawText(_T("Monte Carlo"), 0.0, fontheight * 1.1 + fontheight2 * 1.2);
        gc->SetFont(legfont, *wxRED);
        gc->DrawText(_T("Network"), 0.0, fontheight * 1.1 + fontheight2 * 2.4);

        delete gc;
    }
}

void TScorePanel::doErase(wxEraseEvent& event) {
    //event.Skip();
}

void TScorePanel::doMouse(wxMouseEvent& event) {
    if (event.LeftDown() || (event.Dragging() && event.LeftIsDown())) {
        int startX = event.GetX();
        int startY = event.GetY();

        wxSize sz = GetClientSize();

        auto parent = static_cast<ScoreHistogram*>(GetParent());
        auto data = parent->m_scores;
        // Sort by move number
        std::sort(data.begin(), data.end());

        if (!data.empty()) {
            float max_move = std::get<0>(data.back());
            int move_selected = std::lround(((float)startX / (float)sz.GetWidth()) * max_move);

            auto my_window_parent = GetParent();
            auto mainframe =  my_window_parent->GetParent();
            wxCommandEvent* cmd = new wxCommandEvent(wxEVT_SET_MOVENUM);
            cmd->SetInt(move_selected);
            mainframe->GetEventHandler()->QueueEvent(cmd);

            m_CurrentMove = move_selected;
            Refresh();
        }
    }

    event.Skip();
}

void TScorePanel::doKeyDown(wxKeyEvent& event) {
    event.Skip();
}
