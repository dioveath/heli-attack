/* 

   World.cpp

   Author: Saroj Rai @ Charicha 
   Created On: Tuesday,  7 August 2018.

*/

#include "World.h"
#include "TiledMapParser.h"

#include "TextureManager.h"
#include "Game.h"

#include "Enemy.h"
#include "Bullet.h"
#include "AnimationManager.h"

#include "LevelCompleteState.h"
#include "MainMenuState.h"
#include "GameOverState.h"

#include <math.h>


// $Log:$ //
//



World::World()
    : m_isGameOver(false),
      m_currentLevelID(0),
      m_Selection(0),
      m_TotalSelection(2)
{ }


void World::load(const LoaderParams* pParams)
{
    SDLGameObject::load(pParams);

    m_Player = new Player();
    m_Player->load(new LoaderParams(300, 100, 128, 55, "helicopter", 5));
    TheTextureManager::Instance()->load("assets/helicopter.png",
					"helicopter",
					TheGame::Instance()->getRenderer());

    m_EnemyManager = new EnemyManager(m_Player);


    std::cout << "Half Complete..!\n";
    // Parse levels.xml
    if(!TheLevelParser::Instance()->ParseLevel(pParams->m_textureID,
					      &m_Levels,
					      &m_currentLevelID)){
	std::cout << "Parsing level failed..!\n";
    }

    std::cout << "currentLevelID: " << m_currentLevelID << std::endl;

    for(int i = 0; i < m_Levels.size(); i++){
	Level level;

	std::cout << "FILE: " << m_Levels[i].m_filename << std::endl;
	std::cout << "ID: " << m_Levels[i].m_id << std::endl;

	if(m_currentLevelID == m_Levels[i].m_id){
	    LoadMap(m_Levels[i].m_filename);
	}
    }


    TheCamera::Instance()->setCameraWidth(TheGame::Instance()->getGameWidth());
    TheCamera::Instance()->setCameraHeight(TheGame::Instance()->getGameHeight());    

    m_isGameOver = false;

    std::cout << "World loading completed..!\n";
}


void World::LoadMap(std::string mapFileName){
    TiledMapParser tParser;
    
    m_Map = tParser.parseTiledMap(mapFileName);
    
    if(!m_Map) return;

    for(int i =0; i < m_Map->m_tilesets.size(); i++){
	Tileset* pTileset = m_Map->m_tilesets[i];
	TheTextureManager::Instance()->load(pTileset->m_imgSource,
					    pTileset->m_name,
					    TheGame::Instance()->getRenderer());
    }

    m_WorldWidth = m_Map->m_layers[0]->m_data[0].size() * m_Map->m_tileWidth;
    m_WorldHeight = m_Map->m_layers[0]->m_data.size() * m_Map->m_tileHeight;

    std::cout << "World Width: " << m_WorldWidth << std::endl;
    std::cout << "World Height: " << m_WorldHeight << std::endl;

    for(int i = 0; i < m_Map->m_objectLayers.size(); i++){
	std::vector<Object*> m_objects = m_Map->m_objectLayers[i];

	if(i == 0) loadStaticObjects(&m_objects);
	if(i == 1) loadDynamicObjects(&m_objects);

    }
    

}


void World::loadStaticObjects(std::vector<Object*>* m_objects){
    for(int i = 0; i < m_objects->size(); i++){ 

	Object* o = (*m_objects)[i];

	if(o->m_objectType == std::string("Ground")){
	    SDLGameObject* gameObject = new SDLGameObject();

	    gameObject->load(new LoaderParams(o->m_x, o->m_y,
 					      o->m_width, o->m_height,
					      "Ground"));
	    m_staticObjects[o->m_name] = gameObject;
	}
	if(o->m_objectType == std::string("Finish")){
	    m_FinishPoint = new SDLGameObject();
	    m_FinishPoint->load(new LoaderParams(o->m_x, o->m_y,
						 o->m_width, o->m_height,
						 "Finish"));
	}

    }
}


void World::loadDynamicObjects(std::vector<Object*>* m_objects){
    std::cout << "Loading dynamic objects...!\n";
    for(int i = 0; i < m_objects->size(); i++){
	Object* o = (*m_objects)[i];

	if(o->m_objectType == std::string("Enemy")){

	    int gid = o->m_gid;
	    Tileset* pTileset;

	    for(int m = 0; m_Map->m_tilesets.size(); m++){
		Tileset* t = m_Map->m_tilesets[m];
		if(gid >= t->m_firstgid &&
		   gid < (t->m_firstgid + t->m_tilecount)){
		    pTileset = t;
		    break;
		}
	    }

	    gid -= pTileset->m_firstgid;

	    Enemy* enemy = new Enemy();
	    enemy->load(new LoaderParams(o->m_x, o->m_y,
					 o->m_width, o->m_height,
					 pTileset->m_name,
					 pTileset->m_tilecount)); // tilecount = numFrames

	    

	    m_EnemyManager->insertEnemy(enemy);
	}
    }
}



void World::update(){

    TheAnimationManager::Instance()->update();
    TheBulletManager::Instance()->updateBullets();
    TheBulletManager::Instance()->freeBullets();

    m_EnemyManager->updateEnemies();



    if(m_Player->isActive() && !m_isGameOver){
	m_Player->update();

	SDLGameObject* pObject = dynamic_cast<SDLGameObject*>(m_Player);

	// getting an alias here but also
	// changes is not being persistent
	Vector2D playerPos = pObject->getPosition();

	if(playerPos.getX() < 0){
	    pObject->setPositionX(0);
	}

	if(playerPos.getY() < 0){
	    pObject->setPositionY(0);
	}

	if(playerPos.getX() + pObject->getWidth() > m_WorldWidth){
	    pObject->setPositionX(m_WorldWidth - pObject->getWidth());
	}
	if(playerPos.getY() + pObject->getHeight() > m_WorldHeight){
	    pObject->setPositionY(m_WorldHeight - pObject->getHeight());
	}

	

	// if(m_EnemyManager->checkCollisionWith(pObject)){
	//     m_isGameOver = true;
	//     std::cout << "Game Over! FROM ENEMYMANAGER" << std::endl;
	//     m_Player->destroy();
	//     TheGame::Instance()->getStateMachine()->changeState(new GameOverState());
	// }

	if(TheBulletManager::Instance()->checkCollisionWith(pObject, "Player")){
	    m_isGameOver = true;
	    m_Player->destroy();
	    TheInputHandler::Instance()->Delay(1000);
	}

	for(std::map<std::string, GameObject*>::iterator it = m_staticObjects.begin();
	    it != m_staticObjects.end(); ++it){
	    if(blockCollision(pObject, dynamic_cast<SDLGameObject*>(it->second))){
		std::cout << "Colliding with ground(SDLGameObject) ..!\n";
	    }
	}

	if(checkCollision(pObject, m_FinishPoint)){
	    std::cout << "Collided with finishpoint...!\n";

	    m_currentLevelID++;

	    std::cout << "You reached " << m_currentLevelID << std::endl;

	    if(m_currentLevelID >= m_Levels.size()){
		std::cout << "THE END..!\n";
		TheLevelParser::Instance()->writeCurrentLevel(m_textureID,
							      0);

		TheGame::Instance()->getStateMachine()->changeState(new GameOverState());
	    } else {
		TheLevelParser::Instance()->writeCurrentLevel(m_textureID,
							      m_currentLevelID);

		TheGame::Instance()->getStateMachine()->changeState(new LevelCompleteState());
	    }
	    // m_isLevelComplete = true;
	    // change to level complete state...
	}

	// bound camera
	int cWidth = TheCamera::Instance()->getCameraWidth();
	int cHeight = TheCamera::Instance()->getCameraHeight();
    

	Vector2D offsetLeft(-pObject->getWidth()/2 - 100, -pObject->getHeight()/2);
	// Vector2D offsetRight(-pObject->getWidth()/2 + 200, -pObject->getHeight()/2);

	// // camera showing more right
	// Vector2D cameraTargetRight = pObject->getPosition() + offsetLeft;
	// // camera showing more left
	// Vector2D cameraTargetLeft = pObject->getPosition() + offsetRight;

	// Vector2D cameraTarget(0, 0);
	// if(m_Player->isTurningLeft()){
	//     cameraTarget = cameraTargetLeft;
	// } else {
	//     cameraTarget = cameraTargetRight;
	// }

	Vector2D cameraTarget(pObject->getPosition() - offsetLeft);


	if(cameraTarget.getX() + cWidth/2 > m_WorldWidth)
	    cameraTarget.setX(m_WorldWidth - cWidth/2);

	if(cameraTarget.getY() + cHeight/2 > m_WorldHeight)
	    cameraTarget.setY(m_WorldHeight - cHeight/2);

	if(cameraTarget.getX() - cWidth/2  < 0)
	    cameraTarget.setX(cWidth/2);

	if(cameraTarget.getY() - cHeight/2  < 0)
	    cameraTarget.setY(cHeight/2);

	

    
	TheCamera::Instance()->setTarget(cameraTarget);
	TheCamera::Instance()->update();

    } // Player

    if(m_isGameOver){

	if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)){
	    ++m_Selection;
	}
	if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)){
	    --m_Selection;
	}
	m_Selection = abs(m_Selection) % m_TotalSelection;

	if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE)){
	    std::cout << "m_Selection: " << m_Selection << std::endl;
	    if(m_Selection == 0){
		TheGame::Instance()->getStateMachine()->changeState(new GameOverState());
		TheGame::Instance()->getStateMachine()->changeState(new PlayState());
	    } else if(m_Selection == 1) {
		TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
	    }
	}
    }



    for(int i = 0; i < m_EnemyManager->getSize(); i++){
	if(m_EnemyManager->getEnemy(i)->isActive())
	    if(TheBulletManager::Instance()->checkCollisionWith(dynamic_cast<SDLGameObject*>(m_EnemyManager->getEnemy(i)), "Enemy")){
		m_EnemyManager->getEnemy(i)->destroy();
	    }
    }


    for(std::map<std::string, GameObject*>::iterator it = m_staticObjects.begin();
	it != m_staticObjects.end(); ++it){
	if(TheBulletManager::Instance()->checkCollisionWith(dynamic_cast<SDLGameObject*>
							   (it->second))){
	    // Grounds can'd be harmed! 
	}
    }

}


void World::render(){
    renderMap();

    if(m_Player->isRenderable()){
	m_Player->render();
    }


    TheBulletManager::Instance()->renderBullets();
    TheAnimationManager::Instance()->render();

    m_EnemyManager->renderEnemies();

    for(std::map<std::string, GameObject*>::iterator it = m_staticObjects.begin();
	it != m_staticObjects.end(); ++it){
	// it->second->render();

	    // SDLGameObject* static_obj = dynamic_cast<SDLGameObject*>(it->second);
	
	    // std::cout << "Rendering triangle.>!";
	    // std::cout << "PosX: " << static_obj->getPosition().getX();
	    // std::cout << "PosY: " << static_obj->getPosition().getY();
	    // std::cout << "Width: " << static_obj->getWidth();
	    // std::cout << "Height: " << static_obj->getHeight() << std::endl;


	    // TheTextureManager::Instance()->fillRect(static_obj->getPosition().getX(),
						    // static_obj->getPosition().getY(),
						    // static_obj->getWidth(),
						    // static_obj->getHeight(),
						    // TheGame::Instance()->getRenderer(),
						    // 244, 200, 140, 255);
    }


    if(m_isGameOver){
	int winWidth = TheGame::Instance()->getGameWidth();
	int winHeight = TheGame::Instance()->getGameHeight();

	int r;
	if(m_Selection == 0)
	    r = 0;
	else if(m_Selection == 1)
	    r = 255;

	TheTextureManager::Instance()->fillRectUI(winWidth/2 - 100, winHeight/2 - 300,
						  200, 200,
						  TheGame::Instance()->getRenderer(),
						  r, 200, 200, 255);


    }

}


void World::renderMap(){
    if(!m_Map) return;

    for(int k = 0; k < m_Map->m_layers.size(); k++){
	Layer* pLayer = m_Map->m_layers[k];

	int numRow = pLayer->m_data.size();

	for(int i = 0; i < numRow; i++){
	    int numColumn = pLayer->m_data[i].size();
	    for(int j = 0; j < numColumn; j++){
		int gid = pLayer->m_data[i][j];
		// if empty continue with next gid
		if(gid == 0) continue;

		Tileset* pTileset;

		for(int m = 0; m < m_Map->m_tilesets.size(); m++){
		    Tileset* t = m_Map->m_tilesets[m];
		    if(gid >= t->m_firstgid &&
		       gid < (t->m_firstgid + t->m_tilecount)){
			pTileset = t;
			break;
		    }
		}

		// adjusting global grid id to local tileset grid id
		// and making it relate to image idx idy (0 based id)
		// for rendering correct image sprite
		gid -= pTileset->m_firstgid; 
		// gid--;


		int idx = gid % pTileset->m_columns;
		int idy = gid / pTileset->m_columns;

		// std::cout << "firstgid: " << pTileset->m_firstgid << "\n";
		// std::cout << "columns: " << pTileset->m_columns << "\n";
		// std::cout << "tileWidth: " << pTileset->m_tileWidth << "\n";
		// std::cout << "tileHeight: " << pTileset->m_tileHeight << "\n";
		// std::cout << "spacing: " << pTileset->m_spacing << "\n";
		// std::cout << "idx: " << idx << "\n";
		// std::cout << "idy: " << idy << "\n\n";
		// std::cout << "i: " << i << "\n";
		// std::cout << "j: " << j << "\n";

		TheTextureManager::Instance()->drawTile(pTileset->m_name,
							pTileset->m_margin,
							pTileset->m_spacing,

							getPosition().getX() +
							j * pTileset->m_tileWidth,

							getPosition().getY() + i *
							pTileset->m_tileHeight,

							pTileset->m_tileWidth,
							pTileset->m_tileHeight,
							idy, idx,
							TheGame::Instance()->getRenderer());
						    
	    }
	}

    } // Layers Loop
}


void World::SaveLevel(std::string levelFilename, int currentLevel){
}


void World::clean(){

    delete m_EnemyManager;
    m_Player->clean();
    delete m_Player;
    TheTextureManager::Instance()->clearFromTextureMap("helicopter");

    m_Levels.clear();


    for(int i = 0; i < m_Map->m_tilesets.size(); i++){
	Tileset* pTileset = m_Map->m_tilesets[i];
	TheTextureManager::Instance()->clearFromTextureMap(pTileset->m_name);
    }

    delete m_Map;


    std::cout << "Half World cleaned..!\n";
    for(std::map<std::string, GameObject*>::iterator it = m_staticObjects.begin();
	it != m_staticObjects.end(); ++it){
	it->second->clean();
	delete it->second;
    }
    m_staticObjects.clear();

    delete m_FinishPoint;

    TheBulletManager::Instance()->clean();

    TheCamera::Instance()->reset();
    std::cout << "World Cleaned ...!\n";
}




bool World::checkCollision(SDLGameObject* p1, SDLGameObject* p2, int offset){

    int minx1 = p1->getPosition().getX() + offset;
    int maxx1 = p1->getPosition().getX() + p1->getWidth() - offset;
    int minx2 = p2->getPosition().getX() + offset;
    int maxx2 = p2->getPosition().getX() + p2->getWidth() - offset;

    int miny1 = p1->getPosition().getY() + offset;
    int maxy1 = p1->getPosition().getY() + p1->getHeight() - offset;
    int miny2 = p2->getPosition().getY() + offset;
    int maxy2 = p2->getPosition().getY() + p2->getHeight() - offset;
    
    return (minx1 <= maxx2 && maxx1 >= minx2)
    	&& (miny1 <= maxy2 && maxy1 >= miny2);
	

    // return ((p1->getPosition().getX()+20 < (p2->getPosition().getX() + p2->getWidth()-20) &&
    // 	     (p1->getPosition().getX() + p1->getWidth())-20 > p2->getPosition().getX()+20)
    // 	 && (p1->getPosition().getY() < (p2->getPosition().getY() + p2->getHeight()) &&
    // 	     (p1->getPosition().getY() + p1->getHeight()) > p2->getPosition().getY()));
}


// blocking collsiion XO
int World::blockCollision(SDLGameObject* p1, SDLGameObject* p2){

    int cx1 = p1->getPosition().getX() + p1->getWidth()/2;
    int cy1 = p1->getPosition().getY() + p1->getHeight()/2;

    int cx2 = p2->getPosition().getX() + p2->getWidth()/2;
    int cy2 = p2->getPosition().getY() + p2->getHeight()/2;

    int dx = cx2 - cx1;
    int dy = cy2 - cy1;

    int totalHalfWidth = p1->getWidth()/2 + p2->getWidth()/2;
    int totalHalfHeight = p1->getHeight()/2 + p2->getHeight()/2;

    int absdx = abs(dx);
    int absdy = abs(dy);

    if(absdx < totalHalfWidth && absdy < totalHalfHeight){

	int overlapx = totalHalfWidth - absdx;
	int overlapy = totalHalfHeight - absdy;

	if (absdy > absdx){	// y-axis
	    if(dy > 0){		// top side
		p1->getPosition().setY(p1->getPosition().getY() - overlapy);
		p1->getVelocity().setY(0);
		return 3;
	    } else { 	// bottom side
		p1->getPosition().setY(p1->getPosition().getY() + overlapy);
		p1->getVelocity().setY(0);
		return 4;
	    }
	}
	if(absdx > absdy){		// x-axis
	    if(dx > 0){		// right side
		p1->getPosition().setX(p1->getPosition().getX() - overlapx);
		p1->getVelocity().setX(0);
		return 1;
	    } else if(dx <0){	// leftside
		p1->getPosition().setX(p1->getPosition().getX() + overlapx);
		p1->getVelocity().setX(0);
		return 2;
	    }

	} 
    }
    
    return 0;
}
