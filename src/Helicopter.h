// Helicopter.h
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef HELICOPTER_H
#define HELICOPTER_H 1


#include "SDLGameObject.h"


class Helicopter : public SDLGameObject {

 public:

    Helicopter();

    virtual void load(const LoaderParams* pParams);
    virtual void update();
    virtual void render();
    virtual void clean();
    virtual void handleInput()=0;

    virtual void destroy();

    bool isTurningLeft() { return m_TurningLeft; }
    bool isTurningRight() { return m_TurningRight; }
    

protected:
    enum AnimationState {
	IDLE_LEFT, IDLE_RIGHT, MOVING_LEFT, MOVING_RIGHT,
	SHOOTING, EXPLODING
    };
    
    void changeAnimationState(AnimationState state);

    bool m_pressingLeft, m_pressingRight;
    bool m_pressingUp, m_pressingDown;
    bool m_pressingSpace;

    bool bullet_fired;
    int m_lastFiredTime;
    float m_fireRate;
 
    AnimationState m_AState;
    int m_currentAnimationTime;
    int m_animStartTime;

    int m_numFrames;
    int m_animSpeed;

    int MAX_VELOCITY = 3;
    int ENGINE_POWER = 2;
    int BULLET_FORCE = 7;

    int m_explosionID;
    int m_ExplosionSoundID;

    bool m_TurningRight;
    bool m_TurningLeft;

};



#endif // HELICOPTER_H
//////////////////////////////////////////////////////////////////////
// $Log:$
//
