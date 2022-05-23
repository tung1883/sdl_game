#pragma once

#include "ObjectLayer.h"

void ObjectLayer::update() {
	for (auto i : m_gameObjects) {
		i->update();
	}
}

void ObjectLayer::render() {
	for (auto i : m_gameObjects) {
		i->draw();
	}
}