/* 

   TiledMapParser.cpp

   Author: Saroj Rai @ Charicha 
   Created On: Friday,  3 August 2018.

*/

#include <iostream>

#include "TiledMapParser.h"


// $Log:$ //
//


TiledMap* TiledMapParser::parseTiledMap(std::string fileName){
    
    TiXmlDocument mapFile;
    if(!mapFile.LoadFile(fileName)){
	std::cerr << mapFile.ErrorDesc() << ", Loading error!\n";
	return 0;
    }

    TiledMap* pTiledMap = new TiledMap();
    
    TiXmlElement* pRoot = mapFile.RootElement();

    // accessing attribute of mapFile (xml)
    std::cout << "Loading Map File...!\n";
    std::cout << "Version: " << pRoot->Attribute("version") << "\n";
    std::cout << "TiledVersion: " << pRoot->Attribute("tiledversion") << "\n";
    std::cout << "Width: " << pRoot->Attribute("width") << "\n";
    std::cout << "Height: " << pRoot->Attribute("height") << "\n";


    pRoot->Attribute("tilewidth", &(pTiledMap->m_tileWidth));
    pRoot->Attribute("tileheight", &(pTiledMap->m_tileHeight));


    for(TiXmlElement* e = pRoot->FirstChildElement(); e != 0;
	e = e->NextSiblingElement()){
	if(e->Value() == std::string("tileset")){
	    // TODO(Saroj): handle relative path of image source
	    parseTileset(e, &pTiledMap->m_tilesets);
	} else if(e->Value() == std::string("layer")){
	    parseLayers(e, &pTiledMap->m_layers);
	} else if(e->Value() == std::string("objectgroup")){
	    
	    // We'll store all objects of all objectlayer in a single m_objects structure
	    parseObjects(e, &pTiledMap->m_objectLayers);
	}
    }

    return pTiledMap;
}


void TiledMapParser::parseTileset(TiXmlElement* pTilesetRoot,
				  std::vector<Tileset*>* pTilesets){
    
    Tileset* pTileset = new Tileset();
    pTilesetRoot->Attribute("firstgid", &pTileset->m_firstgid);

    // parsing the .tsx (Tiledset) file 
    TiXmlDocument tileSetDoc;
    tileSetDoc.LoadFile(pTilesetRoot->Attribute("source"));

    TiXmlElement* pRoot = tileSetDoc.RootElement();

    pTileset->m_name = pRoot->Attribute("name");

    pRoot->Attribute("tilewidth", &pTileset->m_tileWidth);
    pRoot->Attribute("tileheight", &pTileset->m_tileHeight);
    pRoot->Attribute("spacing", &pTileset->m_spacing);
    pRoot->Attribute("margin", &pTileset->m_margin);
    pRoot->Attribute("tilecount", &pTileset->m_tilecount);
    pRoot->Attribute("columns", &pTileset->m_columns);

    for(TiXmlElement* e = pRoot->FirstChildElement(); e != 0;
    	e = e->NextSiblingElement()){
    	if(e->Value() == std::string("image")){
    	    pTileset->m_imgSource = e->Attribute("source");
    	    e->Attribute("width", &pTileset->m_imgWidth);
    	    e->Attribute("height", &pTileset->m_imgHeight);
    	    break;
    	}
    }

    pTilesets->push_back(pTileset);
    std::cout << "Tileset parsing completed...!\n";
}


void TiledMapParser::parseLayers(TiXmlElement* pTileLayerRoot,
				std::vector<Layer*>* pLayers){
    std::cout << "Parsing layers...!\n";
    Layer* pLayer = new Layer();

    pLayer->m_name = pTileLayerRoot->Attribute("name");
    pTileLayerRoot->Attribute("width", &pLayer->m_width);
    pTileLayerRoot->Attribute("height", &pLayer->m_height);

    for(TiXmlElement* e = pTileLayerRoot->FirstChildElement(); e != 0;
	e = e->NextSiblingElement()){
	if(e->Value() == std::string("data") &&
	   e->Attribute("encoding") == std::string("csv")){

	    std::istringstream iss(e->GetText());
	    int currentDataRow = 0;
	    
	    while(iss){
		std::vector<int> column_data;
		for(int i = 0; i < pLayer->m_width; i++){
		    int gid;
		    iss >> gid;
		    column_data.push_back(gid);

		    char ch;
		    iss >> ch;
		    if(ch != ',') {
			// I think I need to reach here at least one time(at last)
			// but It's not happening...! XO
			std::cout << "',' missing...!\n";
		    }
		}

		pLayer->m_data.push_back(column_data);
		currentDataRow++;
	    }

	    // DEBUG
	    // for(int i = 0; i < (pLayer->m_data).size(); i++){
	    // 	for(int j = 0; j < pLayer->m_data[i].size(); j++){
	    // 	    std::cout << pLayer->m_data[i][j] << "\t ";
	    // 	}
	    // 	std::cout << "\n";
	    // }

	}
    } // Layer's elements loop


    pLayers->push_back(pLayer);
}


void TiledMapParser::parseObjects(TiXmlElement* pObjectRoot,
				  std::vector<std::vector<Object*>>* pObjectLayers){
    std::cout << "Parsing objects...!\n";

    std::vector<Object*> tempObjects;

    for(TiXmlElement* e = pObjectRoot->FirstChildElement(); e != 0;
	e = e->NextSiblingElement()){
	if(e->Value() == std::string("object")){
	    Object* o = new Object();

	    e->Attribute("id", &o->m_objectId);

	    e->Attribute("gid", &o->m_gid);

	    e->Attribute("x", &o->m_x);
	    e->Attribute("y", &o->m_y);
	    e->Attribute("width", &o->m_width);
	    e->Attribute("height", &o->m_height);

	    if(e->Attribute("name"))
		o->m_name = e->Attribute("name");
	    if(e->Attribute("type"))
		o->m_objectType = e->Attribute("type");

	    tempObjects.push_back(o);
	}
    }


    pObjectLayers->push_back(tempObjects);
}
