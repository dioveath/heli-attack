/* 

   PauseState.cpp

   Author: Saroj Rai @ Charicha 
   Created On: Thursday, 26 July 2018.

*/

#include "Game.h"
#include "MainMenuState.h"
#include "PauseState.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "MenuButton.h"
#include "Camera.h"

#include "StateParser.h"

// $Log:$ //
//


const std::string PauseState::s_pauseID = "PAUSE";


void PauseState::update(){
    for(int i = 0; i < m_gameObjects.size(); i++){
	m_gameObjects[i]->update();
    }
}


void PauseState::render(){
    for(int i = 0; i < m_gameObjects.size(); i++){
	m_gameObjects[i]->render();
    }
}


bool PauseState::onEnter(){
    
    TheStateParser::Instance()->parseState("test.xml", s_pauseID,
					   &m_gameObjects,
					   &m_textureIDs);


    m_callbacks.push_back(0);
    m_callbacks.push_back(s_pauseToMain);
    m_callbacks.push_back(s_resumePlay);

    setCallbacks(m_callbacks);

    TheCamera::Instance()->reset();

    std::cout << "Entering pause state..!\n";
    return true;
}


bool PauseState::onExit(){
    

    for(int i = 0; i < m_gameObjects.size(); i++){
	m_gameObjects[i]->clean();
	delete m_gameObjects[i];
    }
    m_gameObjects.clear();


    for(int i = 0; i < m_textureIDs.size(); i++){
	TheTextureManager::Instance()->clearFromTextureMap(m_textureIDs[i]);
    }
    m_callbacks.clear();
    std::cout << "Exiting from pause state..!\n";


    return true;
}


void PauseState::s_pauseToMain(){
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
}


void PauseState::s_resumePlay(){
    TheGame::Instance()->getStateMachine()->popState();
}


void PauseState::setCallbacks(const std::vector<Callback>& callbacks){
    for(int i = 0; i < m_gameObjects.size(); i++){
	if(dynamic_cast<MenuButton*>(m_gameObjects[i])){
	    MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
	    pButton->setCallback(callbacks[pButton->getCallbackID()]);
	}
    }
}
