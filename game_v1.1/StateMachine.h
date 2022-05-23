#pragma once

#include <vector>

#include "GameState.h"

class StateMachine
{
public:
	void pushState(GameState* pState);
	void changeState(GameState* pState);
	void popState();

	void update();
	void render();
private:
	std::vector<GameState*> m_states;
};
