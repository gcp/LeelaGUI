#include "stdafx.h"

#include "EngineThread.h"
#include "UCTSearch.h"
#include "MainFrame.h"
#include <boost/thread.hpp>
#include <boost/thread/detail/tss_hooks.hpp>

TEngineThread::TEngineThread(GameState * state, MainFrame * frame)
    : wxThread(wxTHREAD_JOINABLE)
 {
    m_state = state;
    m_frame = frame;
    m_maxvisits = 0;
    m_runflag = true;
    m_nopass = false;
    m_quiet = false;
    m_nets = true;
}

void * TEngineThread::Entry() {
    {
        GameState work_state(*m_state);
        std::unique_ptr<UCTSearch> search(new UCTSearch(work_state));

        int who = m_state->get_to_move();
        search->set_playout_limit(m_maxvisits);
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
    }

    return NULL;
}

void TEngineThread::OnExit() {
    if (!m_analyseflag) {
        wxQueueEvent(m_frame->GetEventHandler(),
                     new wxCommandEvent(EVT_NEW_MOVE));
    }
    boost::on_thread_exit();
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

void TEngineThread::set_nopass(bool flag) {
    m_nopass = flag;
}

void TEngineThread::set_quiet(bool flag) {
    m_quiet = flag;
}

void TEngineThread::set_nets(bool flag) {
    m_nets = flag;
}