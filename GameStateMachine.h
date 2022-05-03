// GameStateMachine.h
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef GAMESTATEMACHINE_H
#define GAMESTATEMACHINE_H 1

#include <vector>

#include "GameState.h"


class GameStateMachine {

 public:
    void pushState(GameState* pState);
    void changeState(GameState* pState);
    void popState();

    void update();
    void render();


 private:
    std::vector<GameState*> m_gameStates;
    std::vector<GameState*> m_leftStates; /* GameState pointers for freeing after their
					     update finishes
					   */

    GameState* m_NextState;	/* handle for new state to change
				   after cleaning the previous state
				   and only after that entering to 
				   this state
				 */
};



#endif // GAMESTATEMACHINE_H
//////////////////////////////////////////////////////////////////////
// $Log:$
//
