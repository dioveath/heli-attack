// TileLayer.h  
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef TILELAYER_H
#define TILELAYER_H 1


#include "Layer.h"
#include "Level.h"


class TileLayer : public Layer {

 public:
    TileLayer(int tileSize, const std::vector<Tileset> &tilesets);

    virtual void update();
    virtual void render();

    void setTileIDs(const std::vector<std::vector<int>>& data) { m_tileIDs = data; }
    void setTileSize(int tileSize) { m_tileSize = tileSize; }
    Tileset getTilesetByID(int tileID);

 private:
    int m_numColumns;
    int m_numRows;
    int m_tileSize;


    Vector2D m_position;
    Vector2D m_velocity;

    const std::vector<Tileset> &m_tilesets;
    std::vector<std::vector<int>> m_tileIDs;

};





#endif // TILELAYER_H
//////////////////////////////////////////////////////////////////////
// $Log:$
//
