// MenuState.h
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef MENUSTATE_H
#define MENUSTATE_H 1

#include "GameState.h"


typedef void (*Callback)();

class MenuState : public GameState {

 protected:
    virtual void setCallbacks(const std::vector<Callback>& callbacks)=0;
    
    std::vector<Callback> m_callbacks;
    
};


#endif // MENUSTATE_H
//////////////////////////////////////////////////////////////////////
// $Log:$
//
