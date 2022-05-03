/* 

   SDLGameObject.cpp

   Author: Saroj Rai @ Charicha 
   Created On: Tuesday, 24 July 2018.

*/

#include "Game.h"
#include "SDLGameObject.h"

// $Log:$ //
//


SDLGameObject::SDLGameObject() 
    :m_position(0, 0),
     m_velocity(0, 0),
     m_acceleration(0, 0),
     m_friction(0.97),
     m_isActive(true),
     m_isRenderable(true)
{ } 


void SDLGameObject::load(const LoaderParams* pParams){
    GameObject::load(pParams);
    m_width = pParams->m_width;
    m_height= pParams->m_height;
    m_position.setX(pParams->m_x);
    m_position.setY(pParams->m_y);
    // m_position = new Vector2D(pParams->m_x, pParams->m_y);
    // m_velocity = new Vector2D(0, 0);
    // m_acceleration = new Vector2D(0, 0);
    m_textureID = pParams->m_textureID;
    m_currentRow = 1;
    m_currentFrame = 0;
}



void SDLGameObject::update() {
    if(!m_isActive) return;
    m_velocity += m_acceleration;
    m_velocity *= m_friction;
    m_position += m_velocity;
    // std::cout << m_velocit
}


void SDLGameObject::render() {
    if(!m_isRenderable) return;
    TheTextureManager::Instance()->drawFrame(m_textureID,
					     (int) m_position.getX(),
					     (int) m_position.getY(),
					     m_width, m_height,
					     m_currentRow,
					     m_currentFrame,
					     TheGame::Instance()->getRenderer());
}


void SDLGameObject::clean() {
}
			      

