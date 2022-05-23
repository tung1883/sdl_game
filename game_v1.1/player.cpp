#pragma once

#include "Game.h"
#include "Player.h"
#include "InputHandler.h"
#include "Sound.h"
#include "Bullet.h"

Player::Player(const ObjectParams* params)
	:Shooter(params) 
{	
	m_recoilCounter = 10;
	m_recoilSpeed = 10;

	m_invulnerable = false;
	m_invulnerableDrawing = false;
	m_invulnerableTime = 70;
	m_invulnerableDrawTime = 60;
	m_invulnerableCounter = 0;

	m_dyingCounter = 0;
	m_dyingTime = 120;
	m_health = 3;
	m_speed = 5;

	m_winningDrawing = false;
}

void Player::draw() {
	TheTextureManager::Instance()->drawFrame(m_textureID, m_position.getX(), m_position.getY(), m_width, m_height,
		m_currentFrame, m_currentRow, TheGame::Instance()->getRenderer(), m_angle, m_alpha, SDL_FLIP_HORIZONTAL);
}

void Player::handleInput() {
	if (m_invulnerableDrawing || m_dying || m_dead || m_winningDrawing) {
		return;
	}

	//Player follows the mouse
	//Vector2D* target = TheInputHandler::Instance()->getMousePosition();
	//m_velocity = *target - m_position;
	//m_velocity /= m_speed;

	//if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_S)) {
	//	m_velocity.setY(1);
	//};
	//if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_W)) {
	//	m_velocity.setY(-1);
	//};
	//if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_A)) {
	//	m_velocity.setX(-1);
	//};
	//if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D)) {
	//	m_velocity.setX(1);
	//};
	
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)) {
		m_velocity.setY(m_speed);
	};
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)) {
		m_velocity.setY(-m_speed);
	};
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
		m_velocity.setX(-m_speed);
	};
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
		m_velocity.setX(m_speed);
	};
	if (m_position.getX() <= 0 && m_velocity.getX() <= 0) {
		m_velocity.setX(0);
	}
	if (m_position.getX() >= GAME_WIDTH - PLAYER_WIDTH - 2 && m_velocity.getX() >= 0) {
		m_velocity.setX(0);
	}
	if (m_position.getY() <= 0 && m_velocity.getY() <= 0) {
		m_velocity.setY(0);
	}
	
	//Shooting the bullets if Z button is pressed
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_Z)) {
		if (m_recoilCounter == m_recoilSpeed) {
			TheBulletHandler::Instance()->addPlayerBullet(m_position.getX() + 128 + 3, m_position.getY() + 27,
				11, 11, "bullet1", 1, Vector2D(10, 0));
			TheSoundManager::Instance()->playSound("shootEffect", 1);
			m_recoilCounter = 0;
		}
		m_recoilCounter++;
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_P)) {
		std::cout << "YOU ARE CHEATING !" << std::endl;
		m_health = 100;
	}
}

void Player::update() {
	//logic if the level is completed
	if (m_winningDrawing) {
		m_velocity.setX(10);
		m_velocity.setY(0);
		m_position += m_velocity;
		return;
	}
	//If shooter is not dying, update it normally
	m_velocity.setX(0);
	m_velocity.setY(0);

	handleInput();
	Shooter::update();
	handleAnimation();
}

void Player::clean() {
	Shooter::clean();
}

//RESURRECT FUNCTION
//Decrease total lives by one and reset to the inital position
void Player::resurrect() {
	m_position.setX(50);
	m_position.setY(500);
	GameObject::changeTexture(new ObjectParams("resurrect", 0, 0, 102, 100, 8, 1), 10);
	m_dying = false;
}

void Player::handleAnimation() {
	if (m_invulnerable) {
		if (m_invulnerableCounter == m_invulnerableTime) {
			m_invulnerable = false;
			m_invulnerableCounter = 0;
		}
		else {
			if (m_invulnerableCounter >= m_invulnerableDrawTime) {
				m_invulnerableDrawing = false;
				GameObject::changeTexture(new ObjectParams("helicopter", 0, 0, 128, 55, 5));
			}
			else {
				resurrect();
			}
		}
		m_invulnerableCounter++;
	}

	if (m_dying || m_dead) {
		m_dyingCounter++;
		if (m_dyingCounter <= m_dyingTime) {
			GameObject::changeTexture(new ObjectParams("explosion", 0, 0, 42, 40, 9, 1));
			GameObject::scroll(SCROLL_SPEED);
			m_currentFrame = int((SDL_GetTicks() / 100 % m_numFrames));
		}
		else {
			m_dead = true;
			m_dying = false;
		}
	}

	if (!m_dead) {
		if (m_velocity.getY() < 0) {
			m_angle = -7.0;
		}
		else if (m_velocity.getY() > 0) {
			m_angle = 7.0;
		}
		else {
			m_angle = 0.0;
		}
	}

	m_currentFrame = int((SDL_GetTicks() / 100) % m_numFrames);
}

void Player::collision() {
	if (m_invulnerable) {
		return;
	}

	checkCollision = true;

	if (m_health == 0) {
		//TheSoundManager::Instance()->playSound("explosionEffect", 1);
		m_dying = true;
	}
	else {
		TheSoundManager::Instance()->playSound("explosionEffect", 1);
		m_invulnerableDrawing = true;
		m_invulnerable = true;
		m_health--;
	}
}
