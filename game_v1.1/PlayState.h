#pragma once

#include <iostream>
#include <vector>

#include "Game.h"
#include "Collision.h"
#include "Texture.h"
#include "Sound.h"
#include "MapParser.h"
#include "MenuState.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "ObjectParams.h"
#include "GameObject.h"

class PlayState : public GameState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const 
	{
		return playID;
	}

	//void checkPlayer_EnemyBulletCollision(Player* pPlayer);
	//void checkPlayer_EnemyCollision(Player* pPlayer, const std::vector<GameObject*>& objects);
	//void checkEnemy_PlayerBulletCollision(const std::vector<GameObject*>& objects);
	//void checkPlayer_TileCollision(Player* pPlayer, const std::vector<TileLayer*>& collisionLayers);
	//void checkBullet_TileCollision(const std::vector<TileLayer*>& collisionLayers);

private:
	static const std::string playID;
	Player* pPlayer;
	std::vector<GameObject*> m_gameObjects;

	bool m_winningAnimation = false; //Check to start drawing winnig animation
	bool m_winning = false; //Check if the level is completed (will be set to true after doing the animation)
};