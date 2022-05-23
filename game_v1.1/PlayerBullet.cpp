#pragma once

#include "PlayerBullet.h"
#include "ObjectParams.h"

PlayerBullet::PlayerBullet(const ObjectParams* params, Vector2D heading) : GameObject(params), m_heading(heading)
{}

void PlayerBullet::draw() {
	GameObject::draw();
}

void PlayerBullet::update() {
	m_currentFrame = int((SDL_GetTicks() / 100 % m_numFrames));

	m_velocity.setX(m_heading.getX());
	m_velocity.setY(m_heading.getY());

	GameObject::update();
}

void PlayerBullet::clean() {
	GameObject::clean();
}
