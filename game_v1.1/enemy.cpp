#pragma once

#include "Game.h"
#include "Enemy.h"

Enemy::Enemy(const ObjectParams* params)
	:Shooter(params)
{
	m_health = 3;
}

void Enemy::draw() 
{
	Shooter::draw();
}

void Enemy::update() {
	m_currentFrame = int((SDL_GetTicks() / 100 % m_numFrames));
}

void Enemy::handleAnimation() {

}

void Enemy::handleBullet() {

}

void Enemy::doDyingAnimation() {
	GameObject::changeTexture(new ObjectParams("explosion", 0, 0, 42, 40, 9, 1));
	GameObject::scroll(SCROLL_SPEED);
}

void Enemy::collision() {
	if (m_health != 0) {
		m_health--;
	}
}

void Enemy::clean() {
	Shooter::clean();
}
