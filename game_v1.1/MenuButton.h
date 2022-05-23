#pragma once

#include "GameObject.h"

class MenuButton: public GameObject
{
public:
	MenuButton(const ObjectParams* params, void (*callback) ());

	virtual void draw();
	virtual void update();
	virtual void clean();
private:
	enum buttonState
	{
		MOUSE_OUT = 0,
		MOUSE_OVER = 1,
		CLICKED = 2
	};

	void (*m_callback)();
	bool m_buttonReleased;
};