// TiledMap.h
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef TILEDMAP_H
#define TILEDMAP_H 1

#include <string>
#include <vector>


struct Tileset {

    int m_firstgid;
    std::string m_name;
    int m_tileWidth;
    int m_tileHeight;
    int m_spacing;
    int m_margin;
    int m_tilecount;
    int m_columns;
    std::string m_imgSource;
    int m_imgWidth;
    int m_imgHeight;

};


struct Layer {

    std::string m_name;
    int m_width;
    int m_height;

    std::vector<std::vector<int>> m_data;

};


struct Object {

    int m_objectId;

    std::string m_name;
    std::string m_objectType;

    int m_gid;
    
    int m_x;
    int m_y;
    int m_width;
    int m_height;



    /* std::map<std::string, std::string> m_properties; */

};


struct TiledMap {

    int m_width;
    int m_height;
    int m_tileWidth;
    int m_tileHeight;

    std::vector<Tileset*> m_tilesets;
    std::vector<Layer*> m_layers;
    std::vector<std::vector<Object*>> m_objectLayers;

    /* Destructor..?? */
    ~TiledMap(){
	for(int i = 0; i < m_tilesets.size(); i++)
	    delete m_tilesets[i];

	for(int i = 0; i < m_layers.size(); i++)
	    delete m_layers[i];

	for(int i = 0; i < m_objectLayers.size(); i++){
	    std::vector<Object*> m_objects = m_objectLayers[i];
	    for(int j = 0; j < m_objects.size(); j++)
		delete m_objects[j];
	}

    }

};


#endif // TILEDMAP_H
//////////////////////////////////////////////////////////////////////
// $Log:$
//
