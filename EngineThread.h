#ifndef ENGINETHREAD_H
#define ENGINETHREAD_H

#include "stdafx.h"
#include "GameState.h"

class MainFrame;

class TEngineThread : public wxThread {
    public:
        TEngineThread(GameState * gamestate, wxSemaphore * sema, MainFrame * frame);
        void limit_visits(int visits);
        void set_resigning(bool res);
        virtual void * Entry();
    private:
        GameState * m_state; 
        wxSemaphore * m_sema;
        MainFrame * m_frame; 
        int m_maxvisits;  
        bool m_resigning;
};

#endif