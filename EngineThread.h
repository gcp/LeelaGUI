#ifndef ENGINETHREAD_H
#define ENGINETHREAD_H

#include "stdafx.h"

#include "GameState.h"

class TMainFrame;

class TEngineThread : public wxThread {
    public:
        TEngineThread(GameState * gamestate, wxSemaphore * sema, TMainFrame * frame);
        void limit_visits(int visits);
        virtual void * Entry();
    private:
        GameState * m_state; 
        wxSemaphore * m_sema;
        TMainFrame * m_frame; 
        int m_maxvisits;  
};

#endif