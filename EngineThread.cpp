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
    m_nopass = false;   
}

void * TEngineThread::Entry() {     
    {
        m_frame->SetStatusBar(_("Engine thinking..."), 1);
        
        std::auto_ptr<UCTSearch> search(new UCTSearch(*m_state));
                
        int who = m_state->get_to_move();
        search->set_visit_limit(m_maxvisits);
        search->set_runflag(&m_runflag);
        search->set_analyzing(m_analyseflag);        
        
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

void TEngineThread::set_analyzing(bool flag) {
    m_analyseflag = flag;
}

void TEngineThread::set_nopass(bool flag) {
    m_nopass = flag;
}