#pragma once

#include "Cyrer.h"
#include "Sound.h"
#include "Game.h"

Cyrer::Cyrer(const ObjectParams* params)
	:Enemy(params)
{
	//Ensure the bullet speed is positive and speed is negative
	m_bulletSpeed = -5;
	m_speed = 1;
	m_velocity.setX(-m_speed);;
	m_recoilCounter = 0;
	m_recoilSpeed = 60;
	m_health = 1;
}

void Cyrer::draw() {
	Enemy::draw();
}

void Cyrer::update() {
	if (m_updating) {
		m_position.setX(m_position.getX() + m_velocity.getX());
		handleAnimation();
		if (!m_dying) {
			handleBullet();
		}
		m_currentFrame = int((SDL_GetTicks() / 100 % m_numFrames));
	}
}

void Cyrer::handleBullet() {
	if (m_recoilCounter == m_recoilSpeed) {
		//Symbols denoting direction of bullet: -> (RIGHT), <- (LEFT), ^ (UP), !^ (DOWN)
		//D stands for wanted distance (between bullet and object)
		//For ->: WIDTH: + OBJECT_WIDTH + D
		//For <-: WIDTH: -D - BULLET_WIDTH
		//For 0 horizontally: WIDTH: + OBJECT_WIDTH/2 + BULLET_WIDTH/2
		//For ^: HEIGHT: -D - BULLET_HEIGHT
		//For !^: HEIGHT: +D + OBJECT_WIDTH
		//For 0 vertically: HEIGHT: + OBJECT_HEIGHT/2 - BULLET_HEIGHT/2
		//WANTED DISTANCE HERE IS 2
	
		TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() + CYRER_WIDTH + CYRER_DISTANCE, m_position.getY() + CYRER_HEIGHT / 2,
			BULLET1_WIDTH, BULLET1_HEIGHT, "bullet1", 1, Vector2D(m_bulletSpeed, 0)); // ->, 0
		TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() - BULLET1_WIDTH - CYRER_DISTANCE, m_position.getY() + CYRER_HEIGHT / 2,
			BULLET1_WIDTH, BULLET1_HEIGHT, "bullet1", 1, Vector2D(-m_bulletSpeed, 0)); // <-, 0
		TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() + CYRER_WIDTH / 2, m_position.getY() + CYRER_WIDTH + CYRER_DISTANCE,
			BULLET1_WIDTH, BULLET1_HEIGHT, "bullet1", 1, Vector2D(0, m_bulletSpeed)); // 0, !^
		TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() + CYRER_WIDTH / 2, m_position.getY() - BULLET1_HEIGHT - CYRER_DISTANCE,
			BULLET1_WIDTH, BULLET1_HEIGHT, "bullet1", 1, Vector2D(0, -m_bulletSpeed)); // 0, ^
		TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() + CYRER_WIDTH + CYRER_DISTANCE, m_position.getY() - BULLET1_HEIGHT - CYRER_DISTANCE,
			BULLET1_WIDTH, BULLET1_HEIGHT, "bullet1", 1, Vector2D(m_bulletSpeed, -m_bulletSpeed)); // ->, ^
		TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() + CYRER_WIDTH + CYRER_DISTANCE, m_position.getY() + CYRER_WIDTH + CYRER_DISTANCE,
			BULLET1_WIDTH, BULLET1_HEIGHT, "bullet1", 1, Vector2D(m_bulletSpeed, m_bulletSpeed)); // ->, !^
		TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() - BULLET1_WIDTH - CYRER_DISTANCE, m_position.getY() - BULLET1_HEIGHT - CYRER_DISTANCE,
			BULLET1_WIDTH, BULLET1_HEIGHT, "bullet1", 1, Vector2D(-m_bulletSpeed, -m_bulletSpeed)); // <-, ^
		TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() - BULLET1_WIDTH - CYRER_DISTANCE, m_position.getY() + CYRER_WIDTH + CYRER_DISTANCE,
			BULLET1_WIDTH, BULLET1_HEIGHT, "bullet1", 1, Vector2D(-m_bulletSpeed, m_bulletSpeed)); // <-, !^
		
		m_recoilCounter = 0;
	}
	m_recoilCounter++;
}

void Cyrer::handleAnimation() {
	if (m_health == 0) {
		m_dying = true;
	}
	if (m_position.getX() + CYRER_WIDTH <= 0 || m_position.getY() <= 0 || m_position.getY() + CYRER_HEIGHT >= GAME_WIDTH) {
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

void Cyrer::doDyingAnimation() {
	GameObject::changeTexture(new ObjectParams("explosion", 0, 0, 42, 40, 9));
	GameObject::scroll(SCROLL_SPEED);
	m_currentFrame = int((SDL_GetTicks() / 100 % m_numFrames));
}

void Cyrer::collision() {
	TheSoundManager::Instance()->playSound("explosionEffect", 1);
	if (m_health != 0) {
		m_health--;
	}
}

void Cyrer::clean() {
	Enemy::clean();
}