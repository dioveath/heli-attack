/* 

   Game.cpp

   Author: Saroj Rai @ Charicha 
   Created On: Friday, 20 July 2018.

*/


#include "Game.h"

#include "PlayState.h"
#include "MainMenuState.h"
#include "GameObjectFactory.h"
#include "MenuButton.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "World.h"
#include "AudioManager.h"

// $Log:$ //
//


Game* Game::m_pInstance = 0;


bool Game::init(const char* title, int x, int y, int width, int height, int flags){
    if(SDL_Init(SDL_INIT_EVERYTHING)){
	std::cout << "SDL initialization failed..!\n";
	return false;
    }

    m_pWindow = SDL_CreateWindow(title, x, y, width, height, flags);
    if(!m_pWindow) {
	std::cout << "Window creation failed..!\n";
	return false;
    }
    m_gameWidth = width;
    m_gameHeight = height;

    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
    if(!m_pRenderer) {
	std::cout << "Renderer creation failed..!\n";
	return false;
    }
    SDL_SetRenderDrawColor(m_pRenderer, 100, 27, 200, 255);

    m_bRunning = true;
    std::cout << "Game initialized..!" << std::endl;

    TheInputHandler::Instance()->initializeJoysticks();
    TheAudioManager::Instance()->InitAudio();


    TheGameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
    TheGameObjectFactory::Instance()->registerType("World", new WorldCreator());
    TheGameObjectFactory::Instance()->registerType("SDLGameObject",
						   new SDLGameObjectCreator());

    m_pGameStateMachine = new GameStateMachine();
    m_pGameStateMachine->changeState(new MainMenuState());

    return true;
}


void Game::handleEvents(){
    TheInputHandler::Instance()->update();

    if(TheInputHandler::Instance()->joystickInitialized()){
	if(TheInputHandler::Instance()->getButtonState(0, 0)){
	    m_pGameStateMachine->changeState(new PlayState());
	}
    }

}


void Game::update(){
    TheCamera::Instance()->update();
    m_pGameStateMachine->update();
}


void Game::render(){
    SDL_SetRenderDrawColor(m_pRenderer, 100, 27, 200, 255);
    SDL_RenderClear(m_pRenderer);

    m_pGameStateMachine->render();
	
    SDL_RenderPresent(m_pRenderer);
}


void Game::clean(){
    std::cout << "cleaning game..!\n";
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}


void Game::quit(){
    m_bRunning = false;
}
