#ifndef ENGINETHREAD_H
#define ENGINETHREAD_H

#include "stdafx.h"

#include "GameState.h"
#include "MainFrame.h"

class TEngineThread : public wxThread {
    public:
        TEngineThread(GameState * gamestate, wxSemaphore * sema, TMainFrame * frame);
        virtual void * Entry();
    private:
        GameState * m_state; 
        wxSemaphore * m_sema;
        TMainFrame * m_frame;   
};

#endif