// InputHandler.h
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H 1


#include <iostream>
#include <vector>

#include <SDL2/SDL.h>

#include "Vector2D.h"


enum mouse_buttons {
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};


class InputHandler {

 public:
    static InputHandler* Instance() {
	if(!s_pInstance){
	    s_pInstance = new InputHandler();
	}
	return s_pInstance;
    }

    void initializeJoysticks();
    void update();
    void clean();

    bool joystickInitialized() const { return m_bJoysticksInitialized; }

    int xvalue(int joy_id, int stick);
    int yvalue(int joy_id, int stick);
    bool getButtonState(int joy_id, int button);
    Vector2D* getMousePosition();
    bool getMouseButtonState(int button);
    bool isKeyDown(SDL_Scancode key);
    bool isKeyUp(SDL_Scancode key);

    void Delay(int miliseconds);

 private:

    InputHandler()
	:m_isActive(true),
	 m_DelayStartedTime(0),
	 m_DelayTime(0)
    {
	m_mousePosition = new Vector2D(0, 0);
	for(int i = 0; i < 3; i++)
	    m_mouseButtonStates.push_back(false);
    }
    ~InputHandler() { }

    static InputHandler* s_pInstance;

    std::vector<SDL_Joystick*> m_joysticks;
    std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
    std::vector<std::vector<bool>> m_buttonStates;
    bool m_bJoysticksInitialized;
    const int m_joystickDeadZone = 10000;
    
    Vector2D* m_mousePosition;
    std::vector<bool> m_mouseButtonStates;

    const Uint8* m_keystates;

    void onJoystickAxisMove(SDL_Event& event);
    void onJoystickButtonDown(SDL_Event& event);
    void onJoystickButtonUp(SDL_Event& event);

    void onMouseMove(SDL_Event& event);
    void onMouseButtonDown(SDL_Event& event);
    void onMouseButtonUp(SDL_Event& event);

    /* for reseting */
    int m_isActive;
    int m_DelayStartedTime;
    int m_DelayTime;

};


typedef InputHandler TheInputHandler;



#endif // INPUTHANDLER_H
//////////////////////////////////////////////////////////////////////
// $Log:$
//
