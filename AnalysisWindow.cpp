#include "stdafx.h"
#include "AnalysisWindow.h"
#include "Utils.h"

#include <boost/foreach.hpp>

wxDEFINE_EVENT(wxEVT_ANALYSIS_UPDATE, wxCommandEvent);

AnalysisWindow::AnalysisWindow( wxWindow* parent )
    : TAnalysisWindow(parent) {

    Bind(wxEVT_ANALYSIS_UPDATE, &AnalysisWindow::doUpdate, this);

    Utils::setAnalysisQueue(this->GetEventHandler(), wxEVT_ANALYSIS_UPDATE);

    m_moveGrid->SetCellValue(0, 0, "pass");
    m_moveGrid->SetCellValue(0, 1, "0");
    m_moveGrid->SetCellValue(0, 2, "-");
    m_moveGrid->SetCellValue(0, 3, "0.0");
    m_moveGrid->SetCellValue(0, 4, "pass pass");
    m_moveGrid->AutoSize();
    m_moveGrid->SetSelectionMode(wxGrid::wxGridSelectRows);

    int parentWidth, parentHeight;
    parent->GetSize(&parentWidth, &parentHeight);
    int parentX, parentY;
    parent->GetPosition(&parentX, &parentY);

    wxRect dispRect = wxDisplay(wxDisplay::GetFromWindow(parent)).GetClientArea();

    if (parentX + parentWidth + 10 < dispRect.GetWidth()) {
        SetSize(parentX + parentWidth, parentY,
                wxDefaultCoord, wxDefaultCoord, wxSIZE_USE_EXISTING);
    } else {
        CentreOnParent();
    }
}

void AnalysisWindow::doClose( wxCloseEvent& event ) {
    Utils::setAnalysisQueue(nullptr, 0);
    // Don't unbind the event handler. Destroy will empty it
    // and free any pending events with data.
    event.Skip();
}

void AnalysisWindow::doUpdate(wxCommandEvent& event) {
    void* rawdataptr = event.GetClientData();
    if (!rawdataptr) return;

    using TRowVector = std::vector<std::pair<std::string, std::string>>;
    using TDataVector = std::vector<TRowVector>;

    // Take ownership of the data
    std::unique_ptr<TDataVector> data(reinterpret_cast<TDataVector*>(rawdataptr));

    size_t rows = data->size();
    if (rows == 0) return;

    size_t cols = data->at(0).size();
    if (cols == 0) return;

    size_t oldrows = m_moveGrid->GetNumberRows();
    size_t oldcols = m_moveGrid->GetNumberCols();

    if (rows != oldrows || cols != oldcols) {
        m_moveGrid->SetTable(new wxGridStringTable(rows, cols), true, wxGrid::wxGridSelectRows);
    }

    for (size_t currrow = 0; currrow < data->size(); currrow++) {
        const auto& cellPair = (*data)[currrow];
        for (size_t currcol = 0; currcol < cellPair.size(); currcol++) {
            const auto label = wxString(cellPair[currcol].first);
            const auto value = wxString(cellPair[currcol].second);

            const wxString& oldlabel = m_moveGrid->GetColLabelValue(currcol);

            if (oldlabel.Cmp(label) != 0) {
                m_moveGrid->SetColLabelValue(currcol, label);
                mHasAutoSized = false;
            }

            // Check whether it's an integer number
            unsigned long lval;
            if (value.ToULong(&lval)) {
                m_moveGrid->SetColFormatNumber(currcol);
            } else {
                // Check whether it's a double number
                double dval;
                if (value.ToCDouble(&dval)) {
                    m_moveGrid->SetColFormatFloat(currcol, 7, 2);
                }
            }

            if (label.Cmp("Move") == 0) {
                m_moveGrid->SetCellAlignment(currrow, currcol,
                                             wxALIGN_CENTRE, wxALIGN_CENTRE);
            }
            if (label.Cmp("PV") == 0) {
                wxString padValue(value);
                // Make sure column fits at least 5 moves (3+1 chars)
                if (value.Length() < 5*4) {
                    padValue.Pad(20 - value.Length());
                }
                m_moveGrid->SetCellValue(currrow, currcol, padValue);
                m_moveGrid->AutoSizeColumn(currcol);
            } else {
                m_moveGrid->SetCellValue(currrow, currcol, value);
            }
        }
    }

    if (!mHasAutoSized) {
        m_moveGrid->AutoSize();
        // Make sure we won't obscure anything when scrollbar appears
        wxSize bestSize = GetBestSize();
        bestSize.IncBy(0, wxSystemSettings::GetMetric(wxSYS_HSCROLL_Y));
        SetSize(bestSize);
        mHasAutoSized = true;
    }

    // Colours can be specified for grid cell contents
    //grid->SetCellValue(3, 3, "green on grey");
    //grid->SetCellTextColour(3, 3, *wxGREEN);
    //grid->SetCellBackgroundColour(3, 3, *wxLIGHT_GREY);
}

void AnalysisWindow::doDeselect(wxGridEvent& event) {
    m_moveGrid->ClearSelection();

    wxCommandEvent* cmd = new wxCommandEvent(wxEVT_DISPLAY_MAINLINE);
    cmd->SetString("");
    GetParent()->GetEventHandler()->QueueEvent(cmd);
}

void AnalysisWindow::doLeftClick(wxGridEvent& event) {
    int row = event.GetRow();
    int col = event.GetCol();

    if (m_moveGrid->IsInSelection(row, col)) {
        doDeselect(event);
    } else {
        m_moveGrid->SelectRow(row);
        int gridCols = m_moveGrid->GetNumberCols();
        wxString pv;

        for (int i = 0; i < gridCols; i++) {
            if (m_moveGrid->GetColLabelValue(i).Cmp("PV") == 0) {
                pv = m_moveGrid->GetCellValue(row, i);
                break;
            }
        }

        wxCommandEvent* cmd = new wxCommandEvent(wxEVT_DISPLAY_MAINLINE);
        cmd->SetString(pv);
        GetParent()->GetEventHandler()->QueueEvent(cmd);
    }
}
