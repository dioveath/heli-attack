// GameOverState.h
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H 1


#include <vector>

#include "GameState.h"
#include "GameObject.h"


class GameOverState : public GameState {

 public:
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const { return s_stateID; }

 private:
    static const std::string s_stateID;

    std::vector<GameObject*> m_gameObjects;


};


#endif // GAMEOVERSTATE_H
//////////////////////////////////////////////////////////////////////
// $Log:$
//
