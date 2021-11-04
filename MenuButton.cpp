/* 

   MenuButton.cpp

   Author: Saroj Rai @ Charicha 
   Created On: Wednesday, 25 July 2018.

*/

#include "MenuButton.h"
#include "InputHandler.h"

// $Log:$ //
//


MenuButton::MenuButton()
{
}


void MenuButton::load(const LoaderParams* pParams){
    SDLGameObject::load(pParams);
    m_callbackID = pParams->m_callbackID;
    m_currentFrame = MOUSE_OUT;
}



void MenuButton::render(){
    SDLGameObject::render();
}



void MenuButton::update(){
    Vector2D* pMousePos = TheInputHandler::Instance()->getMousePosition();

    if(pMousePos->getX() < (m_position.getX() + m_width) &&
       pMousePos->getX() > m_position.getX() &&
       pMousePos->getY() < (m_position.getY() + m_height) &&
       pMousePos->getY() > m_position.getY()){

	if(TheInputHandler::Instance()->getMouseButtonState(LEFT) && m_bReleased){
	    m_currentFrame = CLICKED;

	    m_callback();
	    m_bReleased = false;
	} else if(!TheInputHandler::Instance()->getMouseButtonState(LEFT)){
	    m_bReleased = true;
	    m_currentFrame = MOUSE_OVER;
	}
	    
    } else {
	m_currentFrame = MOUSE_OUT;
    }
}


void MenuButton::clean(){
    SDLGameObject::clean();
}
