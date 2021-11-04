/* 

   AnimatedGraphic.cpp

   Author: Saroj Rai @ Charicha 
   Created On: Thursday, 26 July 2018.

*/

#include "AnimatedGraphic.h"

#include <SDL2/SDL.h>

// $Log:$ //
//


AnimatedGraphic::AnimatedGraphic() { }


void AnimatedGraphic::load(const LoaderParams* pParams){
    SDLGameObject::load(pParams);
    m_numFrames = pParams->m_numFrames;
    m_animSpeed = pParams->m_animSpeed;
    m_animationStartTime = -1;
}


void AnimatedGraphic::update(){
    if(m_animationStartTime == -1)
	m_animationStartTime = SDL_GetTicks();

    // int timePerFrame = 1000 / m_animSpeed;

    m_currentFrame = int(((SDL_GetTicks() - m_animationStartTime)/ m_animSpeed) % m_numFrames);

    if(!m_isLoop){
	if((SDL_GetTicks() - m_animationStartTime) >= m_animSpeed * m_numFrames){
	    m_isActive = false;
	    m_isRenderable = false;
	    m_animationStartTime = -1;
	}
    }
}


void AnimatedGraphic::render(){
    SDLGameObject::render();
}


void AnimatedGraphic::clean(){
    SDLGameObject::clean();
} 


void AnimatedGraphic::setPosition(int x, int y){
    m_position.setX(x);
    m_position.setY(y);
}
