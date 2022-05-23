#pragma once

#include "GameObject.h"
#include "ObjectParams.h"

class PlayerBullet : public GameObject
{
public:
	PlayerBullet(const ObjectParams* params, Vector2D heading);

	virtual void draw();
	virtual void update();
	virtual void clean();

private:
	Vector2D m_heading;
};
