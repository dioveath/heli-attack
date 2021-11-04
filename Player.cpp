/* 

   Player.cpp

   Author: Saroj Rai @ Charicha 
   Created On: Thursday, 26 July 2018.

*/

#include "Player.h"
#include "InputHandler.h"
#include "Bullet.h"
#include "AnimationManager.h"
#include "AudioManager.h"


#include <SDL2/SDL.h>

// $Log:$ //
//

Player::Player()
    :Helicopter()
{
    m_BulletSoundID = -1;
    TheAudioManager::Instance()->LoadSound("assets/phaser.wav");
}



void Player::load(const LoaderParams* pParams){
    Helicopter::load(pParams);
    m_fireRate = 0.1;
    MAX_VELOCITY = 4;
    ENGINE_POWER = 6;
    m_friction = 0.9;
    m_BulletSoundID = TheAudioManager::Instance()->LoadSound("assets/phaser.wav");
}


void Player::update(){
    Helicopter::update();
}


void Player::render(){
    Helicopter::render();
}


void Player::handleInput(){
    // Vector2D* mouse_pos = TheInputHandler::Instance()->getMousePosition();
    // Vector2D offset_vec(m_width/2, m_height/2);
    // Vector2D target = (*mouse_pos) - offset_vec;

    // m_velocity = target - m_position;
    // m_velocity /= 50;

    // if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LCTRL)){
	// destroy();
    // }

    m_pressingLeft = TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT);
    m_pressingRight = TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT);
    m_pressingUp = TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP);
    m_pressingDown = TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN);
    m_pressingSpace = TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE);

    if(m_pressingLeft && !m_pressingRight){
    	m_acceleration.setX(-ENGINE_POWER);
    	changeAnimationState(MOVING_LEFT);
    }
    if(m_pressingRight && !m_pressingLeft){
    	m_acceleration.setX(ENGINE_POWER);
    	changeAnimationState(MOVING_RIGHT);
    }
    if(m_pressingUp && !m_pressingDown){
    	m_acceleration.setY(-ENGINE_POWER);
    }
    if(m_pressingDown && !m_pressingUp){
    	m_acceleration.setY(ENGINE_POWER);
    }

    if(!m_pressingLeft && !m_pressingRight)
	m_acceleration.setX(0);
    if(!m_pressingUp && !m_pressingDown)
	m_acceleration.setY(0);

    if(!m_pressingLeft && !m_pressingRight && !m_pressingUp && !m_pressingDown){
    	m_acceleration.setX(0);
    	m_acceleration.setY(0);
    	if(m_AState == MOVING_RIGHT)
    	    changeAnimationState(IDLE_RIGHT);
	if(m_AState == MOVING_LEFT)
	    changeAnimationState(IDLE_LEFT);
    }

    if(m_pressingSpace && !bullet_fired){
	if(m_AState == MOVING_LEFT || m_AState == IDLE_LEFT){
	    TheBulletManager::Instance()->addBullet(m_position.getX()+10,//offset magic num
						    m_position.getY() + m_height/2,
						    m_velocity.getX() - BULLET_FORCE,
						    m_velocity.getY(),
						    "Player",
						    1);
	} else if(m_AState == MOVING_RIGHT || m_AState == IDLE_RIGHT){
	    TheBulletManager::Instance()->addBullet(m_position.getX()+m_width-10, //offset
						    m_position.getY() + m_height/2,
						    m_velocity.getX() + BULLET_FORCE,
						    m_velocity.getY(),
						    "Player",
						    1);
	}
	TheAudioManager::Instance()->PlaySound(m_BulletSoundID);
	bullet_fired = true;
	m_lastFiredTime = SDL_GetTicks();
    } else if(bullet_fired) {
	if((((SDL_GetTicks() - m_lastFiredTime) / 1000.0) >= m_fireRate) && !m_pressingSpace){
	    bullet_fired = false;
	}
    }

}


void Player::clean(){
    Helicopter::clean();
    TheAudioManager::Instance()->ReleaseSound(m_BulletSoundID);
}


void Player::destroy(){
    Helicopter::destroy();
    // std::cout << "Player::destroy()\n";
    // changeAnimationState(EXPLODING);
    // TheAnimationManager::Instance()->animateAt(m_explosionID,
    // 					       m_position.getX() + m_width/2,
    // 					       m_position.getY() + m_height/2,
    // 					       false);
}
