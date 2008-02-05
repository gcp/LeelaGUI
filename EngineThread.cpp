#include "stdafx.h"

#include "EngineThread.h"
#include "UCTSearch.h"
#include "MainFrame.h"

TEngineThread::TEngineThread(GameState * state, wxSemaphore * sema, MainFrame * frame) {
    m_state = state;
    m_sema = sema;
    m_frame = frame;
    m_maxvisits = 0;
    m_runflag = true;    
}

void * TEngineThread::Entry() {     
    {
        m_frame->SetStatusBar(_("Engine thinking..."), 1);
        
        std::auto_ptr<UCTSearch> search(new UCTSearch(*m_state));
                
        int who = m_state->get_to_move();
        search->set_visit_limit(m_maxvisits);
        search->set_runflag(&m_runflag);
        
        int move;
        if (m_resigning) {
            move = search->think(who);
        } else {
            move = search->think(who, UCTSearch::NORESIGN);
        }        
        m_state->play_move(who, move);                                
        
        m_sema->Post();                
        
        wxCommandEvent event(EVT_NEW_MOVE);                               
        ::wxPostEvent(m_frame->GetEventHandler(), event);                
    }

    return NULL;
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