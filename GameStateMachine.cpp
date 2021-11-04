/* 

   GameStateMachine.cpp

   Author: Saroj Rai @ Charicha 
   Created On: Friday, 20 July 2018.

*/

#include "GameStateMachine.h"
#include <iostream>

// $Log:$ //
//


void GameStateMachine::pushState(GameState* pState){
    m_gameStates.push_back(pState);
    if(!m_gameStates.back()->onEnter()){
	popState();
    }
}


void GameStateMachine::changeState(GameState* pState){
    while(!m_gameStates.empty()){
	if(m_gameStates.back()->getStateID() == pState->getStateID()) return;

	m_leftStates.push_back(m_gameStates.back());
	m_gameStates.pop_back();
    }


    // if(!pState->onEnter()){
    // 	std::cout << "Entering " << m_leftStates.back()->getStateID() << " failed..!\n";
    // 	return;
    // }
    
    // m_gameStates.push_back(pState);
    m_NextState = pState;
}


void GameStateMachine::popState(){
    if(!m_gameStates.empty()){
	    m_leftStates.push_back(m_gameStates.back());
	    m_gameStates.pop_back();
    }
}


void GameStateMachine::update(){
    
    // std::cout << "\nCurrent State Machine \n\n";

    // for(int i = m_gameStates.size() - 1; i >= 0; i--){
    // 	std::cout << " | " << m_gameStates[i]->getStateID() << " | "<< std::endl;
    // }

    // std::cout << "\n\n";

    while(!m_leftStates.empty()){
	m_leftStates.back()->onExit();
	std::cout << "deleting " << m_leftStates.back()->getStateID() << " ...!\n";
	delete m_leftStates.back();
	m_leftStates.pop_back();
    }

    if(m_NextState){
	if(m_NextState->onEnter()){
	    std::cout << "Entered " << m_NextState->getStateID() << std::endl;
	    m_gameStates.push_back(m_NextState);
	    m_NextState = 0;
	}
    }


    if(!m_gameStates.empty()){
	m_gameStates.back()->update();
    } else {
	std::cout << "state machine empty..!\n";
    }


}


void GameStateMachine::render(){
    if(!m_gameStates.empty()){
	m_gameStates.back()->render();
    }
}


