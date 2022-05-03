/* 

   MainMenuState.cpp

   Author: Saroj Rai @ Charicha 
   Created On: Wednesday, 1 August 2018.

*/

#include "MainMenuState.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "StateParser.h"
#include "Camera.h"
#include "AudioManager.h"

#include <iostream>


// $Log:$ //
//


const std::string MainMenuState::s_menuID = "MAINMENU";



void MainMenuState::update(){
    for(int i = 0; i < m_gameObjects.size(); i++)
	m_gameObjects[i]->update();
}


void MainMenuState::render(){
    for(int i = 0; i < m_gameObjects.size(); i++)
	m_gameObjects[i]->render();
}


bool MainMenuState::onEnter(){
    std::cout << "entering MainMenuState\n";

    m_MusicID = TheAudioManager::Instance()->LoadMusic("assets/DST_Announce.ogg");
    TheAudioManager::Instance()->PlayMusic(m_MusicID);

    m_callbacks.push_back(0);
    m_callbacks.push_back(s_menuToPlay);
    m_callbacks.push_back(s_exitFromMenu);


    TheStateParser::Instance()->parseState("test.xml", s_menuID, &m_gameObjects, &m_textureIDs);

    setCallbacks(m_callbacks);

    TheCamera::Instance()->reset();
    
    return true;
}


bool MainMenuState::onExit(){
    std::cout << "exiting MainMenuState\n";

    TheAudioManager::Instance()->ReleaseMusic(m_MusicID);


    for(int i = 0; i < m_gameObjects.size(); i++){
	m_gameObjects[i]->clean();
	delete m_gameObjects[i];
    }
    m_gameObjects.clear();

    for(int i = 0; i < m_textureIDs.size(); i++){
	TheTextureManager::Instance()->clearFromTextureMap(m_textureIDs[i]);
    }

    m_callbacks.clear();

    return true;
}


void MainMenuState::s_menuToPlay(){
    TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}


void MainMenuState::s_exitFromMenu(){
    TheGame::Instance()->quit();
}


void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks){
    for(int i = 0; i < m_gameObjects.size(); i++){
	if(dynamic_cast<MenuButton*>(m_gameObjects[i])){
	    MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
	    pButton->setCallback(callbacks[pButton->getCallbackID()]);
	}
    }
}
