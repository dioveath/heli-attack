/* 

   AnimationManager.cpp

   Author: Saroj Rai @ Charicha 
   Created On: Thursday,  9 August 2018.

*/

#include <iostream>

#include "AnimationManager.h"
#include "TextureManager.h"
#include "Game.h"

// $Log:$ //
//


AnimationManager* AnimationManager::s_pInstance = 0;


AnimationManager::AnimationManager()
    :m_poolSize(100),
     m_totalCount(0)
{
}



int AnimationManager::loadSpriteSheet(std::string texture_id,
				       int frameWidth, int frameHeight,
				       int numFrames,
				       int animSpeed)
{
    AnimatedGraphic* anim;

    if(m_reusableAnimations.size() > 0) {
	anim = m_reusableAnimations.back();
	m_reusableAnimations.pop_back();
    } else {
	anim = new AnimatedGraphic();
    }

    anim->load(new LoaderParams(0, 0, frameWidth, frameHeight, texture_id,
				numFrames, animSpeed));

    anim->m_isActive = false;
    anim->m_isRenderable = false;

    m_Animations[++m_totalCount] = anim;
    return m_totalCount;
}


void AnimationManager::animateAt(int id, int x, int y, bool loop, int animSpeed){
    m_Animations[id]->setPosition(x, y);
    m_Animations[id]->m_isActive = true;
    m_Animations[id]->m_isRenderable = true;
    m_Animations[id]->setLoop(loop);
    if(animSpeed != -1)		// default
	m_Animations[id]->setAnimSpeed(animSpeed);
}


void AnimationManager::release(int id){
    if(m_Animations.find(id) == m_Animations.end()){
	std::cout << "Animation with id: " << id << " not found!" << std::endl;
	return;
    }

    m_Animations[id]->m_isActive = false;
    m_Animations[id]->m_isRenderable = false;

    if(m_reusableAnimations.size() >= m_poolSize){
	std::cout << "Animation Manager deleting m_Animations[id]\n" << std::endl;
	m_Animations[id]->clean();
	delete m_Animations[id];
	m_Animations.erase(id);
    }else {
	m_reusableAnimations.push_back(m_Animations[id]);
	m_Animations.erase(id);
    }

}


void AnimationManager::update(){
    for(std::map<int, AnimatedGraphic*>::iterator it = m_Animations.begin();
	it != m_Animations.end(); ++it){	

	if(it->second->m_isActive)
	    it->second->update();

    }
}


void AnimationManager::render(){
    for(std::map<int, AnimatedGraphic*>::iterator it = m_Animations.begin();
	it != m_Animations.end(); ++it){

	if(it->second->m_isRenderable)
	    it->second->render();

    }
}
