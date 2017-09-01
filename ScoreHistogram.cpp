#include "ScoreHistogram.h"
#include "MainFrame.h"
#include "TScorePanel.h"

std::vector<std::tuple<int, float, float, float>> ScoreHistogram::m_scores;

ScoreHistogram::ScoreHistogram( wxWindow* parent )
:
TScoreHistogram( parent )
{
    Bind(wxEVT_EVALUATION_UPDATE, &ScoreHistogram::doNewScore, this);
    Bind(wxEVT_SET_MOVENUM, [=](wxCommandEvent& event) {
        m_DrawPanel->GetEventHandler()->AddPendingEvent(event);
    });

    wxPersistentRegisterAndRestore(this, "ScoreHistogram");
}

void ScoreHistogram::doNewScore(wxCommandEvent& event) {
    if (!event.GetClientData()) return;

    auto score_data = reinterpret_cast<std::tuple<int, float, float, float>*>(event.GetClientData());
    std::unique_ptr<std::remove_pointer<decltype(score_data)>::type> scores(score_data);
    int movenum = std::get<0>(*scores);

    auto it = std::find_if(m_scores.begin(), m_scores.end(),
        [=](auto const& n) {
            return std::get<0>(n) == movenum;
        }
    );

    if (it != m_scores.end()) {
        *it = *scores;
    } else {
        m_scores.push_back(*scores);
    }
    Refresh();
}

void ScoreHistogram::ClearHistogram() {
    m_scores.clear();
}
