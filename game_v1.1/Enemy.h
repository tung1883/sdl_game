#pragma once

#include "Shooter.h"
#include "InputHandler.h"
#include "Bullet.h"
class Enemy : public Shooter
{
public:
	Enemy(const ObjectParams* params);

	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void collision();

	std::string type() { return "Enemy"; };

	int getHealth() {
		return m_health;
	}

private:
	virtual void handleAnimation();
	virtual void doDyingAnimation();
	virtual void handleBullet();

	int m_health;
};
