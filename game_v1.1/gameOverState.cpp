#pragma once

#include <iostream>
#include <vector>

#include "Game.h"
#include "GameOverState.h"
#include "GameState.h"
#include "MenuState.h"
#include "PlayState.h"
#include "GameObject.h"
#include "AnimatedGraphic.h"
#include "Sound.h"

const std::string GameOverState::playID = "GAMEOVER";

void GameOverState::s_gameOverToMain () {
	TheGame::Instance()->getStateMachine()->changeState(new MenuState());
}

void GameOverState::s_restartPlay() {
	TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}

void GameOverState::update()
{
	for (auto i : m_gameObjects) {
		i->update();
	}
}

void GameOverState::render()
{
	for (auto i : m_gameObjects) {
		i->draw();
	}
}

bool GameOverState::onEnter()
{
	if (!TheSoundManager::Instance()->load("res/DST_ElectroRock.ogg", "mainMusic", SOUND_MUSIC)) {
		return false;
	}

	TheSoundManager::Instance()->playMusic("mainMusic", 10);

	if (!TheTextureManager::Instance()->loadTexture("res/gameover.png", "gameoverText", TheGame::Instance()->getRenderer())) {
		return false;
	}

	if (!TheTextureManager::Instance()->loadTexture("res/main.png", "mainButton", TheGame::Instance()->getRenderer())) {
		return false;
	}

	if (!TheTextureManager::Instance()->loadTexture("res/restart.png", "restartButton", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->loadTexture("res/background.png", "background", TheGame::Instance()->getRenderer())) {
		std::cout << "Can not load Exit button" << std::endl;
		return false;
	}


	GameObject* overBackground = new AnimatedGraphic(new ObjectParams("background", 0, 0, 1280, 720, 1), 1);
	GameObject* gameoverText = new AnimatedGraphic(new ObjectParams("gameoverText", 540, 100, 190, 30, 2, 1), 2);
	GameObject* mainButton = new MenuButton(new ObjectParams("mainButton", 540, 200, 200, 80, 3), s_gameOverToMain);
	GameObject* restartButton = new MenuButton(new ObjectParams("restartButton", 540, 400, 200, 80, 3), s_restartPlay);
	
	m_gameObjects.push_back(overBackground);
	m_gameObjects.push_back(gameoverText);
	m_gameObjects.push_back(mainButton);
	m_gameObjects.push_back(restartButton);

	std::cout << "Entering Gameover State" << std::endl;
	return true;
}

bool GameOverState::onExit()
{
	for (auto i : m_gameObjects) {
		i->clean();
	}
	m_gameObjects.clear();

	TheSoundManager::Instance()->clear();

	TheTextureManager::Instance()->clearTextureFromMap("mainButton");
	TheTextureManager::Instance()->clearTextureFromMap("restartButton");
	TheTextureManager::Instance()->clearTextureFromMap("gameoverText");

	TheInputHandler::Instance()->reset();
	

	std::cout << "Exiting Gameover State" << std::endl;
	return true;
}