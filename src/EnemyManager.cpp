/* 

   EnemyManager.cpp

   Author: Saroj Rai @ Charicha 
   Created On: Saturday, 11 August 2018.

*/

#include "EnemyManager.h"
#include "TextureManager.h"
#include "Game.h"
#include "World.h"
#include "AnimationManager.h"

#include <sstream>
#include <stdio.h>


// $Log:$ //
//


EnemyManager::EnemyManager(Player* player)
    :lastSpawnedTime(0),
     m_Player(player)
     
{
    TheTextureManager::Instance()->load("assets/largeexplosion.png",
					"largeexplosion",
					TheGame::Instance()->getRenderer());
}


EnemyManager::~EnemyManager(){
    for(int i = 0; i < m_enemies.size(); i++){
	m_enemies[i]->clean();
	delete m_enemies[i];
    }
    m_enemies.clear();

    TheTextureManager::Instance()->clearFromTextureMap("largeexplosion");
}


void EnemyManager::setPlayer(Player *player){
    if(player){
	m_Player = player;
    }
}

void EnemyManager::insertEnemy(Enemy* enemy){
    printf("Enemy(level:%d) at (%f, %f) spawned..!\n", enemy->m_numFrames,
	   enemy->m_position.getX(),
	   enemy->m_position.getY());

    enemy->lockPlayer(m_Player);
    m_enemies.push_back(enemy);
}



void EnemyManager::updateEnemies(){
    for(int i = 0; i < m_enemies.size(); i++){
	if(m_enemies[i]->m_isActive)
	    m_enemies[i]->update();
    }
}


void EnemyManager::renderEnemies(){
    for(int i = 0; i < m_enemies.size(); i++)
	if(m_enemies[i]->m_isRenderable)
	    m_enemies[i]->render();
}


bool EnemyManager::checkCollisionWith(SDLGameObject* obj){
    for(int i = 0; i < m_enemies.size(); i++){
	if(!m_enemies[i]->m_isActive) continue;

	if(World::checkCollision(dynamic_cast<SDLGameObject*>(m_enemies[i]),
				 obj)){
	    m_enemies[i]->destroy();
	    return true;
	}
    }
    return false;
}
