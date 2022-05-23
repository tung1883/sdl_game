#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include "ObjectParams.h"
#include "Math.h"

class GameObject
{
public:
	GameObject(const ObjectParams* params);

	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void collision() {};

	//scroll along with tile map
	void scroll(float scrollSpeed) {
		m_position.setX(m_position.getX() - scrollSpeed);
	}

	
	virtual void changeTexture(const ObjectParams* params, double angle = 0.0, int alpha = 255);

	bool updating() { return m_updating; }
	bool dead() { return m_dead; }
	bool dying() { return m_dying; } //is the object doing the death animation
	void setUpdating(bool updating) { m_updating = updating; } //whether object need to update or not

	virtual std::string type() { return "Game Object"; };

	//getters
	virtual std::string getID() {
		return m_textureID;
	}
	virtual Vector2D getPosition() {
		return m_position;
	}
	virtual int getWidth() {
		return m_width;
	}
	virtual int getHeight() {
		return m_height;
	}
	virtual double getAngle() {
		return m_angle;
	}
	virtual int getAlpha() {
		return m_alpha;
	}
	virtual Vector2D getVelocity() {
		return m_velocity;
	}
	virtual bool getDead() {
		return m_dead;
	}

	virtual void setVel(int x, int y) {
		m_velocity = Vector2D(x, y);
	}

protected:
	std::string m_textureID;

	int m_currentFrame;
	int m_currentRow;
	int m_numFrames;
	int m_numRows;

	int m_width;
	int m_height;

	double m_angle;
	int m_alpha;

	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_acceleration;

	bool m_updating;
	bool m_dead;
	bool m_dying;
};