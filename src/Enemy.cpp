/* 

   Enemy.cpp

   Author: Saroj Rai @ Charicha 
   Created On: Thursday, 26 July 2018.

*/

#include "Enemy.h"
#include "Bullet.h"
#include "AudioManager.h"

#include <SDL2/SDL.h>
#include <math.h>
#include <cstdlib>

// $Log:$ //
//


Enemy::Enemy()
    : m_Player(0)
{
    m_BulletSoundID = -1;
}


void Enemy::load(const LoaderParams* pParams){
    Helicopter::load(pParams);
    m_AState = IDLE_LEFT;
    m_fireRate = 1;

    m_lastFiredTime = rand() % 1000;
    MAX_VELOCITY = 2;
    BULLET_FORCE = 4;

    m_BulletSoundID = TheAudioManager::Instance()->LoadSound("assets/phaser.wav");
}


void Enemy::render() {
    Helicopter::render();
}


void Enemy::update() {
    Helicopter::update();
}


void Enemy::lockPlayer(Player* player) {
    m_Player = player;
}


void Enemy::handleInput(){
    if(!m_Player) {
	std::cout << "No player target..!\n";
	return;
    }

    Vector2D PlayerPosition = m_Player->getPosition();
    Vector2D offset = PlayerPosition - m_position;

    int dist = (int) offset.length();

    if(dist <= 600){
	m_pressingSpace = true;
	if(abs(offset.getX()) > abs(offset.getY())){
	    if(offset.getX() > 0){
		if(dist <= 200){
		    changeAnimationState(IDLE_RIGHT);
		} else {
		    m_pressingRight = true;
		    m_pressingLeft = false;
		}
	    }
	    else if(offset.getX() < 0){
		if(dist <= 200){
		    changeAnimationState(IDLE_LEFT);
		} else {
		    m_pressingLeft = true;
		    m_pressingRight = false;
		}
	    }
	} else {
	    if(offset.getY() > 0){
		m_pressingDown = true;
		m_pressingUp = false;
	    }
	    else if(offset.getY() < 0){
		m_pressingUp = true;
		m_pressingDown = false;
	    }
	    
	}
    } else {
	m_pressingSpace = false;
	m_pressingLeft = false;
	m_pressingRight = false;
	m_pressingUp = false;
	m_pressingDown = false;
    }


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
	    TheBulletManager::Instance()->addBullet(m_position.getX()+10, //offset magic num
						    m_position.getY() + m_height/2,
						    m_velocity.getX() - BULLET_FORCE,
						    m_velocity.getY(),
						    "Enemy",
						    1);
	} else if(m_AState == MOVING_RIGHT || m_AState == IDLE_RIGHT){
	    TheBulletManager::Instance()->addBullet(m_position.getX()+m_width-10, // offset
						    m_position.getY() + m_height/2,
						    m_velocity.getX() + BULLET_FORCE,
						    m_velocity.getY(),
						    "Enemy",
						    1);
	}

	TheAudioManager::Instance()->PlaySound(m_BulletSoundID);
	bullet_fired = true;
	m_lastFiredTime = SDL_GetTicks();
    }
    
    if(bullet_fired) {
	if((((SDL_GetTicks() - m_lastFiredTime) / 1000.0) >= m_fireRate)){
	    bullet_fired = false;
	}
    }    

}

   
void Enemy::clean(){
    Helicopter::clean();
    m_Player = 0;
    TheAudioManager::Instance()->ReleaseSound(m_BulletSoundID);
}
