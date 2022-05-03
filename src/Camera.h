// Camera.h
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef CAMERA_H
#define CAMERA_H 1


#include "SDLGameObject.h"

class Camera : public SDLGameObject {

 public:
    Camera();

    static Camera* Instance() {
    	if(!s_pInstance) s_pInstance = new Camera();
    	return s_pInstance;
    }

    virtual void load(const LoaderParams* pParams);
    virtual void update();
    virtual void render();
    virtual void clean();
    
    void setTarget(int x, int y) { m_Target.setX(x); m_Target.setY(y); }
    void setTarget(Vector2D& target);
    Vector2D& getTarget() { return m_Target; }
    Vector2D& getPosition() { return m_position; }

    void reset();

    void setCameraWidth(int width) { m_Width = width; }
    void setCameraHeight(int height) { m_Height = height; }
    int getCameraWidth() { return m_Width; }
    int getCameraHeight() { return m_Height; }

 private:
    Vector2D m_Target;
    int m_Width, m_Height;

    const int MAX_VELOCITY = 8;

    static Camera* s_pInstance;
    

};


typedef Camera TheCamera;


#endif // CAMERA_H
//////////////////////////////////////////////////////////////////////
// $Log:$
//
