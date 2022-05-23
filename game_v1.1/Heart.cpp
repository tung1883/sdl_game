#pragma once

#include "Heart.h"
#include "GameObject.h"
#include "ObjectParams.h"
#include "InputHandler.h"

Heart::Heart(const ObjectParams* params)
	:GameObject(params)
{}

void Heart::draw() {
	GameObject::draw();
}

void Heart::update()
{
	m_currentFrame = int((SDL_GetTicks() / 100) % m_numFrames);
}

void Heart::clean() {
	GameObject::clean();
}