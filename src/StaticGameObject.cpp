/* 

   StaticGameObject.cpp

   Author: Saroj Rai @ Charicha 
   Created On: Thursday,  9 August 2018.

*/

#include <iostream>

#include "StaticGameObject.h"
#include "Game.h"

// $Log:$ //
//



StaticGameObject::StaticGameObject()
    : m_position(0, 0){ }



void StaticGameObject::load(const LoaderParams* pParams){
    // GameObject::load(pParams);
    m_position.setX(pParams->m_x);
    m_position.setY(pParams->m_y);

    m_width = pParams->m_width;
    m_height = pParams->m_height;

    m_textureID = pParams->m_textureID;
    m_numFrames = pParams->m_numFrames;
}


void StaticGameObject::update(){
    m_currentFrame = (int)((SDL_GetTicks() / (1000/30)) % m_numFrames);
}


void StaticGameObject::render(){
    if(m_textureID == "") {
	std::cout << "NO DRAWING..!\n";
	return;
    }
    TheTextureManager::Instance()->drawFrame(m_textureID,
					     (int) m_position.getX(),
					     (int) m_position.getY(),
					     m_width, m_height,
					     m_currentRow,
					     m_currentFrame,
					     TheGame::Instance()->getRenderer());
}


void StaticGameObject::clean(){
}
