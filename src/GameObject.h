// GameObject.h
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H 1


#include <string>


class LoaderParams {

 public:

 LoaderParams(int x, int y, int width, int height, std::string textureID,
	      int numFrames = 1, int animSpeed = 14, int callbackID = 0)
     :m_x(x), m_y(y), m_width(width), m_height(height),
	m_textureID(textureID),
	m_numFrames(numFrames),
	m_animSpeed(animSpeed),
	m_callbackID(callbackID)  { }

    int m_x, m_y;
    int m_width, m_height;

    std::string m_textureID;
    int m_numFrames;
    int m_animSpeed;
    int m_callbackID;

    std::string m_id;
};




class GameObject {

 public:
    virtual void load(const LoaderParams* pParams) { }
    virtual void update()=0;
    virtual void render()=0;
    virtual void clean()=0;

    GameObject() { }
    virtual ~GameObject() { }
    

};


#endif // GAMEOBJECT_H
//////////////////////////////////////////////////////////////////////
// $Log:$
//
