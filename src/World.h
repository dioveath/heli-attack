// World.h
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef WORLD_H
#define WORLD_H 1


#include <map>

#include "TiledMap.h"
#include "SDLGameObject.h"
#include "EnemyManager.h"
#include "Player.h"

#include "LevelParser.h"

class World : public SDLGameObject {

 public:
    World();

    virtual void load(const LoaderParams* pParams);
    virtual void update();
    virtual void render();
    virtual void clean();
    
    static bool checkCollision(SDLGameObject* p1, SDLGameObject* p2, int offset=5);
    static int blockCollision(SDLGameObject* p1, SDLGameObject* p2);

    
 private:
    void LoadMap(std::string mapFileName);
    void loadStaticObjects(std::vector<Object*>* m_objects);
    void loadDynamicObjects(std::vector<Object*>* m_objects);
    void renderMap();
    void SaveLevel(std::string levelFilename, int currentLevel);

    TiledMap* m_Map;
    Player* m_Player;
    EnemyManager* m_EnemyManager;
    SDLGameObject* m_FinishPoint;
    std::map<std::string, GameObject*> m_staticObjects; /* for static objects */

    int m_WorldWidth;
    int m_WorldHeight;


    bool m_isGameOver;
    /* bool m_isLevelComplete; */
    int m_Selection;
    int m_TotalSelection;
    
    
    std::vector<Level> m_Levels;
    int m_currentLevelID;

 
};


class WorldCreator : public BaseCreator {

 public:
    GameObject* createGameObject() const {
	return new World();
    }

};



#endif // WORLD_H
//////////////////////////////////////////////////////////////////////
// $Log:$
//
