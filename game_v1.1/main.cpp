#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Game.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char* args[])
{
	Uint32 frameStart, frameTime;

	std::cout << "Game initialization attempt..." << std::endl;
	if (TheGame::Instance()->init("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		TheGame::Instance()->getGameWidth(), TheGame::Instance()->getGameHeight(), SDL_WINDOW_SHOWN)) {
		std::cout << "Game initialization success!" << std::endl;
		while (TheGame::Instance()->isRunning()) {
			frameStart = SDL_GetTicks();

			TheGame::Instance()->handleEvents();
			TheGame::Instance()->update();
			TheGame::Instance()->render();

			frameTime = SDL_GetTicks() - frameStart;

			if (frameTime < DELAY_TIME) {
				SDL_Delay(int(DELAY_TIME - frameTime));
			}
		}
	}
	else {
		std::cout << "Game initialization failed! SDL Error: " << SDL_GetError() << std::endl;
		return -1;
	}
	
	std::cout << "Game closing..." << std::endl;
	TheGame::Instance()->clean();
	return 0;
}