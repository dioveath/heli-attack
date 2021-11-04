// SDLGameObject.h
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef SDLGAMEOBJECT_H
#define SDLGAMEOBJECT_H 1


#include "GameObject.h"
#include "Vector2D.h"
#include "GameObjectFactory.h"


class SDLGameObject : public GameObject {

 public:
    SDLGameObject();

    virtual void load(const LoaderParams* pParams);
    virtual void update();
    virtual void render();
    virtual void clean();

    Vector2D& getPosition() { return m_position; }
    void setPositionX(int x) { m_position.setX(x); }
    void setPositionY(int y) { m_position.setY(y); }
    Vector2D& getVelocity() { return m_velocity; }
    
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }

    bool isActive() const { return m_isActive; }
    bool isRenderable() const { return m_isRenderable; }

    /* friend World; */

 protected:
    Vector2D m_position;
    Vector2D m_velocity;
    Vector2D m_acceleration;

    float m_friction;

    int m_width, m_height;
    std::string m_textureID;

    int m_currentRow;
    int m_currentFrame;

    bool m_isActive;
    bool m_isRenderable;

};



class SDLGameObjectCreator : public BaseCreator {
    
 public:
    /* const in function implies that this function will not modify the object 
       with which the function is called
     */

    virtual GameObject* createGameObject() const { 
	return new SDLGameObject();
    }

};
    





#endif // SDLGAMEOBJECT_H
//////////////////////////////////////////////////////////////////////
// $Log:$
//
