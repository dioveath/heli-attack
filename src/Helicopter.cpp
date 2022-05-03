/* 

   Helicopter.cpp

   Author: Saroj Rai @ Charicha 
   Created On: Friday, 10 August 2018.

*/

#include "Helicopter.h"

#include "TextureManager.h"
#include "Game.h"
#include "AnimationManager.h"
#include "AudioManager.h"


#include <SDL2/SDL.h>

// $Log:$ //
//

Helicopter::Helicopter()
    :SDLGameObject(),
     m_pressingLeft(false),
     m_pressingRight(false),
     m_pressingUp(false),
     m_pressingDown(false),
     m_pressingSpace(false),
     m_TurningLeft(false),
     m_TurningRight(false)
{
}


void Helicopter::load(const LoaderParams* pParams){
    SDLGameObject::load(pParams);

    m_numFrames = pParams->m_numFrames;
    m_animSpeed = pParams->m_animSpeed;

    m_explosionID = TheAnimationManager::Instance()->loadSpriteSheet("largeexplosion",
								     60, 60, 10,
								     1000/15);
    m_ExplosionSoundID = TheAudioManager::Instance()->LoadSound("assets/boom.wav");
    m_AState = IDLE_RIGHT;
}


void Helicopter::update(){
    // m_velocity.setX(0);
    // m_velocity.setY(0);
    if(!m_isActive) return;

    handleInput();

    m_velocity += m_acceleration;

    if(m_velocity.getX() > MAX_VELOCITY) m_velocity.setX(MAX_VELOCITY);
    if(m_velocity.getX() < -MAX_VELOCITY) m_velocity.setX(-MAX_VELOCITY);
    if(m_velocity.getY() > MAX_VELOCITY) m_velocity.setY(MAX_VELOCITY);
    if(m_velocity.getY() < -MAX_VELOCITY) m_velocity.setY(-MAX_VELOCITY);

    m_velocity *= m_friction;
    m_position += m_velocity;


    m_currentFrame = int((SDL_GetTicks() / (1000/m_animSpeed)) % m_numFrames);
    m_currentAnimationTime = m_animStartTime - SDL_GetTicks();


    if(m_velocity.getX() > 0){
	m_TurningRight = true;
	m_TurningLeft = false;
    }
    if(m_velocity.getX() < 0){
	m_TurningRight = false;
	m_TurningLeft = true;
    }

}


void Helicopter::render(){
    if(!m_isRenderable) return;

    switch(m_AState){
    case IDLE_LEFT:
    	TheTextureManager::Instance()->drawFrame(m_textureID,
    						 (int) m_position.getX(),
    						 (int) m_position.getY(),
    						 m_width, m_height,
    						 m_currentRow, m_currentFrame,
    						 TheGame::Instance()->getRenderer(),
    						 SDL_FLIP_NONE);
	break;
    case IDLE_RIGHT:
    	TheTextureManager::Instance()->drawFrame(m_textureID,
    						 (int) m_position.getX(),
    						 (int) m_position.getY(),
    						 m_width, m_height,
    						 m_currentRow, m_currentFrame,
    						 TheGame::Instance()->getRenderer(),
    						 SDL_FLIP_HORIZONTAL);
    	break;
    case MOVING_LEFT:
    	TheTextureManager::Instance()->drawFrame(m_textureID,
    						 (int) m_position.getX(),
    						 (int) m_position.getY(),
    						 m_width, m_height,
    						 m_currentRow, m_currentFrame,
    						 TheGame::Instance()->getRenderer(),
    						 SDL_FLIP_NONE, -10);
    	break;
    case MOVING_RIGHT:
    	TheTextureManager::Instance()->drawFrame(m_textureID,
    						 (int) m_position.getX(),
    						 (int) m_position.getY(),
    						 m_width, m_height,
    						 m_currentRow, m_currentFrame,
    						 TheGame::Instance()->getRenderer(),
    						 SDL_FLIP_HORIZONTAL, 10);
    	break;
    default:
    	break;
    }

    // Vector2D* target = TheInputHandler::Instance()->getMousePosition();
    // SDL_Rect tRect;
    // tRect.x = target->getX() - 10;
    // tRect.y = target->getY() - 10;
    // tRect.w = 20;
    // tRect.h = 20;

    // SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(),
    // 			255, 255, 255, 255);
    // SDL_RenderFillRect(TheGame::Instance()->getRenderer(), &tRect);

    // TheTextureManager::Instance()->fillRect(m_position.getX(),
    // 					    m_position.getY(),
    // 					    m_width,
    // 					    m_height,
    // 					    TheGame::Instance()->getRenderer(),
    // 					    255, 0, 255, 200);
}




void Helicopter::destroy(){
    m_isActive = false;
    m_isRenderable = false;
    
    changeAnimationState(EXPLODING);

    TheAnimationManager::Instance()->animateAt(m_explosionID,
					       m_position.getX(),
					       m_position.getY(),
					       false);
    TheAudioManager::Instance()->PlaySound(m_ExplosionSoundID);
}


void Helicopter::changeAnimationState(AnimationState state){
    // while(!m_AStateMachine.empty()){
    // 	AnimationState aState = m_AStateMachine[i];
    
    	if(m_AState == state) return;
    	m_AState = state;
    	m_currentAnimationTime = 0;
    	m_animStartTime = SDL_GetTicks();
}


void Helicopter::clean(){
    TheAnimationManager::Instance()->release(m_explosionID);
    TheAudioManager::Instance()->ReleaseSound(m_ExplosionSoundID);
    // m_pressingLeft = false; m_pressingRight = false;
    // m_pressingUp = false; m_pressingDown = false;
    // m_pressingSpace = false;
    // bullet_fired = false;
    // lastFiredTime = 0;
    // m_currentAnimationTime = 0;
    // m_animStartTime = 0;
}
