// Bullet.h
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef BULLET_H
#define BULLET_H 1

#include <vector>
#include "SDLGameObject.h"


class BulletManager;


class Bullet : public SDLGameObject {

 public:
    Bullet();

    virtual void load(const LoaderParams* pParams);
    virtual void update();
    virtual void render();
    virtual void clean();

    friend BulletManager;

 private:
    int m_level;		/* power level */
    std::string m_whose;		/* whose bullet is this? */

    int m_explosionID;

};


class BulletManager {

 public:
    static BulletManager* Instance(){
	if(!s_pInstance)
	    s_pInstance = new BulletManager(100);
	return s_pInstance;
    }

    void addBullet(int x, int y, int vx, int vy, std::string whose, int level = 1);
    void updateBullets();
    void renderBullets();
    void freeBullets();
    void clean();

    void freeBullet(Bullet* b);

    Bullet* getBullet(int index) { return m_bullets[index]; }
    int getSize() { return m_bullets.size(); }

    bool checkCollisionWith(SDLGameObject* obj, std::string who="static");


 private:
    BulletManager(int maxsize);
    
    static BulletManager* s_pInstance;

    int m_poolSize;

    std::vector<Bullet*> m_bullets;
    std::vector<Bullet*> m_freeBullets;

};


typedef BulletManager TheBulletManager;


#endif // BULLET_H
//////////////////////////////////////////////////////////////////////
// $Log:$
//
