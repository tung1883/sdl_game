#pragma once

#include <vector>

#include "Game.h"
#include "Texture.h"
#include "GameState.h"
#include "MenuButton.h"
#include "ObjectParams.h"

class MenuState : public GameState
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
	
	//call back functions for menu items
	static void s_menuToPlay();
	static void s_exitFromMenu();

	std::vector<GameObject*> m_gameObjects;

};