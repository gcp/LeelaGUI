#include "stdafx.h"

#include "EngineThread.h"
#include "UCTSearch.h"
#include "MainFrame.h"

TEngineThread::TEngineThread(GameState * state, wxSemaphore * sema, TMainFrame * frame) {
    m_state = state;
    m_sema = sema;
    m_frame = frame;
}

void * TEngineThread::Entry() {     
    {
        std::auto_ptr<UCTSearch> search(new UCTSearch(*m_state));

        int who = m_state->get_to_move();
        int move = search->think(who, UCTSearch::NOPASS);
        m_state->play_move(who, move);                
        
        wxCommandEvent event(EVT_NEW_MOVE);                               
        ::wxPostEvent(m_frame->GetEventHandler(), event);
        
        m_sema->Post();
    }

    return NULL;
}
