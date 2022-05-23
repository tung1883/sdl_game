#pragma once

#include "Bullet.h"
#include "Game.h"
#include "Texture.h"

BulletHandler* BulletHandler::bulletInstance = NULL;

void BulletHandler::addPlayerBullet(int x, int y, int width, int height,
	std::string textureID, int numFrames, Vector2D heading)
{
	PlayerBullet* playerBullet = new PlayerBullet(new ObjectParams(textureID, x, y, width, height, numFrames), heading);
	m_playerBullets.push_back(playerBullet);
	
}

void BulletHandler::addEnemyBullet(int x, int y, int width, int height,
	std::string textureID, int numFrames, Vector2D heading)
{
	EnemyBullet* enemyBullet = new EnemyBullet(new ObjectParams(textureID, x, y, width, height, numFrames), heading);
	m_enemyBullets.push_back(enemyBullet);
}

void BulletHandler::updateBullets()
{
	for (std::vector<EnemyBullet*>::iterator i = m_enemyBullets.begin(); i != m_enemyBullets.end();) {
		if ((*i)->getPosition().getX() < 0 || (*i)->getPosition().getX() > TheGame::Instance()->getGameWidth() 
			|| (*i)->getPosition().getY() < 0 || (*i)->getPosition().getY() > TheGame::Instance()->getGameHeight() || (*i)->getDead() == true) {
			delete (*i);
			i = m_enemyBullets.erase(i);
		}
		else {
			(*i)->update();
			++i;
		}
	}

	for (std::vector<PlayerBullet*>::iterator i = m_playerBullets.begin(); i != m_playerBullets.end();) {
		if ((*i)->getPosition().getX() < 0 || (*i)->getPosition().getX() > TheGame::Instance()->getGameWidth()
			|| (*i)->getPosition().getY() < 0 || (*i)->getPosition().getY() > TheGame::Instance()->getGameHeight() || (*i)->getDead() == true) {
			delete (*i);
			i = m_playerBullets.erase(i);
		}
		else {
			(*i)->update();
			++i;
		}
	}
}

void BulletHandler::drawBullets()
{
	for (auto i : m_enemyBullets) {
		i->draw();
	}
	for (auto i : m_playerBullets) {
		i->draw();
	}
}

void BulletHandler::cleanBullets()
{
	for (auto i : m_playerBullets) {
		i->clean();
	}
	for (auto i : m_enemyBullets) {
		i->clean();
	}
	m_playerBullets.clear();
	m_enemyBullets.clear();
}