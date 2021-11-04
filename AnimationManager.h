// AnimationManager.h
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H 1


#include <map>
#include <vector>

#include "AnimatedGraphic.h"


class AnimationManager {

 public:

    /* returns animtedgraphic index for invoking animateAt() */
    int loadSpriteSheet(std::string texture_id,
			 int frameWidth, int frameHeight,
			 int m_numFrames,
			 int animSpeed = 1000); /*in animSpeed in milisc */

    void animateAt(int id, int x, int y, bool loop, int animSpeed = -1);
    void release(int id);

    void update();
    void render();

    static AnimationManager* Instance() {
	if(!s_pInstance)
	    s_pInstance = new AnimationManager();
	return s_pInstance;
    }
    

 private:
    AnimationManager();
    static AnimationManager* s_pInstance;

    std::map<int, AnimatedGraphic*> m_Animations;
    std::vector<AnimatedGraphic*> m_reusableAnimations;

    int m_poolSize;
    int m_totalCount;		

};


typedef AnimationManager TheAnimationManager;


#endif // ANIMATIONMANAGER_H
//////////////////////////////////////////////////////////////////////
// $Log:$
//
