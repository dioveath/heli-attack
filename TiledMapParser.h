// TiledMapParser.h
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef TILEDMAPPARSER_H
#define TILEDMAPPARSER_H 1


#include "TiledMap.h"
#include "tinyxml.h"


class TiledMapParser {

 public:
    TiledMapParser() { }
    TiledMap* parseTiledMap(std::string fileName);
    void parseTileset(TiXmlElement* pTilesetRoot, std::vector<Tileset*>* pTilesets);
    void parseLayers(TiXmlElement* pTileLayerRoot, std::vector<Layer*>* pLayers);
    void parseObjects(TiXmlElement* pObjectRoot,
		      std::vector<std::vector<Object*>>* pObjects);

};


#endif // TILEDMAPPARSER_H
//////////////////////////////////////////////////////////////////////
// $Log:$
//
