#ifndef __Game__
#define __Game__

#pragma once
#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>

#include "StateMachine.h"
#include "Texture.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

const int SCROLL_SPEED = 3;
const int GAME_WIDTH = 1280;
const int GAME_HEIGHT = 640;

class Game
{
public:
	static Game* Instance() {
		if (p_instance == NULL) {
			p_instance = new Game();
		}
		return p_instance;
	}

	bool init(const char* title, int xPosition, int yPosition, int windowWidth, int windowHeight, int windowFlags);
	void render();
	void handleEvents();
	void update();
	void clean();

	bool isRunning() {
		return running;
	}
	SDL_Renderer* getRenderer() const { return p_renderer; };
	StateMachine* getStateMachine() {
		return m_pStateMachine;
	}
	int getGameWidth() {
		return gameWidth;
	}
	int getGameHeight() {
		return gameHeight;
	}
	int getScrollSpeed() {
		return scrollSpeed;
	}
	
	void setRunning(bool run) {
		running = run;
	}

private:
	const int gameWidth = GAME_WIDTH;
	const int gameHeight = GAME_HEIGHT;

	static Game* p_instance;

	Game() {};
	~Game() {};

	StateMachine* m_pStateMachine;

	bool running;

	SDL_Window* p_window;
	SDL_Renderer* p_renderer;

	int scrollSpeed;

	std::vector<GameObject*> objectArray;
};

typedef Game TheGame;

#endif // ! __Game__


