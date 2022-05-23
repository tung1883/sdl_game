#pragma once

#include "Boss.h"
#include "Sound.h"
#include "Game.h"
#include "Bullet.h"

Boss::Boss(const ObjectParams* params)
	:Enemy(params)
{
	//Ensure the bullet speed is positive and speed is negative
	m_bulletSpeed = -10;
	m_speed = 1;
	m_velocity.setX(-m_speed);;
	m_health = 20;

	m_recoilCounter = 0;
	m_recoilSpeed = 30;

	m_modeCounter = 0;
	m_modeTime = 240;
	m_mode = true;
}

void Boss::draw() {
	Enemy::draw();
}

void Boss::update() {
	if (m_updating) {
		m_position.setX(m_position.getX() + m_velocity.getX());
		handleAnimation();
		if (!m_dying) {
			handleBullet();
		}
		m_currentFrame = int((SDL_GetTicks() / 100 % m_numFrames));
	}
	m_currentFrame = int((SDL_GetTicks() / 100 % m_numFrames));
}

void Boss::handleAnimation() {
	if (m_health == 0) {
		m_dying = true;
	}
	if (m_position.getX() + BOSS_WIDTH <= 0 || m_position.getY() <= 0 || m_position.getY() + BOSS_HEIGHT >= GAME_WIDTH) {
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

void Boss::handleBullet() {
	//2 types of bullet shooting 
	//
	//Boss sizes
	//230 183px
	//Empty: 8px - Gun_1: 22 - Empty: 2 - Gun_2: 22 - Head: 122 - Gun_3: 22 - Empty: 2 - Gun_4: 22 - Empty: 8px
	//
	//m_mode = true -> mode 1, = false -> mode 2
	//mode_1: shoot bullet 3 horizontally
	//mode_2: shoot bullet 1 diagnally

	if (m_modeCounter == m_modeTime) {
		m_mode = (m_mode == true) ? false : true;
		m_modeCounter = 0;
	}
	if (m_recoilCounter == m_recoilSpeed && m_mode == true) {
		//Symbols denoting direction of bullet: -> (RIGHT), <- (LEFT), ^ (UP), !^ (DOWN)
		//D stands for wanted distance (between bullet and object)
		//For ->: WIDTH: + OBJECT_WIDTH + D
		//For <-: WIDTH: -D - BULLET_WIDTH
		//For 0 horizontally: WIDTH: + OBJECT_WIDTH/2 + BULLET_WIDTH/2
		//For ^: HEIGHT: -D - BULLET_HEIGHT
		//For !^: HEIGHT: +D + OBJECT_WIDTH
		//For 0 vertically: HEIGHT: + OBJECT_HEIGHT/2 - BULLET_HEIGHT/2
		//WANTED DISTANCE HERE IS 2
		
		//Gun_1:
		TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() - BULLET3_WIDTH - BOSS_DISTANCE,
			m_position.getY() + BOSS_HEIGHT / 2 - BOSS_HEAD / 2 - BOSS_GUN - 2 - BOSS_GUN / 2, BULLET1_WIDTH, BULLET1_HEIGHT, "bullet1", 1, Vector2D(m_bulletSpeed, 0)); // <-, 0
		TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() - BULLET3_WIDTH - BOSS_DISTANCE,
			m_position.getY() + BOSS_HEIGHT / 2 - BOSS_HEAD / 2 - BOSS_GUN - 2 - BOSS_GUN / 2, BULLET1_WIDTH, BULLET1_HEIGHT, "bullet1", 1, Vector2D(m_bulletSpeed, m_bulletSpeed)); // <-, ^
		TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() - BULLET3_WIDTH - BOSS_DISTANCE,
			m_position.getY() + BOSS_HEIGHT / 2 - BOSS_HEAD / 2 - BOSS_GUN - 2 - BOSS_GUN / 2, BULLET1_WIDTH, BULLET1_HEIGHT, "bullet1", 1, Vector2D(m_bulletSpeed, m_bulletSpeed)); // <-, !^

		//Gun_2:
		TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() - BULLET3_WIDTH - BOSS_DISTANCE,
			m_position.getY() + BOSS_HEIGHT / 2 - BOSS_HEAD / 2 - BOSS_GUN / 2, BULLET1_WIDTH, BULLET1_HEIGHT, "bullet1", 1, Vector2D(m_bulletSpeed, 0)); // <-, 0
		TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() - BULLET3_WIDTH - BOSS_DISTANCE,
			m_position.getY() + BOSS_HEIGHT / 2 - BOSS_HEAD / 2 - BOSS_GUN / 2, BULLET1_WIDTH, BULLET1_HEIGHT, "bullet1", 1, Vector2D(m_bulletSpeed, m_bulletSpeed)); // <-, ^
		TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() - BULLET3_WIDTH - BOSS_DISTANCE,
			m_position.getY() + BOSS_HEIGHT / 2 - BOSS_HEAD / 2 - BOSS_GUN / 2, BULLET1_WIDTH, BULLET1_HEIGHT, "bullet1", 1, Vector2D(m_bulletSpeed, m_bulletSpeed)); // <-, !^

		//Gun_3:
		TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() - BULLET3_WIDTH - BOSS_DISTANCE,
			m_position.getY() + BOSS_HEIGHT / 2 + BOSS_HEAD / 2 + BOSS_GUN / 2, BULLET1_WIDTH, BULLET1_HEIGHT, "bullet1", 1, Vector2D(m_bulletSpeed, 0)); // <-, 0
		TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() - BULLET3_WIDTH - BOSS_DISTANCE,
			m_position.getY() + BOSS_HEIGHT / 2 + BOSS_HEAD / 2 + BOSS_GUN / 2, BULLET1_WIDTH, BULLET1_HEIGHT, "bullet1", 1, Vector2D(m_bulletSpeed, -m_bulletSpeed)); // <-, ^
		TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() - BULLET3_WIDTH - BOSS_DISTANCE,
			m_position.getY() + BOSS_HEIGHT / 2 + BOSS_HEAD / 2 + BOSS_GUN / 2, BULLET1_WIDTH, BULLET1_HEIGHT, "bullet1", 1, Vector2D(m_bulletSpeed, m_bulletSpeed)); // <-, !^

		//Gun_4:
		TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() - BULLET3_WIDTH - BOSS_DISTANCE,
			m_position.getY() + BOSS_HEIGHT / 2 + BOSS_HEAD / 2 + BOSS_GUN + 2 + BOSS_GUN / 2, BULLET1_WIDTH, BULLET1_HEIGHT, "bullet1", 1, Vector2D(m_bulletSpeed, 0)); // <-, 0
		TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() - BULLET3_WIDTH - BOSS_DISTANCE,
			m_position.getY() + BOSS_HEIGHT / 2 + BOSS_HEAD / 2 + BOSS_GUN + 2 + BOSS_GUN / 2, BULLET1_WIDTH, BULLET1_HEIGHT, "bullet1", 1, Vector2D(m_bulletSpeed, -m_bulletSpeed)); // <-, ^
		TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() - BULLET3_WIDTH - BOSS_DISTANCE,
			m_position.getY() + BOSS_HEIGHT / 2 + BOSS_HEAD / 2 + BOSS_GUN + 2 + BOSS_GUN / 2, BULLET1_WIDTH, BULLET1_HEIGHT, "bullet1", 1, Vector2D(m_bulletSpeed, m_bulletSpeed)); // <-, !^

		m_recoilCounter = 0;
	}

	if (m_recoilCounter == m_recoilSpeed && m_mode == false) {
		//Gun_1:
		TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() - BULLET3_WIDTH - BOSS_DISTANCE,
			m_position.getY() + BOSS_HEIGHT / 2 - BOSS_HEAD / 2 - BOSS_GUN - 2 - BOSS_GUN / 2, BULLET3_WIDTH, BULLET3_HEIGHT, "bullet3", 1, Vector2D(m_bulletSpeed, 0)); // <-, 0

		//Gun_2:
		TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() - BULLET3_WIDTH - BOSS_DISTANCE,
			m_position.getY() + BOSS_HEIGHT / 2 - BOSS_HEAD / 2 - BOSS_GUN / 2 + 20, BULLET3_WIDTH, BULLET3_HEIGHT, "bullet3", 1, Vector2D(m_bulletSpeed, 0)); // <-, 0

		//Gun_3:
		TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() - BULLET3_WIDTH - BOSS_DISTANCE,
			m_position.getY() + BOSS_HEIGHT / 2 + BOSS_HEAD / 2 + BOSS_GUN / 2 - 20, BULLET3_WIDTH, BULLET3_HEIGHT, "bullet3", 1, Vector2D(m_bulletSpeed, 0)); // <-, 0

		//Gun_4:
		TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() - BULLET3_WIDTH - BOSS_DISTANCE,
			m_position.getY() + BOSS_HEIGHT / 2 + BOSS_HEAD / 2 + BOSS_GUN + 2 + BOSS_GUN / 2, BULLET3_WIDTH, BULLET3_HEIGHT, "bullet3", 1, Vector2D(m_bulletSpeed, 0)); // <-, 0
		//Head:
		TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() - BULLET3_WIDTH - BOSS_DISTANCE,
			m_position.getY() + BOSS_HEIGHT / 2, BULLET3_WIDTH, BULLET3_HEIGHT, "bullet3", 1, Vector2D(m_bulletSpeed, 0)); // <-, 0

		m_recoilCounter = 0;
	}

	m_modeCounter++;
	m_recoilCounter++;

}
void Boss::doDyingAnimation() {
	GameObject::changeTexture(new ObjectParams("explosion", 0, 0, 42, 40, 9));
	GameObject::scroll(SCROLL_SPEED);
	m_currentFrame = int((SDL_GetTicks() / 100 % m_numFrames));
}

void Boss::collision() {
	TheSoundManager::Instance()->playSound("explosionEffect", 1);
	if (m_health != 0) {
		m_health--;
	}
	if (m_health == 0) {
		m_dead = true;
	}
}

void Boss::clean() {
	Enemy::clean();
}


