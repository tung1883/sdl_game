#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include "GameObject.h"
#include "Texture.h"
#include "ObjectParams.h"
#include "Game.h"

//Loading the object
//Default value for: angle = 0.0, alpha = 255
GameObject::GameObject(const ObjectParams* params)
{
	m_textureID = params->getID();
	m_currentFrame = 1;
	m_currentRow = 1;
	m_numFrames = params->getFrames();
	m_numRows = params->getRows();

	m_position = Vector2D(params->getX(), params->getY());
	m_velocity = Vector2D(0, 0);
	m_acceleration = Vector2D(0, 0);

	m_width = params->getWidth();
	m_height = params->getHeight();

	m_updating = true;
	m_dead = false;
	m_dying = false;

	m_angle = 0.0;
	m_alpha = 255;
}

//Drawing the object
//If velocity.x < 0 draw normally, else flip it horizontally
void GameObject::draw() {
	TheTextureManager::Instance()->drawFrame(m_textureID, m_position.getX(), m_position.getY(), m_width, m_height,
		m_currentFrame, m_currentRow, TheGame::Instance()->getRenderer(), m_angle, m_alpha);
}

//Update the position and velocity 
void GameObject::update(){
	m_position += m_velocity;
	m_velocity += m_acceleration;
}

//Clean texture of the object
void GameObject::clean() {
	TheTextureManager::Instance()->clearTextureFromMap(m_textureID);
}

void GameObject::changeTexture(const ObjectParams* params, double angle, int alpha) {
	m_textureID = params->getID();
	m_currentFrame = 1;
	m_currentRow = 1;
	m_numFrames = params->getFrames();
	m_numRows = params->getRows();

	m_width = params->getWidth();
	m_height = params->getHeight();

	m_angle = angle;
	m_alpha = alpha;
}
