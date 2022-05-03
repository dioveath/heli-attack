// Level.h
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef LEVEL_H
#define LEVEL_H 1


#include "TiledMap.h"
#include "Vector2D.h"
#include "SDLGameObject.h"



/* 'Level' this name should be more well thought */
class Level : public SDLGameObject {

 public:


    /* use pParams->textureID for our tiledmap file */
    virtual void load(const LoaderParams* pParams);
    virtual void update();
    virtual void render();
    virtual void clean();

 private:
    TiledMap* m_Map;


};


#endif // LEVEL_H
//////////////////////////////////////////////////////////////////////
// $Log:$
//
