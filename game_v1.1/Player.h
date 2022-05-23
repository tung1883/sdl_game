#pragma once

#include "Shooter.h"
#include "InputHandler.h"

const int PLAYER_HEIGHT = 55;
const int PLAYER_WIDTH = 128;
const int PLAYER_NORMAL_SPEED = 30;

class Player : public Shooter 
{
public:
	Player(const ObjectParams* params);
	
	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void collision();

	//getters
	int getHealth() {
		return m_health;
	}
	bool getWinningDrawing() {
		return m_winningDrawing;
	}
	bool getCollision() {
		return checkCollision;
	};
	
	//setters
	void setWinningDrawing(bool winningDrawing) {
		m_winningDrawing = winningDrawing;
	}
	void setCollision(bool collision) {
		checkCollision = collision;
	};

private:
	void resurrect();
	
	void handleInput();
	void handleAnimation();

	bool m_invulnerable;
	bool m_invulnerableDrawing;
	int m_invulnerableTime;
	int m_invulnerableDrawTime;
	int m_invulnerableCounter;

	int m_dyingCounter;
	int m_dyingTime;
	int m_health;
	int m_speed;

	bool checkCollision;

	bool m_winningDrawing;
};
