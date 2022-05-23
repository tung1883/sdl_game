#pragma once

#include <iostream>
#include <vector>

#include "AnimatedGraphic.h"
#include "Game.h"
#include "PauseState.h"
#include "MenuState.h"
#include "PlayState.h"
#include "Sound.h"
#include "Texture.h"

const std::string PauseState::menuID = "PAUSE";

void PauseState::update() {
	for (auto i : m_gameObjects) {
		i->update();
	}
}

void PauseState::render() {
	for (auto i : m_gameObjects) {
		i->draw();
	}
}

bool PauseState::onEnter() {
	if (!TheSoundManager::Instance()->load("res/DST_ElectroRock.ogg", "mainMusic", SOUND_MUSIC)) {
		return false;
	}

	if (!TheTextureManager::Instance()->loadTexture("res/main.png", "mainButton", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->loadTexture("res/resume.png", "resumeButton", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->loadTexture("res/background.png", "background", TheGame::Instance()->getRenderer())) {
		std::cout << "Can not load Exit button" << std::endl;
		return false;
	}

	TheSoundManager::Instance()->playMusic("mainMusic", 10);

	GameObject* pauseBackground = new AnimatedGraphic(new ObjectParams("background", 0, 0, 1280, 720, 1), 1);
	GameObject* mainButton = new MenuButton(new ObjectParams("mainButton", 540, 200, 200, 80, 3), s_pauseToMain);
	GameObject* resumeButton = new MenuButton(new ObjectParams("resumeButton", 540, 400, 200, 80, 3), s_resumePlay);

	m_gameObjects.push_back(pauseBackground);
	m_gameObjects.push_back(mainButton);
	m_gameObjects.push_back(resumeButton);

	std::cout << "Entering pause state" << std::endl;
	return true;
}

bool PauseState::onExit() {
	for (auto i : m_gameObjects) {
		i->clean();
	}
	m_gameObjects.clear();

	TheSoundManager::Instance()->clear();

	TheTextureManager::Instance()->clearTextureFromMap("mainButton");
	TheTextureManager::Instance()->clearTextureFromMap("resumeButton");

	TheInputHandler::Instance()->reset();

	std::cout << "Exiting pause state" << std::endl;
	return true;
}

//Call back functions for menu state
void PauseState::s_pauseToMain() {
	TheGame::Instance()->getStateMachine()->changeState(new MenuState());
};

void PauseState::s_resumePlay() {
	TheGame::Instance()->getStateMachine()->popState();
};