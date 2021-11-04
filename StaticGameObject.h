// StaticGameObject.h
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef STATICGAMEOBJECT_H
#define STATICGAMEOBJECT_H 1


#include "GameObject.h"
#include "Vector2D.h"



class StaticGameObject : public GameObject {

 public:
    StaticGameObject();

    virtual void load(const LoaderParams* pParams);
    virtual void update();
    virtual void render();
    virtual void clean();


 protected:
    Vector2D m_position;

    int m_width, m_height;
    std::string m_textureID;

    int m_currentRow;		/* y index */
    int m_currentFrame; 	/* x index */
    int m_numFrames;

};


#endif // STATICGAMEOBJECT_H
//////////////////////////////////////////////////////////////////////
// $Log:$
//
