#pragma once

#include <tinyxml.h>
#include <tinystr.h>

#include "Game.h"
#include "Texture.h"
#include "MapParser.h"
#include "Player.h"
#include "Cyrer.h"
#include "Glider.h"
#include "Slinger.h"
#include "Boss.h"

MapParser* MapParser::mapInstance = NULL;

bool MapParser::parse(std::string id, std::string source) {
	TiXmlDocument xml;
	xml.LoadFile(source);

	if (xml.Error()) {
		std::cout << "Failed to load" << source << std::endl;
		return false;
	}
	
	TiXmlElement* root = xml.RootElement();
	int rowCount, colCount, tileSize = 0;

	root->Attribute("width", &colCount);
	root->Attribute("height", &rowCount);
	root->Attribute("tilewidth", &tileSize);

	//Parse Tile Sets
	TilesetList tilesets;
	for (TiXmlElement* e = root->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
		if (e->Value() == std::string ("tileset")) {
			tilesets.push_back(ParseTileset(e));
		}
	}

	GameMap* gameMap = new GameMap();

	//Parse Tile Layers
	for (TiXmlElement* e = root->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
		if (e->Value() == std::string ("layer")) {
			TileLayer* tileLayer = ParseTileLayer(e, tilesets, tileSize, rowCount, colCount);
			gameMap->m_TileLayers.push_back(tileLayer);
		}
	}

	//Parse Object Layers
	for (TiXmlElement* e = root->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("objectgroup")) {
			ObjectLayer* objectLayer = ParseObjectLayer(e);
			gameMap->m_ObjectLayers.push_back(objectLayer);
		}
	}

	m_Maps[id] = gameMap;
	return true;
}


Tileset MapParser::ParseTileset(TiXmlElement* xmlTileset) {
	Tileset tileset;
	tileset.Name = xmlTileset->Attribute("name");
	xmlTileset->Attribute("firstgid", &tileset.FirstID);

	xmlTileset->Attribute("tilecount", &tileset.TileCount);
	tileset.LastID = tileset.FirstID + tileset.TileCount - 1;

	xmlTileset->Attribute("columns", &tileset.ColCount);
	tileset.RowCount = tileset.TileCount / tileset.ColCount;
	xmlTileset->Attribute("tilewidth", &tileset.TileSize);
	xmlTileset->Attribute("margin", &tileset.margin);
	xmlTileset->Attribute("spacing", &tileset.spacing);

	TiXmlElement* image = xmlTileset->FirstChildElement();
	tileset.Source = image->Attribute("source");

	return tileset;
}

TileLayer* MapParser::ParseTileLayer(TiXmlElement* xmlTileLayer, TilesetList tilesets, int tileSize, int rowCount, int colCount) {
	TiXmlElement* data = NULL;
	for (TiXmlElement* e = xmlTileLayer->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
		if (e->Value() == std::string ("data")) {
			data = e;
			break;
		}
	}

	if (data == NULL) {
		std::cout << "Can not load tile layer data" << std::endl;
		return NULL;
	}

	std::string matrix(data->GetText());
	std::istringstream iss(matrix);
	std::string id;

	TileMap tilemap(rowCount, std::vector<int>(colCount+2, 0));

	for (int row = 0; row < rowCount; row++) {
		for (int col = 0; col < colCount; col++) {
			getline(iss, id, ',');
			std::stringstream converter(id);
			converter >> tilemap[row][col];
			if (!iss.good()) {
				break;
			}
		}
	}

	return (new TileLayer(tileSize, tilemap, tilesets));
}

void MapParser::ParseTextures(TiXmlElement* xmlTextureRoot) {
	std::string textureName = xmlTextureRoot->Attribute("name");
	std::string filePath = "res/" + textureName + ".png";
	TheTextureManager::Instance()->loadTexture(filePath.c_str(), textureName, TheGame::Instance()->getRenderer());
}

ObjectLayer* MapParser::ParseObjectLayer(TiXmlElement* xmlObjectLayer) {
	ObjectLayer* pObjectLayer = new ObjectLayer();
	
	for (TiXmlElement* e = xmlObjectLayer->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("object"))
		{
 			int x, y, width, height, numFrames, numRows = 1;
			std::string textureID;
			std::string type;
			GameObject* pObject;

			// get the initial node values type, x and y
			e->Attribute("x", &x);
			e->Attribute("y", &y);
			type = e->Attribute("type");

			//Get the following values: textureID, numFrames, numRows, width, height
			for (TiXmlElement* properties = e->FirstChildElement(); properties != NULL; properties = properties->NextSiblingElement())
			{
				if (properties->Value() == std::string("properties"))
				{
					for (TiXmlElement* property = properties->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
					{
						if (property->Value() == std::string("property"))
						{
							if (property->Attribute("name") == std::string("numFrames"))
							{
								property->Attribute("value", &numFrames);
							}
							else if (property->Attribute("name") == std::string("numRows"))
							{
								property->Attribute("value", &height);
							}
							else if (property->Attribute("name") == std::string("textureHeight"))
							{
								property->Attribute("value", &height);
							}
							else if (property->Attribute("name") == std::string("textureID"))
							{
								textureID = property->Attribute("value");
							}
							else if (property->Attribute("name") == std::string("textureWidth"))
							{
								property->Attribute("value", &width);
							}
						}
					}
				}
			}

			//Create objet according to diffrent types
			if (type == "cyrer") {
				pObject = new Cyrer(new ObjectParams(textureID, x, y, width, height, numFrames, numRows));
			}
			if (type == "slinger") {
				pObject = new Slinger(new ObjectParams(textureID, x, y, width, height, numFrames, numRows));
			}
			if (type == "glider") {
				pObject = new Glider(new ObjectParams(textureID, x, y, width, height, numFrames, numRows));
			}
			if (type == "boss") {
				pObject = new Boss(new ObjectParams(textureID, x, y, width, height, numFrames, numRows));
			}

			pObjectLayer->getGameObjects()->push_back(pObject);
		}
	}
	return pObjectLayer;
}
void MapParser::clean() {

}