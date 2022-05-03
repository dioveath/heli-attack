// Enemy.h
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef ENEMY_H
#define ENEMY_H 1


#include "Helicopter.h"
#include "GameObjectFactory.h"
#include "Player.h"

class EnemyManager;


class Enemy : public Helicopter {

 public:
    Enemy();

    virtual void load(const LoaderParams* pParams);
    virtual void update();
    virtual void render();
    virtual void clean();

    void lockPlayer(Player* player);

    virtual void handleInput();

    friend EnemyManager;

 private:
    Player* m_Player;
    int m_BulletSoundID;

};


class EnemyCreator : public BaseCreator {

 public:
    GameObject* createGameObject() const {
	return new Enemy();
    }

};


#endif // ENEMY_H
//////////////////////////////////////////////////////////////////////
// $Log:$
//
