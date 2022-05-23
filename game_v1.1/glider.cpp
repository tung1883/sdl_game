#pragma once

#include "Game.h"
#include "InputHandler.h"
#include "Sound.h"
#include "Glider.h"

Glider::Glider(const ObjectParams* params)
	:Enemy(params)
{
	m_bulletSpeed = -8;
	m_speed = 5;
	m_velocity.setX(-m_speed);
	m_recoilCounter = 0;
	m_recoilSpeed = 120;
	m_health = 3;
}

void Glider::draw() {
	Enemy::draw();
}

void Glider::update() {
	if (m_updating) {
		m_position.setX(m_position.getX() + m_velocity.getX());
		handleAnimation();
		if (!m_dying) {
			handleBullet();
		}
		m_currentFrame = int((SDL_GetTicks() / 100 % m_numFrames));
	}
}

void Glider::handleBullet() {
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
		TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() - BULLET1_WIDTH - GLIDER_DISTANCE, m_position.getY() + GLIDER_HEIGHT/2 - BULLET1_HEIGHT/2,
			BULLET1_WIDTH, BULLET1_HEIGHT, "bullet1", 1, Vector2D(m_bulletSpeed, 0));
		m_recoilCounter = 0;
	}
	m_recoilCounter++;
}

void Glider::handleAnimation() {
	//COLLISION FUNCTIONS 
	if (m_health == 0) {
		m_dying = true;
	}
	if (m_position.getX() + GLIDER_WIDTH <= 0 || m_position.getY() <= 0 || m_position.getY() + GLIDER_HEIGHT >= GAME_WIDTH) {
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

void Glider::doDyingAnimation() {
	GameObject::changeTexture(new ObjectParams("explosion", 0, 0, 42, 40, 9, 1));
	GameObject::scroll(SCROLL_SPEED);
	m_currentFrame = int((SDL_GetTicks() / 100 % m_numFrames));
}

void Glider::collision() {
	TheSoundManager::Instance()->playSound("explosionEffect", 1);
	if (m_health != 0) {
		m_health--;
	}
}

void Glider::clean() {
	Enemy::clean();
}