#pragma once

#include "Enemy.h"

const int SLINGER_WIDTH = 38;
const int SLINGER_HEIGHT = 34;
const int SLINGER_DISTANCE = 2; //distance between object and bullet

class Slinger : public Enemy
{
public:
	Slinger(const ObjectParams* params);

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
};
