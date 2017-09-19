#include "stdafx.h"

#include <thread>
#include "EngineThread.h"
#include "UCTSearch.h"
#include "MainFrame.h"
#include "Utils.h"

TEngineThread::TEngineThread(const GameState& state, MainFrame * frame) {
    m_state = std::make_unique<GameState>(state);
    m_frame = frame;
    m_maxvisits = 0;
    m_runflag = true;
    m_nopass = false;
    m_quiet = false;
    m_nets = true;
    m_update_score = true;
}

void TEngineThread::Run() {
    auto Func = [this] {
        auto search = std::make_unique<UCTSearch>(*m_state);

        int who = m_state->get_to_move();
        if (m_analyseflag && !m_pondering) {
            search->set_playout_limit(0);
        } else {
            search->set_playout_limit(m_maxvisits);
        }
        search->set_runflag(&m_runflag);
        search->set_analyzing(m_analyseflag);
        search->set_quiet(m_quiet);
        search->set_use_nets(m_nets);

        int mode = UCTSearch::NORMAL;
        if (m_nopass) {
            mode = UCTSearch::NOPASS;
        }

        int move;
        if (m_resigning) {
            move = search->think(who, mode);
        } else {
            move = search->think(who, mode | UCTSearch::NORESIGN);
        }

        if (!m_analyseflag) {
            m_state->play_move(who, move);
        }

        if (m_update_score) {
            // Broadcast result from search
            auto event = new wxCommandEvent(wxEVT_EVALUATION_UPDATE);
            auto scores = search->get_scores();
            auto movenum = m_state->get_movenum();
            auto scoretuple = std::make_tuple(movenum,
                                              std::get<0>(scores),
                                              std::get<1>(scores),
                                              std::get<2>(scores));
            event->SetClientData((void*)new auto(scoretuple));

            wxQueueEvent(m_frame->GetEventHandler(), event);
        }

        if (!m_analyseflag) {
            wxQueueEvent(m_frame->GetEventHandler(),
                new wxCommandEvent(wxEVT_NEW_MOVE));
        }
    };

    m_tg.add_task(Func);
}

void TEngineThread::Wait() {
    m_tg.wait_all();
}

void TEngineThread::limit_visits(int visits) {
    m_maxvisits = visits;
}

void TEngineThread::stop_engine() {
    m_runflag = false;
}

void TEngineThread::set_resigning(bool res) {
    m_resigning = res;
}

void TEngineThread::set_analyzing(bool flag) {
    m_analyseflag = flag;
}

void TEngineThread::set_pondering(bool flag) {
    m_pondering = flag;
}

void TEngineThread::set_nopass(bool flag) {
    m_nopass = flag;
}

void TEngineThread::set_quiet(bool flag) {
    m_quiet = flag;
}

void TEngineThread::set_nets(bool flag) {
    m_nets = flag;
}

void TEngineThread::kill_score_update(void) {
    m_update_score = false;
}