/* 

   Camera.cpp

   Author: Saroj Rai @ Charicha 
   Created On: Tuesday,  7 August 2018.

*/

#include "Camera.h"
#include "Game.h"

// $Log:$ //
//


Camera* Camera::s_pInstance = 0;

Camera::Camera()
    :m_Target(0, 0) { } 


void Camera::load(const LoaderParams* pParams){
    SDLGameObject::load(pParams);
}


void Camera::update(){
    // center adjusted from target 
    // Vector2D adjustedTarget =

    // if(
    // m_acceleration = (m_Target - m_position);
    m_position = m_Target;
    SDLGameObject::update();
    
}


void Camera::setTarget(Vector2D& target){
    m_Target.setX(target.getX() - m_Width/2);
    m_Target.setY(target.getY() - m_Height/2);
    // std::cout << m_Target << "\n";
}


void Camera::render(){
    // no render
}


void Camera::clean(){
}


void Camera::reset(){
    Vector2D origin(m_Width/2, m_Height/2);
    setTarget(origin);
}
