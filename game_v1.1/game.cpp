#pragma once

#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>

#include "Game.h"
#include "Texture.h"
#include "GameObject.h"
#include "InputHandler.h"
#include "StateMachine.h"
#include "GameState.h"
#include "MenuState.h"
#include "PlayState.h"
#include "PauseState.h"


Game* Game::p_instance = NULL;

bool Game::init(const char* title, int xPosition, int yPosition, int windowWidth, int windowHeight, int windowFlags)
{
	bool success = true;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Errors when initializing SDL! SDL Error: " << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		if (IMG_Init(IMG_INIT_PNG) < 0)
		{
			std::cout << "Erros when initializing PNG image! SDL Error: " << SDL_GetError() << std::endl;
			success = false;
		}
		else {
			p_window = SDL_CreateWindow(title, xPosition, yPosition, windowWidth, windowHeight, windowFlags);
			if (p_window == nullptr)
			{
				std::cout << "Erros when creating window! SDL Error: " << SDL_GetError() << std::endl;
				success = false;
			}
			else {
				p_renderer = SDL_CreateRenderer(p_window, -1, 0);
				if (p_renderer == nullptr)
				{
					std::cout << "Erros when creating renderer! SDL Error: " << SDL_GetError() << std::endl;
					success = false;
				}
			}
		}
	}
	
	if (success == true) {
		running = true;
	}

	m_pStateMachine = new StateMachine();
	m_pStateMachine->changeState(new MenuState());

	return success;
}

void Game::handleEvents()
{
	TheInputHandler::Instance()->update();

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
	{
		m_pStateMachine->changeState(new PlayState());
	}
	  
}

void Game::render()
{
	SDL_RenderClear(p_renderer);
	for (auto object : objectArray) {
		object->draw();
	}
	m_pStateMachine->render();
	SDL_RenderPresent(p_renderer);
	
}

void Game::update()
{
	for (auto object : objectArray) {
		object->update();
	}
	m_pStateMachine->update();
}

void Game::clean()
{
	std::cout << "Cleaning Game" << std::endl;

	TheInputHandler::Instance()->clean();

	SDL_DestroyWindow(p_window);
	SDL_DestroyRenderer(p_renderer);

	IMG_Quit();
	SDL_Quit();
}
