/* 

   PlayState.cpp

   Author: Saroj Rai @ Charicha 
   Created On: Friday, 20 July 2018.

*/

#include "PlayState.h"
#include "PauseState.h"
#include "TextureManager.h"
#include "Game.h"
#include "World.h"
#include "AudioManager.h"

#include "StateParser.h"

#include <iostream>

// $Log:$ //
//


const std::string PlayState::s_playID = "PLAY";


void PlayState::update(){
    // std::cout << "This is playstate update..!\n";

    // if(dynamic_cast<SDLGameObject*>(m_gameObjects[1])){
	// TheCamera::Instance()->setTarget(dynamic_cast<SDLGameObject*>(m_gameObjects[1])->getPosition());
    // }

    for(int i = 0; i < m_gameObjects.size(); i++){
	m_gameObjects[i]->update();
    }

    if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)){
	TheGame::Instance()->getStateMachine()->pushState(new PauseState());
    }


}

void PlayState::render(){
    for(int i = 0; i < m_gameObjects.size(); i++){
	m_gameObjects[i]->render();
    }
}


bool PlayState::onEnter(){
    // if(!TheTextureManager::Instance()->load("assets/helicopter.png",
    // 					    "helicopter",
    // 					    TheGame::Instance()->getRenderer()))
    // 	{ return false; }
    // if(!TheTextureManager::Instance()->load("assets/helicopter2.png",
    // 					    "helicopter2",
    // 					    TheGame::Instance()->getRenderer()))
    // 	{ return false; }

    // GameObject* player = new Player();
    // player->load(new LoaderParams(300, 100, 128, 55, "helicopter"));

    // GameObject* enemy = new Enemy();
    // enemy->load(new LoaderParams(100, 100, 128, 55, "helicopter2"));

    // GameObject* level = new Level();
    // level->load(new LoaderParams(0, 0, 0, 0, "level1.tmx"));

    // m_gameObjects.push_back(level);
    // m_gameObjects.push_back(player);
    // m_gameObjects.push_back(enemy);

    int musicId = TheAudioManager::Instance()->LoadMusic("assets/DST_ElectroRock.ogg");
    TheAudioManager::Instance()->PlayMusic(musicId);


    TheStateParser::Instance()->parseState("test.xml", s_playID,
					   &m_gameObjects,
					   &m_textureIDs);

    // GameObject* world = new World();
    // world->load(new LoaderParams(0, 0, 0, 0, "level 2.tmx"));

    // m_gameObjects.push_back(world);

    std::cout << "Entering play state..!\n";
    return true;
}


bool PlayState::onExit(){
    std::cout << "Exiting play state..!\n";

    for(int i = 0; i < m_gameObjects.size(); i++){
	m_gameObjects[i]->clean();
	delete m_gameObjects[i];
    }

    m_gameObjects.clear();

    for(int i = 0; i < m_textureIDs.size(); i++){
	TheTextureManager::Instance()->clearFromTextureMap(m_textureIDs[i]);
    }

    std::cout << "PlayState exited..!\n";
    return true;
}


// bool PlayState::checkCollision(SDLGameObject* p1, SDLGameObject* p2){
//     // int leftA, leftB;
//     // int rightA, rightB;
//     // int topA, topB;
//     // int bottomA, bottomB;

//     return ((p1->getPosition().getX() < (p2->getPosition().getX() + p2->getWidth()) &&
// 	     (p1->getPosition().getX() + p1->getWidth()) > p2->getPosition().getX())
// 	 && (p1->getPosition().getY() < (p2->getPosition().getY() + p2->getHeight()) &&
// 	     (p1->getPosition().getY() + p1->getHeight()) > p2->getPosition().getY()));
// }
