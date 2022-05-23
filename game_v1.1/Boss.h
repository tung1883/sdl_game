#pragma once

#include "Enemy.h"

const int BOSS_WIDTH = 183;
const int BOSS_HEIGHT = 230;
const int BOSS_DISTANCE = 2; //distance between object and bullet
const int BOSS_HEAD = 122;
const int BOSS_GUN = 22;

class Boss : public Enemy
{
public:
	Boss(const ObjectParams* params);

	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void collision();

private:
	void handleAnimation();
	void doDyingAnimation();
	void handleBullet();

	int m_speed;
	int m_health;

	int m_bulletSpeed;
	bool m_mode; //to change between different shooting modes
	int m_modeCounter; 
	int m_modeTime; //time in one mode
};
