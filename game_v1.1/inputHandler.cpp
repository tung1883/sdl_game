#pragma once

#include <SDL.h>
#include <iostream>
#include <vector>

#include "InputHandler.h"
#include "Game.h"

InputHandler* InputHandler::s_pInstance = NULL;

InputHandler::InputHandler() {
	for (int i = 0; i < 3; i++) {
		m_mouseButtonStates.push_back(false);
	}
	m_mousePosition = new Vector2D( 0, 0);
}

//KEYBOARD FUNCTIONS
bool InputHandler::isKeyDown(SDL_Scancode key)
{
	if (m_keystate != 0)
	{
		if (m_keystate[key] == 1) {
			return true;
		}
		else return false;
	}
	return false;
}

void InputHandler::reset()
{
	for (auto i : m_mouseButtonStates) {
		i = false;
	}
};

//UPDATE FUNCTION
void InputHandler::update() {
	m_keystate = SDL_GetKeyboardState(0);
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			TheGame::Instance()->setRunning(false);
		}

		if (event.type == SDL_MOUSEBUTTONDOWN) {
			switch(event.button.button) {
			case SDL_BUTTON_LEFT:
				m_mouseButtonStates[LEFT] = true;
			case SDL_BUTTON_MIDDLE:
				m_mouseButtonStates[MIDDLE] = true;
			case SDL_BUTTON_RIGHT:
				m_mouseButtonStates[RIGHT] = true;
			}
		}

		if (event.type == SDL_MOUSEBUTTONUP) {
			switch (event.button.button) {
			case SDL_BUTTON_LEFT:
				m_mouseButtonStates[LEFT] = false;
			case SDL_BUTTON_MIDDLE:
				m_mouseButtonStates[MIDDLE] = false;
			case SDL_BUTTON_RIGHT:
				m_mouseButtonStates[RIGHT] = false;
			}
		}

		if (event.type == SDL_MOUSEMOTION) {
			m_mousePosition->setX(event.motion.x);
			m_mousePosition->setY(event.motion.y);
		}
	}
};

void InputHandler::clean() {
	for (auto i : m_joysticks) {
		SDL_JoystickClose(i);
	}
};