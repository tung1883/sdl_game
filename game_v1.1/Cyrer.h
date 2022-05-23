#pragma once

#include "Enemy.h"

const int CYRER_WIDTH = 35;
const int CYRER_HEIGHT = 35;
const int CYRER_DISTANCE = 2; //distance between object and bullet
class Cyrer : public Enemy
{
public:
	Cyrer(const ObjectParams* params);

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
