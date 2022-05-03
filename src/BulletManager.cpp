/* 

   BulletManager.cpp

   Author: Saroj Rai @ Charicha 
   Created On: Saturday, 11 August 2018.

*/

#include "BulletManager.h"

// $Log:$ //
//



BulletManager::BulletManager(int size)
    :m_poolSize(size) {
    // BulletManager will load the spritesheet for bullets
    for(int i = 0; i < 3; i++){
	std::stringstream iss;
	iss << "assets/bullet" << i+1 << ".png";
	std::stringstream iss2;
	iss2 << "bullet" << i+1;
	TheTextureManager::Instance()->load(iss.str(),
					    iss2.str(),
					    TheGame::Instance()->getRenderer());
    }

    TheAnimationManager::Instance()->loadSpriteSheet("smallexplosion",
						     "assets/smallexplosion.png",
						     20, 20,
						     2, 1000);
}


~BulletManager::BulletManager(){
    for(int i = 0; i < m_freeBullets.size(); i++){
	delete m_freeBullets.back();
	m_freeBullets.pop_back();
    }
}


Bullet* BulletManager::createBullet(int x, int y, int vx, int vy,
				    std::string whose, int level)
{
    Bullet* b;
    if(m_freeBullets.size()){
	b = m_freeBullets.back();
	m_freeBullets.pop_back();
    } else {
	b = new Bullet();
    }

    // 11: frame width ;magic number
    std::stringstream ss;
    ss << "bullet" << level;
    b->load(new LoaderParams(x, y, 11 * level, 11 * level, ss.str()));
    b->m_velocity.setX(vx);
    b->m_velocity.setY(vy);
    b->m_friction = 1;
    b->m_isActive = true;
    b->m_isRenderable = true;
    b->m_whose = whose;

    return b;
}


void BulletManager::freeBullet(Bullet* b){
    if(m_poolSize >= m_freeBullets.size())
	return;
    m_freeBullets.push_back(b);
}


void BulletManager::clean(){
}
