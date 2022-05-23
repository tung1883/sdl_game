#pragma once

#include <iostream>
#include <vector>

#include "Layer.h"
#include "GameObject.h"

class ObjectLayer : public Layer
{
public:
	virtual void update();
	virtual void render();

	//getters
	std::vector<GameObject*>* getGameObjects() {
		return &m_gameObjects;
	};

private:
	std::vector<GameObject*> m_gameObjects;
	
};