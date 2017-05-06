#include "ScoreHistogram.h"
#include "MainFrame.h"

ScoreHistogram::ScoreHistogram( wxWindow* parent )
:
TScoreHistogram( parent )
{
    Bind(wxEVT_EVALUATION_UPDATE, &ScoreHistogram::doNewScore, this);
}

void ScoreHistogram::doNewScore(wxCommandEvent& event) {
    if (!event.GetClientData()) return;

    auto scores = reinterpret_cast<std::tuple<int, float, float, float>*>(event.GetClientData());
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