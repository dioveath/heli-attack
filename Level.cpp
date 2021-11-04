/* 

   Level.cpp

   Author: Saroj Rai @ Charicha 
   Created On: Thursday,  2 August 2018.

*/

#include "Level.h"
#include "TiledMapParser.h"
#include "TextureManager.h"
#include "Game.h"

// $Log:$ //
//



void Level::load(const LoaderParams* pParams)
{
    SDLGameObject::load(pParams);
    TiledMapParser tParser;
    // pParams->m_textureID : Just a hack need  to reimplement whole system for how
    // i integrate tiledmap map to my game
    m_Map = tParser.parseTiledMap(pParams->m_textureID); 

    for(int i = 0; i < m_Map->m_tilesets.size(); i++){
	Tileset *pTileset = m_Map->m_tilesets[i];
	TheTextureManager::Instance()->load(pTileset->m_imgSource,
					    pTileset->m_name,
					    TheGame::Instance()->getRenderer());
    }
}





void Level::update() {
    SDLGameObject::update();
}


void Level::render() {
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
		       gid <= (t->m_firstgid + t->m_tilecount)){
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

							m_position.getX() +
							j * pTileset->m_tileWidth,

							m_position.getY() + i *
							pTileset->m_tileHeight,

							pTileset->m_tileWidth,
							pTileset->m_tileHeight,
							idy, idx,
							TheGame::Instance()->getRenderer());
						    
	    }
	}

    } // Layers Loop

}


void Level::clean(){
    delete m_Map;
}

    
