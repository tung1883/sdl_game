#pragma once

#include "GameObject.h"
#include "InputHandler.h"
#include "MenuButton.h"
#include "Math.h"

MenuButton::MenuButton(const ObjectParams* params, void (*callback) ())
	:GameObject(params)
{
	m_callback = callback;
	m_currentFrame = MOUSE_OUT;
}

void MenuButton::draw()
{
	GameObject::draw();
}

void MenuButton::update()
{
	Vector2D* p_MousePos = TheInputHandler::Instance()->getMousePosition();
	if (p_MousePos->getX() <= m_position.getX() + m_width
		&& p_MousePos->getX() >= m_position.getX()
		&& p_MousePos->getY() <= m_position.getY() + m_height
		&& p_MousePos->getY() >= m_position.getY())
	{
		m_currentFrame = MOUSE_OVER;
		if (TheInputHandler::Instance()->getMouseButtonState(LEFT) && m_buttonReleased) {
			m_currentFrame = CLICKED;
			std::cout << "Mouse click! Button Name:" << " " << GameObject::m_textureID << std::endl;
			m_callback();
			m_buttonReleased = false;
		}
	}
	else {
		m_buttonReleased = true;
		m_currentFrame = MOUSE_OUT;
	}
}

void MenuButton::clean()
{
	GameObject::clean();
}