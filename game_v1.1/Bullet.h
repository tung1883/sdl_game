#pragma once

#include <vector>

#include "GameObject.h"
#include "ObjectParams.h"

const int BULLET1_WIDTH = 11;
const int BULLET1_HEIGHT = 11;
const int BULLET2_WIDTH = 16;
const int BULLET2_HEIGHT = 16;
const int BULLET3_WIDTH = 33;
const int BULLET3_HEIGHT = 33;

class PlayerBullet : public GameObject
{
public:
	PlayerBullet(const ObjectParams* params, Vector2D heading) : GameObject(params), m_heading(heading)
	{};

	virtual ~PlayerBullet() {};

	std::string getType() {
		return "Player Bullet";
	}

	virtual void draw() {
		GameObject::draw();
	}

	virtual void update() {
		m_currentFrame = int((SDL_GetTicks() / 100 % m_numFrames));

		m_velocity.setX(m_heading.getX());
		m_velocity.setY(m_heading.getY());

		GameObject::update();
	}

	virtual void collision() {

	}

	virtual void clean() {
		GameObject::clean();
	}

	bool getDead() {
		return m_dead;
	}

	void setDead(bool state) {
		m_dead = state;
	}

private:
	bool m_dead = false;
	Vector2D m_heading;
};

class EnemyBullet : public GameObject
{
public:
	EnemyBullet(const ObjectParams* params, Vector2D heading) : GameObject(params), m_heading(heading)
	{};

	virtual ~EnemyBullet() {};

	std::string getType() {
		return "Enemy Bullet";
	}

	virtual void draw() {
		GameObject::draw();
	}

	virtual void update() {
		m_currentFrame = int((SDL_GetTicks() / 100 % m_numFrames));

		m_velocity.setX(m_heading.getX());
		m_velocity.setY(m_heading.getY());

		GameObject::update();
	}

	virtual void collision() {

	}

	virtual void clean() {
		GameObject::clean();
	}

	bool getDead() {
		return m_dead;
	}

	void setDead(bool state) {
		m_dead = state;
	}

private:
	bool m_dead = false;

	Vector2D m_heading;
};

class BulletHandler
{
public:
	static BulletHandler* Instance()
	{
		if (bulletInstance == NULL) {
			bulletInstance = new BulletHandler();
		}
		return bulletInstance;
	}

	void addPlayerBullet(int x, int y, int width, int height,
		std::string textureID, int numFrames, Vector2D heading);

	void addEnemyBullet(int x, int y, int width, int height,
		std::string textureID, int numFrames, Vector2D heading);

	void drawBullets();
	void updateBullets();
	void cleanBullets();

	//Getters
	std::vector<PlayerBullet*> getPlayerBullets() {
		return m_playerBullets;
	}
	std::vector<EnemyBullet*> getEnemyBullets() {
		return m_enemyBullets;
	}

private:
	BulletHandler() {};
	~BulletHandler() {};

	static BulletHandler* bulletInstance;
	std::vector<PlayerBullet*> m_playerBullets;
	std::vector<EnemyBullet*> m_enemyBullets;
};

typedef BulletHandler TheBulletHandler;