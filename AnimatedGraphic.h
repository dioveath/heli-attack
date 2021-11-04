// AnimatedGraphic.h
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef ANIMATEDGRAPHIC_H
#define ANIMATEDGRAPHIC_H 1


#include "SDLGameObject.h"

class AnimationManager;

class AnimatedGraphic : public SDLGameObject {


 public:
    AnimatedGraphic();

    virtual void load(const LoaderParams* pParams);
    virtual void update();
    virtual void render();
    virtual void clean();

    void setLoop(bool b) { m_isLoop = b; }
    bool isLoop() { return m_isLoop; }

    void setPosition(int x, int y);
    void setAnimSpeed(int speed) { m_animSpeed = speed; }

    friend AnimationManager;

 private:
    int m_numFrames;
    int m_animSpeed;
    bool m_isLoop;

    int m_animationStartTime;
    

};



#endif // ANIMATEDGRAPHIC_H
//////////////////////////////////////////////////////////////////////
// $Log:$
//
