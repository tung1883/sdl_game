#pragma once

#include <iostream>
#include <vector>
#include <SDL.h>

#include "Math.h"

enum mouseButton
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2,
};

class InputHandler
{
public:
	static InputHandler* Instance() {
		if (s_pInstance == NULL) {
			s_pInstance = new InputHandler();
			return s_pInstance;
		}
		return s_pInstance;
	}

	void update();
	void clean();

	//Mouse Function
	bool getMouseButtonState(int buttonNumber)
	{
		return m_mouseButtonStates[buttonNumber];
	}
	Vector2D* getMousePosition() {
		return m_mousePosition;
	}

	//Keyboard Function
	bool isKeyDown(SDL_Scancode key);
	void reset();

private:
	InputHandler();
	~InputHandler() {};

	//Joystick
	std::vector<SDL_Joystick*> m_joysticks;
	bool m_bJoystickInitialised;
	std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;

	//Mouse
	std::vector<bool> m_mouseButtonStates;
	Vector2D* m_mousePosition;

	//Keyboard
	const Uint8* m_keystate;
	static InputHandler* s_pInstance;
};

typedef InputHandler TheInputHandler;