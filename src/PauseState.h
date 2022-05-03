// PauseState.h
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef PAUSESTATE_H
#define PAUSESTATE_H 1


#include "MenuState.h"
#include <vector>


class GameObject;


class PauseState : public MenuState {

 public:
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    std::string getStateID() const { return s_pauseID; }
    
    void setCallbacks(const std::vector<Callback>& callbacks);

 private:
    static const std::string s_pauseID;

    std::vector<GameObject*> m_gameObjects;

    static void s_pauseToMain();
    static void s_resumePlay();
    
};



#endif // PAUSESTATE_H
//////////////////////////////////////////////////////////////////////
// $Log:$
//
