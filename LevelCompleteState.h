// LevelCompleteState.h
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef LEVELCOMPLETESTATE_H
#define LEVELCOMPLETESTATE_H 1


#include <vector>


#include "GameState.h"
#include "GameObject.h"

class LevelCompleteState : public GameState {

 public:
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const { return s_levelCompleteID; }

 protected:
    static const std::string s_levelCompleteID;

    std::vector<GameObject*> m_gameObjects;

};



#endif // LEVELCOMPLETESTATE_H
//////////////////////////////////////////////////////////////////////
// $Log:$
//
