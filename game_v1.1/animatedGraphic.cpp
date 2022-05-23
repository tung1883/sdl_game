#pragma once

#include "AnimatedGraphic.h"
#include "GameObject.h"
#include "ObjectParams.h"
#include "InputHandler.h"

AnimatedGraphic::AnimatedGraphic(const ObjectParams* params, int animateSpeed)
	:GameObject(params), m_animateSpeed(animateSpeed)
{}

void AnimatedGraphic::draw() {
	GameObject::draw();
}

void AnimatedGraphic::update()
{
	m_currentFrame = int ((SDL_GetTicks() / (1000 / m_animateSpeed)) % m_numFrames);
}

void AnimatedGraphic::clean() {
	GameObject::clean();
}