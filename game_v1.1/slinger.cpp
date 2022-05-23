#pragma once

#include "Slinger.h"
#include "Sound.h"
#include "Game.h"

Slinger::Slinger(const ObjectParams* params)
	:Enemy(params)
{
	m_bulletSpeed = -5;
	m_speed = 3;
	m_velocity.setX(-m_speed);
	m_recoilCounter = 0;
	m_recoilSpeed = 60;
	m_health = 3;
}

void Slinger::draw() {
	Enemy::draw();
}

void Slinger::update() {
	if (m_updating) {
		m_position.setX(m_position.getX() + m_velocity.getX());
		handleAnimation();
		if (!m_dead && !m_dying) {
			handleBullet();
		}
		m_currentFrame = int((SDL_GetTicks() / 100 % m_numFrames));
	}
}

void Slinger::handleAnimation() {
	//COLLISION FUNCTIONS 
	if (m_health == 0) {
		m_dying = true;
	}
	if (m_position.getX() + SLINGER_WIDTH <= 0 || m_position.getY() <= 0 || m_position.getY() + SLINGER_WIDTH >= GAME_WIDTH) {
		m_dying = false;
		m_dead = true;
	}
	if (m_dying) {
		doDyingAnimation();
	}
	if (m_dead) {
		setUpdating(false);
	}
}

void Slinger::handleBullet() {
	//Symbols denoting direction of bullet: -> (RIGHT), <- (LEFT), ^ (UP), !^ (DOWN)
	//D stands for wanted distance (between bullet and object)
	//For ->: WIDTH: + OBJECT_WIDTH + D
	//For <-: WIDTH: -D - BULLET_WIDTH
	//For 0 horizontally: WIDTH: + OBJECT_WIDTH/2 + BULLET_WIDTH/2
	//For ^: HEIGHT: -D - BULLET_HEIGHT
	//For !^: HEIGHT: +D + OBJECT_WIDTH
	//For 0 vertically: HEIGHT: + OBJECT_HEIGHT/2 - BULLET_HEIGHT/2
	//WANTED DISTANCE HERE IS 2

	if (m_recoilCounter == m_recoilSpeed) {
		TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() - BULLET2_WIDTH - SLINGER_DISTANCE, m_position.getY() + SLINGER_HEIGHT / 2 - BULLET2_HEIGHT / 2,
			BULLET2_WIDTH, BULLET2_HEIGHT, "bullet2", 1, Vector2D(m_bulletSpeed, 0)); //<-, 0
		m_recoilCounter = 0;
	}
	m_recoilCounter++;
}

void Slinger::doDyingAnimation() {
	GameObject::changeTexture(new ObjectParams("explosion", 0, 0, 42, 40, 9, 1));
	GameObject::scroll(SCROLL_SPEED);
	m_currentFrame = int((SDL_GetTicks() / 100 % m_numFrames));
}

void Slinger::collision() {
	TheSoundManager::Instance()->playSound("explosionEffect", 1);
	if (m_health != 0) {
		m_health--;
	}
}

void Slinger::clean() {
	Enemy::clean();
}