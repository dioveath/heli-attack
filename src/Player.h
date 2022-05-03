// Player.h
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef PLAYER_H
#define PLAYER_H 1

#include "Helicopter.h"
#include "GameObjectFactory.h"

class Player : public Helicopter {

 public:
    Player();

    virtual void load(const LoaderParams* pParams);
    virtual void update();
    virtual void render();
    virtual void clean();

    virtual void destroy();

 private:
    virtual void handleInput();

    int m_BulletSoundID;


};


class PlayerCreator : public BaseCreator {
 public:
    virtual GameObject* createGameObject() const {
	return new Player();
    }

};


#endif // PLAYER_H
//////////////////////////////////////////////////////////////////////
// $Log:$
//
