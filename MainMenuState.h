// MenuState.h
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H 1


#include "MenuState.h"
#include "PlayState.h"
#include "GameObject.h"


class MainMenuState : public MenuState {

 public:
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const { return s_menuID; }

    virtual void setCallbacks(const std::vector<Callback>& callbacks);

 private:
    static const std::string s_menuID;

    std::vector<GameObject*> m_gameObjects;


    /* call back functions for menu buttons */
    static void s_menuToPlay();
    static void s_exitFromMenu();

    int m_MusicID;


};


#endif // MAINMENUSTATE_H
//////////////////////////////////////////////////////////////////////
// $Log:$
//
