#pragma once

#include "GameObject.h"
#include "ObjectParams.h"
#include "InputHandler.h"

class AnimatedGraphic : public GameObject
{
public:
	AnimatedGraphic(const ObjectParams* params, int animateSpeed);

	virtual void draw();
	virtual void update();
	virtual void clean();

private:
	int m_animateSpeed;
};
