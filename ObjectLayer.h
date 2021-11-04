// ObjectLayer.h
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef OBJECTLAYER_H
#define OBJECTLAYER_H 1


class ObjectLayer : public Layer {

 public:
    virtual void update();
    virtual void render();

    std::vector<GameObject*>* getGameObjects() {
	return &m_gameObjects;
    }

 private:
    std::vector<GameObject*> m_gameObjects;

};


#endif // OBJECTLAYER_H
//////////////////////////////////////////////////////////////////////
// $Log:$
//
