#pragma once

#include "GameObject.h"
#include "ObjectParams.h"
#include "InputHandler.h"

class Heart : public GameObject
{
public:
	Heart(const ObjectParams* params);

	virtual void draw();
	virtual void update();
	virtual void clean();

};
