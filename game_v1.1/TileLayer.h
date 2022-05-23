#pragma once

#include <string>
#include <vector>

#include "Math.h"
#include "Layer.h"

const int TILE_LAYER_WIDTH = 3840;

struct Tileset {
	int FirstID, LastID;
	int RowCount, ColCount;
	int TileCount, TileSize;
	int margin, spacing;
	std::string Name, Source;
};

using TilesetList = std::vector<Tileset>;
using TileMap = std::vector<std::vector<int> >;

class TileLayer: public Layer
{
public:
	TileLayer(int tileSize, TileMap tileMap, TilesetList tilesets);
	virtual void render();
	virtual void update();
	
	//Getters
	TileMap getTileMap() { return m_TileMap; };
	int getTileSize() { return m_TileSize; };
	Vector2D getPosition() { return m_position; };

private:
	int m_TileSize;
	int m_RowCount, m_ColCount;
	TileMap m_TileMap;
	TilesetList m_Tilesets;
	Vector2D m_position, m_velocity;
};