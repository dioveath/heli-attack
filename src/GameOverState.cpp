/* 

   GameOverState.cpp

   Author: Saroj Rai @ Charicha 
   Created On: Thursday, 26 July 2018.

*/

#include "GameOverState.h"
#include "Game.h"
#include "StateParser.h"
#include "Camera.h"
#include "InputHandler.h"
#include "TextureManager.h"

#include "MainMenuState.h"

// $Log:$ //
//


const std::string GameOverState::s_stateID = "GAMEOVER";


void GameOverState::update() {
    for(int i = 0; i < m_gameObjects.size(); i++){
	m_gameObjects[i]->update();
    }

   if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)){
	TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
    }    
}


void GameOverState::render() {
    for(int i = 0; i < m_gameObjects.size(); i++){
	m_gameObjects[i]->render();
    }
}


bool GameOverState::onEnter(){
    TheStateParser::Instance()->parseState("test.xml", s_stateID,
					   &m_gameObjects,
					   &m_textureIDs);

    TheCamera::Instance()->reset();
    return true;
}


bool GameOverState::onExit(){

    for(int i = 0; i < m_gameObjects.size(); i++){
	m_gameObjects[i]->clean();
	delete m_gameObjects[i];
    }
    m_gameObjects.clear();

    for(int i = 0; i < m_textureIDs.size(); i++){
	TheTextureManager::Instance()->clearFromTextureMap(m_textureIDs[i]);
    }

    return true;

}
