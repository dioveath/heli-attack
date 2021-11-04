// EnemyManager.h
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H 1


#include "Enemy.h"
#include <vector>



class EnemyManager  {

 public:
    EnemyManager(Player* player); 	      
    ~EnemyManager();

    void insertEnemy(Enemy* enemy);
    void setPlayer(Player* player);

    void updateEnemies();
    void renderEnemies();

    Enemy* getEnemy(int index) { return m_enemies[index]; }
    int getSize() { return m_enemies.size(); }

    bool checkCollisionWith(SDLGameObject* obj);


 private:
    std::vector<Enemy*> m_enemies;
    std::vector<Enemy*> m_reusableEnemies;

    Player* m_Player;
    int lastSpawnedTime;


};



#endif // ENEMYMANAGER_H
//////////////////////////////////////////////////////////////////////
// $Log:$
//
