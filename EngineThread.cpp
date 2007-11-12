#include "stdafx.h"

#include "EngineThread.h"
#include "UCTSearch.h"
#include "MainFrame.h"

TEngineThread::TEngineThread(GameState * state, wxSemaphore * sema, TMainFrame * frame) {
    m_state = state;
    m_sema = sema;
    m_frame = frame;
    m_maxvisits = 0;
}

void * TEngineThread::Entry() {     
    {
        std::auto_ptr<UCTSearch> search(new UCTSearch(*m_state));

        int who = m_state->get_to_move();
        search->set_visit_limit(m_maxvisits);
        int move = search->think(who);
        m_state->play_move(who, move);                
        
        wxCommandEvent event(EVT_NEW_MOVE);                               
        ::wxPostEvent(m_frame->GetEventHandler(), event);
        
        m_sema->Post();
    }

    return NULL;
}

void TEngineThread::limit_visits(int visits) {
    m_maxvisits = visits;
}