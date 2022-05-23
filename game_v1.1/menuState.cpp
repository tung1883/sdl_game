#pragma once

#include <iostream>
#include "CollisionManager.h"
#include "Sound.h"
#include "MenuState.h"
#include "PlayState.h"
#include "AnimatedGraphic.h"

const std::string MenuState::menuID = "MENU";

void MenuState::update() {
	for (auto i : m_gameObjects) {
		i->update();
	}
}

void MenuState::render() {
	for (auto i : m_gameObjects) {
		i->draw();
	}
}

bool MenuState::onEnter() {
	if (!TheSoundManager::Instance()->load("res/DST_Announce.ogg", "menuMusic", SOUND_MUSIC)) {
		return false;
	}

	if (!TheTextureManager::Instance()->loadTexture("res/background.png", "menuBackground", TheGame::Instance()->getRenderer())) {
		std::cout << "Can not load Exit button" << std::endl;
		return false;
	}

	if (!TheTextureManager::Instance()->loadTexture("res/button.png", "playButton", TheGame::Instance()->getRenderer())) {
		std::cout << "Can not load Play button" << std::endl;
		return false;
	}
	if (!TheTextureManager::Instance()->loadTexture("res/exit.png", "exitButton", TheGame::Instance()->getRenderer())) {
		std::cout << "Can not load Exit button" << std::endl;
		return false;
	}

	TheSoundManager::Instance()->playMusic("menuMusic", 1);

	GameObject* menuBackground = new AnimatedGraphic(new ObjectParams("menuBackground", 0, 0, 1280, 720, 1), 1);
	GameObject* playButton = new MenuButton(new ObjectParams("playButton", 440, 210, 400, 100, 3), s_menuToPlay);
	GameObject* exitButton = new MenuButton(new ObjectParams("exitButton", 440, 410, 400, 100, 3), s_exitFromMenu);
	
	m_gameObjects.push_back(menuBackground);
	m_gameObjects.push_back(playButton);
	m_gameObjects.push_back(exitButton);

	std::cout << "Entering menu state" << std::endl;
	return true;
}

bool MenuState::onExit() {
	for (auto i : m_gameObjects) {
		i->clean();
	}
	m_gameObjects.clear();

	TheSoundManager::Instance()->fadeClear(300);

	TheTextureManager::Instance()->clearTextureFromMap("playButton");
	TheTextureManager::Instance()->clearTextureFromMap("exitButton");

	std::cout << "Exiting menu state" << std::endl;
	return true;
}

//Call back functions for menu state
void MenuState::s_menuToPlay() {
	TheGame::Instance()->getStateMachine()->changeState(new PlayState());
};
void MenuState::s_exitFromMenu() {
	TheGame::Instance()->setRunning(false);
};