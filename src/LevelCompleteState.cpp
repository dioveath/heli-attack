/* 

   LevelCompleteState.cpp

   Author: Saroj Rai @ Charicha 
   Created On: Monday, 13 August 2018.

*/

#include "LevelCompleteState.h"
#include "Game.h"
#include "StateParser.h"
#include "Camera.h"
#include "InputHandler.h"
#include "TextureManager.h"

#include "PlayState.h"


// $Log:$ //
//


const std::string LevelCompleteState::s_levelCompleteID = "LEVELCOMPLETE";


void LevelCompleteState::update(){
    for(int i = 0; i < m_gameObjects.size(); i++){
	m_gameObjects[i]->update();
    }

    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE)){
	TheGame::Instance()->getStateMachine()->changeState(new PlayState());
    }
}


void LevelCompleteState::render(){
    for(int i = 0; i < m_gameObjects.size(); i++){
	m_gameObjects[i]->render();
    }
}


bool LevelCompleteState::onEnter(){

    std::cout << "Entering LevelCompleteState..\n";

    TheStateParser::Instance()->parseState("test.xml", s_levelCompleteID,
					   &m_gameObjects,
					   &m_textureIDs);

    TheCamera::Instance()->reset();
    return true;
}


bool LevelCompleteState::onExit(){
    std::cout << "Exiting LevelCompleteState..\n";

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
	
