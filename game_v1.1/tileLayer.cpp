#pragma once

#include "TileLayer.h"
#include "Game.h"
#include "Texture.h"

TileLayer::TileLayer(int tileSize, TileMap tileMap, TilesetList tilesets)
	:m_TileSize(tileSize), m_TileMap(tileMap), m_Tilesets(tilesets)
{
	m_RowCount = GAME_HEIGHT / tileSize;
	m_ColCount = GAME_WIDTH / tileSize + 2;

	for (int i = 0; i < m_Tilesets.size(); i++) {
		std::string sourcePath = "res/Tile/" + m_Tilesets[i].Source;
		TheTextureManager::Instance()->loadTexture(sourcePath.c_str(), m_Tilesets[i].Name, 
			TheGame::Instance()->getRenderer());
	}
	m_position = Vector2D(0, 0);
	m_velocity = Vector2D(0, 0);
}

void TileLayer::render() {
	//Positioning the layer while scrolling
	int x, y, x2, y2;
	x = m_position.getX() / m_TileSize;
	y = m_position.getY() / m_TileSize;
	x2 = int(m_position.getX()) % m_TileSize;
	y2 = int(m_position.getY()) % m_TileSize;
	
	for (int j = 0; j < m_ColCount; j++) {
		for (int i = 0; i < m_RowCount; i++) {
			int tileID = m_TileMap[i][j+x];

			//tileID = 0 -> nothing to draw 
			if (tileID == 0) {
				continue;
			}
			else {
				//Finding which tileset to draw
				int index = 0;
				if (m_Tilesets.size() > 1) {
					for (int k = 1; k < m_Tilesets.size(); k++) {
						if (tileID >= m_Tilesets[k].FirstID && tileID <= m_Tilesets[k].LastID) {
							tileID = tileID + m_Tilesets[k].TileCount - m_Tilesets[k].LastID;
							index = k;
							break;
						}
					}
				}

				Tileset ts = m_Tilesets[index];
				
				int tileRow = tileID / ts.ColCount + 1;
				int tileCol = tileID - (tileRow-1) * ts.ColCount ;
	
				TheTextureManager::Instance()->drawTile(ts.Name, ts.margin, ts.spacing,
					(j * m_TileSize) - x2, (i * m_TileSize) - y2, m_TileSize, m_TileSize,
					tileRow-1, tileCol-1, TheGame::Instance()->getRenderer());
			}			
		}
	}
}

void TileLayer::update() {
	if (m_position.getX() == TILE_LAYER_WIDTH - GAME_WIDTH) {
		return;
	}
	m_position += m_velocity;
	m_velocity.setX(1);
}