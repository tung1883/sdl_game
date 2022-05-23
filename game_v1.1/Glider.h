#pragma once

#include "Enemy.h"

const int GLIDER_WIDTH = 38;
const int GLIDER_HEIGHT = 36;
const int GLIDER_DISTANCE = 2; //distance between object and bullet
class Glider: public Enemy
{
public:
	Glider(const ObjectParams* params);

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
