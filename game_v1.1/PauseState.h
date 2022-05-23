#pragma once

#include <vector>

#include "Game.h"
#include "Texture.h"
#include "GameState.h"
#include "MenuButton.h"
#include "ObjectParams.h"

class PauseState : public GameState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const
	{
		return menuID;
	}
private:
	static const std::string menuID;

	//call back functions 
	static void s_pauseToMain();
	static void s_resumePlay();

	std::vector<GameObject*> m_gameObjects;

};