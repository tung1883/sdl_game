#pragma once

#include <map>
#include <string>
#include <tinyxml.h>

#include "GameMap.h"
#include "TileLayer.h"
#include "ObjectLayer.h"

class MapParser
{
public:
	static MapParser* Instance() {
		if (mapInstance == NULL) {
			mapInstance = new MapParser();
		}
		return mapInstance;
	}

	bool parse(std::string id, std::string source);
	void clean();
	inline GameMap* getMaps(std::string id) {
		return m_Maps[id];
	};

	//get tile and object layers of a map
	std::vector<TileLayer*> getTileLayers(std::string id) {
		return m_Maps[id]->m_TileLayers;
	}
	std::vector<ObjectLayer*> getObjectLayer(std::string id) {
		return m_Maps[id]->m_ObjectLayers;
	}
	
private:
	MapParser() {};
	static MapParser* mapInstance;

	Tileset ParseTileset(TiXmlElement* xmlTileset);
	TileLayer* ParseTileLayer(TiXmlElement* xmlTileLayer, TilesetList tilesets, int tileSize, int rowCount, int colCount);
	
	void ParseTextures(TiXmlElement* xmlTextureRoot);
	ObjectLayer* ParseObjectLayer(TiXmlElement* xmlObjectLayer);

	std::map<std::string, GameMap*> m_Maps;
};

typedef MapParser TheMapParser;