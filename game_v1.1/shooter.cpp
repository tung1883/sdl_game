#pragma once

#include "Game.h"
#include "Shooter.h"
#include "Texture.h"

//Load the shooter with default value: m_dead = false, m_dying = false
Shooter::Shooter(const ObjectParams* params)
	:GameObject(params)
{
	m_dead = false;
	m_dying = false;

	m_dyingCounter = 0;
	m_dyingTime = 0;

	m_recoilCounter = 0;
	m_recoilSpeed = 0;

};


void Shooter::draw() {
	GameObject::draw();
}
void Shooter::update() {
	GameObject::update();
}

void Shooter::clean() {
	GameObject::clean();
}

void Shooter::doDyingAnimation() {
	scroll(SCROLL_SPEED);

	m_currentFrame = (int) ((SDL_GetTicks() / (1000 / 3)) % m_numFrames);

	GameObject::changeTexture(new ObjectParams("explosion", 0, 0, 0, 0, 0, 0));

	m_dying = true;

	if (m_dyingCounter == m_dyingTime) {
		m_dying = false;
		GameObject::changeTexture(new ObjectParams("helicopter", 0, 0, 128, 55, 5));
	}
	
	m_dyingCounter++;
}