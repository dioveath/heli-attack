// BulletManager.h
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H 1


#include "Bullet.h"


class BulletManager {

 public:
    BulletManager(int size);
    ~BulletManager();
    
    Bullet* createBullet(int x, int y, int vx, int vy, std::string whose, int level);
    void freeBullet(Bullet* b);

 private:
    std::vector<Bullet*> m_freeBullets;
    int m_poolSize = 0;

};



#endif // BULLETMANAGER_H
//////////////////////////////////////////////////////////////////////
// $Log:$
//
