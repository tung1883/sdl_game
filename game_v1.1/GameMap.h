#pragma once

#include <vector>
#include "Layer.h"
#include "TileLayer.h"
#include "ObjectLayer.h"

class GameMap
{
public:
	void render() {
		for (auto i : m_TileLayers) {
			i->render();
		}
		for (auto i : m_ObjectLayers) {
			i->render();
		}
	}
	void update() {
		for (auto i : m_TileLayers) {
			renderedCol++;
			i->update();
		}
		for (auto i : m_ObjectLayers) {
			i->update();
		}
	}

	bool updating = true;

private:
	int renderedCol = 0;
	friend class MapParser;
	std::vector<TileLayer*> m_TileLayers;
	std::vector<ObjectLayer*> m_ObjectLayers;
};