#pragma once

#include <string>

class GameState
{
public:
	virtual void update() = NULL;
	virtual void render() = NULL;

	virtual bool onEnter() = NULL;
	virtual bool onExit() = NULL;

	virtual std::string getStateID() const = NULL;
};