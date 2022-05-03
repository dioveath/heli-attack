// Game.h
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef GAME_H
#define GAME_H 1

#include <iostream>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "SDLGameObject.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "GameStateMachine.h"


class Game {

 public:
    static Game* Instance(){
	if(!m_pInstance)
	    m_pInstance = new Game();
	return m_pInstance;
    }

    bool init(const char* title, int x, int y, int width, int height, int flags);
    void handleEvents();
    void update();
    void render();
    void clean();
    void quit();

    bool isRunning() { return m_bRunning; }
    SDL_Renderer* getRenderer() { return m_pRenderer; }
    GameStateMachine* getStateMachine() { return  m_pGameStateMachine; }


    int getGameWidth() { return m_gameWidth; }
    int getGameHeight() { return m_gameHeight; }

 private:

    Game() { }
    ~Game() { }

    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    bool m_bRunning = false;

    static Game* m_pInstance;

    GameStateMachine* m_pGameStateMachine;

    int m_gameWidth;
    int m_gameHeight;

};


typedef Game TheGame;


#endif // GAME_H
//////////////////////////////////////////////////////////////////////
// $Log:$
//
