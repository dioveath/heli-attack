/* 

   main.cpp

   Author: Saroj Rai @ Charicha 
   Created On: Friday, 20 July 2018.

*/

// $Log:$ //
//

#include "Game.h"


const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;


int main(int argc, char* argv[]){

    Uint32 frameStart, frameTime;

    TheGame::Instance()->init("HOLY SHIT THIS IS GAME!",
			      SDL_WINDOWPOS_UNDEFINED,
			      SDL_WINDOWPOS_UNDEFINED,
			      800, 
			      600,
			      0);

    while(TheGame::Instance()->isRunning()){

	frameStart = SDL_GetTicks();

	TheGame::Instance()->handleEvents();
	TheGame::Instance()->update();
	TheGame::Instance()->render();

	frameTime = SDL_GetTicks() - frameStart;

	if(frameTime < DELAY_TIME){
	    SDL_Delay((int) DELAY_TIME - frameTime);
	}
    }

    TheGame::Instance()->clean();

    return 0;
}
