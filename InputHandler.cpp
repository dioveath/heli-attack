/* 

   InputHandler.cpp

   Author: Saroj Rai @ Charicha 
   Created On: Tuesday, 24 July 2018.

*/

#include "InputHandler.h"
#include "Game.h"


// $Log:$ //
//


InputHandler* InputHandler::s_pInstance = 0;



void InputHandler::initializeJoysticks() {
    if(SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
	SDL_InitSubSystem(SDL_INIT_JOYSTICK);


    if(SDL_NumJoysticks() > 0){
	for(int i = 0; i < SDL_NumJoysticks(); i++){
	    SDL_Joystick* joy = SDL_JoystickOpen(i);

	    if(joy){
		m_joysticks.push_back(joy);
		m_joystickValues.push_back(std::make_pair(new Vector2D(0, 0),
							  new Vector2D(0, 0)));

		std::vector<bool> tempButtons;
		for(int j = 0; j < SDL_JoystickNumButtons(joy); j++)
		    tempButtons.push_back(false);
		m_buttonStates.push_back(tempButtons);
	    } else {
		std::cout << "Couldn't open Joystick, Error " << SDL_GetError() << std::endl;
	    }
	}

	if(SDL_JoystickEventState(SDL_ENABLE) == 1){
	    // std::cout << "Enabled...!\n";
	    m_bJoysticksInitialized = true;
	}

	std::cout << "Initialized " << m_joysticks.size() << " joystick(s) ..!\n";

    } else {
	m_bJoysticksInitialized = false;
    }
	
}


void InputHandler::update() {
    if(m_DelayStartedTime + m_DelayTime <= SDL_GetTicks())
	m_isActive = true;
    // else {
	// return;
    // }


    SDL_Event event;
    while(SDL_PollEvent(&event)){

	m_keystates = SDL_GetKeyboardState(0);

	switch(event.type){
	case SDL_QUIT:
	    TheGame::Instance()->quit();
	    break;
	case SDL_JOYAXISMOTION:
	    onJoystickAxisMove(event);
	    break;
	case SDL_JOYBUTTONUP:
	    onJoystickButtonUp(event);
	    break;
	case SDL_JOYBUTTONDOWN:
	    onJoystickButtonDown(event);
	    break;
	case SDL_MOUSEMOTION:
	    onMouseMove(event);
	    break;
	case SDL_MOUSEBUTTONDOWN:
	    onMouseButtonDown(event);
	    break;
	case SDL_MOUSEBUTTONUP:
	    onMouseButtonUp(event);
	    break;
	default:
	    break;
	}

    }

}



void InputHandler::onJoystickAxisMove(SDL_Event& event){
    int whichOne = event.jaxis.which;


    // left stick move left or right
    if(event.jaxis.axis == 0){
	if(event.jaxis.value > m_joystickDeadZone)
	    m_joystickValues[whichOne].first->setX(1);
	else if(event.jaxis.value < -m_joystickDeadZone)
	    m_joystickValues[whichOne].first->setX(-1);
	else
	    m_joystickValues[whichOne].first->setX(0);
    }

    // left stick move up or down
    if(event.jaxis.axis == 1){
	if(event.jaxis.value > m_joystickDeadZone)
	    m_joystickValues[whichOne].first->setY(1);
	else if(event.jaxis.value < -m_joystickDeadZone)
	    m_joystickValues[whichOne].first->setY(-1);
	else
	    m_joystickValues[whichOne].first->setY(0);
    }

    // right stick move left or right
    if(event.jaxis.axis == 3){
	if(event.jaxis.value > m_joystickDeadZone)
	    m_joystickValues[whichOne].second->setX(1);
	else if(event.jaxis.value < -m_joystickDeadZone)
	    m_joystickValues[whichOne].second->setX(-1);
	else
	    m_joystickValues[whichOne].second->setX(0);
    }

    // right stick move up or down
    if(event.jaxis.axis == 4){
	if(event.jaxis.value > m_joystickDeadZone)
	    m_joystickValues[whichOne].second->setY(1);
	else if(event.jaxis.value < -m_joystickDeadZone)
	    m_joystickValues[whichOne].second->setY(-1);
	else
	    m_joystickValues[whichOne].second->setY(0);
    }
}



void InputHandler::onJoystickButtonDown(SDL_Event& event){
    int whichOne = event.jaxis.which;
    m_buttonStates[whichOne][event.jbutton.button] = true;
    // std::cout << "Button Down: " << (int)event.jbutton.button << " \n";
}


void InputHandler::onJoystickButtonUp(SDL_Event& event){
    int whichOne = event.jaxis.which;
    m_buttonStates[whichOne][event.jbutton.button] = false;
}


void InputHandler::onMouseMove(SDL_Event& event){
    m_mousePosition->setX(event.motion.x);
    m_mousePosition->setY(event.motion.y);
}


void InputHandler::onMouseButtonDown(SDL_Event& event){
    if(event.button.button == SDL_BUTTON_LEFT)
	m_mouseButtonStates[LEFT] = true;
    else if(event.button.button == SDL_BUTTON_MIDDLE)
	m_mouseButtonStates[MIDDLE] = true;
    else if(event.button.button == SDL_BUTTON_RIGHT)
	m_mouseButtonStates[RIGHT] = true;
}


void InputHandler::onMouseButtonUp(SDL_Event& event){
    if(event.button.button == SDL_BUTTON_LEFT)
	m_mouseButtonStates[LEFT] = false;
    else if(event.button.button == SDL_BUTTON_MIDDLE)
	m_mouseButtonStates[MIDDLE] = false;
    else if(event.button.button == SDL_BUTTON_RIGHT)
	m_mouseButtonStates[RIGHT] = false;
}


int InputHandler::xvalue(int joy_id, int stick){
    if(!m_isActive) return 0;

    if(m_joysticks.size() == 0) return 0;
    if(stick == 1)
	return m_joystickValues[joy_id].first->getX();
    else if(stick == 2)
	return m_joystickValues[joy_id].second->getX();
    return 0;
}


int InputHandler::yvalue(int joy_id, int stick){
    if(!m_isActive) return 0;

    if(m_joysticks.size() == 0) return 0;
    if(stick == 1)
	return m_joystickValues[joy_id].first->getY();
    else if(stick == 2)
 	return m_joystickValues[joy_id].second->getY();
    return 0;
}


bool InputHandler::getButtonState(int joy_id, int button){
    if(!m_isActive) return 0;

    return m_buttonStates[joy_id][button];
}


Vector2D* InputHandler::getMousePosition(){
    if(!m_isActive) {
	m_mousePosition->setX(0);
	m_mousePosition->setY(0);
    }

    return m_mousePosition;
}


bool InputHandler::getMouseButtonState(int button){
    if(!m_isActive) return 0;

    if(button < 0 || button > 3) return false;
    return m_mouseButtonStates[button];
}


bool InputHandler::isKeyDown(SDL_Scancode key){
    if(!m_isActive) return 0;

    if(m_keystates == 0) return false;

    if(m_keystates[key] == 1) return true;
    else return false;
}

bool InputHandler::isKeyUp(SDL_Scancode key){
    if(!m_isActive) return 0;

    return !isKeyDown(key);
}



void InputHandler::Delay(int miliseconds){
    m_DelayStartedTime = SDL_GetTicks();
    m_DelayTime = miliseconds;
    m_isActive = false;
}

