// PlayState.h
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef PLAYSTATE_H
#define PLAYSTATE_H 1


#include <vector>

#include "GameState.h"
#include "SDLGameObject.h"



class PlayState : public GameState {

 public:
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const { return s_playID; }

    bool checkCollision(SDLGameObject*, SDLGameObject*);

 private:
    static const std::string s_playID;

    std::vector<GameObject*> m_gameObjects;

};


#endif // PLAYSTATE_H
//////////////////////////////////////////////////////////////////////
// $Log:$
//
