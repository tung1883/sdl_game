#pragma once

#include <iostream>
#include <vector>

#include "GameState.h"
#include "GameObject.h"

class GameOverState : public GameState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const
	{
		return playID;
	}
private:
	static const std::string playID;

	static void s_gameOverToMain();
	static void s_restartPlay();

	std::vector<GameObject*> m_gameObjects;
};