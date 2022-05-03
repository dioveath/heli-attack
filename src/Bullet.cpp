/* 

   Bullet.cpp

   Author: Saroj Rai @ Charicha 
   Created On: Thursday,  9 August 2018.

*/

#include <iostream>		// temp
#include "Bullet.h"
#include "TextureManager.h"	// temp
#include "Game.h"
#include "AnimationManager.h"
#include "World.h"

#include <sstream>

// $Log:$ //
//


Bullet::Bullet() { }


void Bullet::load(const LoaderParams* pParams){
    SDLGameObject::load(pParams);
    m_explosionID = TheAnimationManager::Instance()->loadSpriteSheet("smallexplosion",
								     20, 20,
								     2, 1000/15);
}


void Bullet::update(){
    SDLGameObject::update();
}


void Bullet::render(){
    SDLGameObject::render();
}


void Bullet::clean(){
    SDLGameObject::clean();
    TheAnimationManager::Instance()->release(m_explosionID);
}




BulletManager* BulletManager::s_pInstance = 0;


BulletManager::BulletManager(int size)
    :m_poolSize(size){

    for(int i = 0; i < 3; i++){
	std::stringstream iss;
	iss << "assets/bullet" << i+1 << ".png";
	std::stringstream iss2;
	iss2 << "bullet" << i+1;
	TheTextureManager::Instance()->load(iss.str(),
					    iss2.str(),
					    TheGame::Instance()->getRenderer());
    }

    TheTextureManager::Instance()->load("assets/smallexplosion.png",
					"smallexplosion",
					TheGame::Instance()->getRenderer());



}


void BulletManager::addBullet(int x, int y, int vx, int vy, std::string whose, int level){
    // here 11 is magic number, it's from the bullet sprite itself
    Bullet* b;


    if(m_freeBullets.size()){
	b = m_freeBullets.back();
	m_freeBullets.pop_back();
    } else {
	b = new Bullet();
    }


    std::stringstream iss;
    iss << "bullet" << level;
    b->load(new LoaderParams(x, y, 11 * level, 11 * level,
			     iss.str()));
    b->m_velocity.setX(vx);
    b->m_velocity.setY(vy);
    b->m_friction = 1;
    b->m_isActive = true;
    b->m_isRenderable = true;
    b->m_whose = whose;
    b->m_level = level;

    m_bullets.push_back(b);
}


void BulletManager::updateBullets(){
    for(int i = 0; i < m_bullets.size(); i++){

	if(!m_bullets[i]->m_isActive) continue;

	m_bullets[i]->update();


	Vector2D cameraPos = TheCamera::Instance()->getPosition();
	if(m_bullets[i]->getPosition().getX() < cameraPos.getX() ||
	   m_bullets[i]->getPosition().getY() < cameraPos.getY() ||
	   m_bullets[i]->getPosition().getX() + m_bullets[i]->getWidth() > cameraPos.getX() + TheCamera::Instance()->getCameraWidth() ||
	   m_bullets[i]->getPosition().getY() + m_bullets[i]->getHeight() > cameraPos.getY() + TheCamera::Instance()->getCameraHeight()){

	    m_bullets[i]->m_isActive = false;
	    m_bullets[i]->m_isRenderable = false;

	}
    }


    for(int i = 0; i < m_bullets.size(); i++){
	if(!m_bullets[i]->m_isActive) continue;

	for(int j = i + 1; j < m_bullets.size(); j++){
	    // if(m_bullets[i]->m_whose == m_bullets[i]->m_whose) continue;

	    if(!m_bullets[j]->m_isActive) continue;

	    SDLGameObject* bullet1 = dynamic_cast<SDLGameObject*>(m_bullets[i]);
	    SDLGameObject* bullet2 = dynamic_cast<SDLGameObject*>(m_bullets[j]);
	    
	    if(World::checkCollision(bullet1, bullet2, 0)){

		m_bullets[i]->m_isActive = false;
		m_bullets[i]->m_isRenderable = false;
		m_bullets[j]->m_isActive = false;
		m_bullets[j]->m_isRenderable = false;
		TheAnimationManager::Instance()->animateAt(m_bullets[i]->m_explosionID,
							   m_bullets[i]->getPosition().getX(),
							   m_bullets[i]->getPosition().getY(),
							   false);
	    }	    
	}
    }

}


void BulletManager::renderBullets(){
    for(int i = 0; i < m_bullets.size(); i++){
	if(!m_bullets[i]->m_isRenderable) continue;
	m_bullets[i]->render();
    }
}


void BulletManager::freeBullets(){
    for(int i = 0; i < m_bullets.size(); i++){
	if(!m_bullets[i]->m_isActive){
	    freeBullet(m_bullets[i]);
	    m_bullets.erase(m_bullets.begin() + i);
	}
    }
}


void BulletManager::freeBullet(Bullet* b){
    if(m_freeBullets.size() >= m_poolSize) {
	b->clean();
	delete b;
	return;
    }
    
    m_freeBullets.push_back(b);
}


void BulletManager::clean(){
    for(int i = 0; i < m_bullets.size(); i++){
	m_bullets[i]->m_isActive = false;
	m_bullets[i]->m_isRenderable = false;
    }
    freeBullets();
}


bool BulletManager::checkCollisionWith(SDLGameObject* obj, std::string who){
    for(int i = 0; i < m_bullets.size(); i++){

	if(!m_bullets[i]->m_whose.compare(who) || !m_bullets[i]->m_isActive) {
	    continue;
	}
	
	if(World::checkCollision(dynamic_cast<SDLGameObject*>(m_bullets[i]),
				 obj)){
	    m_bullets[i]->m_isActive = false;
	    m_bullets[i]->m_isRenderable = false;
	    TheAnimationManager::Instance()->animateAt(m_bullets[i]->m_explosionID,
						       m_bullets[i]->getPosition().getX(),
						       m_bullets[i]->getPosition().getY(),
						       false);
	    return true;
	}
    }

    return false;
}

