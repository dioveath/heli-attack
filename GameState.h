// GameState.h
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef GAMESTATE_H
#define GAMESTATE_H 1


#include <vector>
#include <string>

class GameState {
 public:
    virtual void update()=0;
    virtual void render()=0;

    virtual bool onEnter()=0;
    virtual bool onExit()=0;

    virtual std::string getStateID() const = 0;

 protected:
    std::vector<std::string> m_textureIDs;
    /* std::vector<GameObje */

};


#endif // GAMESTATE_H
//////////////////////////////////////////////////////////////////////
// $Log:$
//
