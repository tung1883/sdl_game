#pragma once

#include <iostream>

#include "Level1.h"
#include "Level2.h"
#include "Collision.h"
#include "Player.h"
#include "Cyrer.h"
#include "Glider.h"
#include "Slinger.h"
#include "Bullet.h"
#include "AnimatedGraphic.h"
#include "ScrollingBackground.h"
#include "Heart.h"

const std::string Level1::playID = "LEVEL_1";

void Level1::render() {
    for (auto i : m_gameObjects) {
        i->draw();
    }

    pPlayer->draw();

    TheBulletHandler::Instance()->drawBullets();

    TheMapParser::Instance()->getMaps("level1")->render();
}

void Level1::update() {

    //before = > winningInit = > winningDrawing = > winning = > after
    //
    //    //can integrate winningInit + winningDrawing states
    //    + ) before = > winningInit
    //    1. condition: end of map + player still alive(health > 0)
    //    2. if condition == true = > set winningInit = true
    //    + ) winningInit = > winningDrawing
    //    1. condition: winningInit == true
    //    2. if condition == true = > set winningDrawing == true, winningInit == false
    //    3. set player to winning mode(how ? )
    //    + ) include winning mode in player class
    //    + ) a variable(bool m_winningDrawing) and a method(bool setWinningDrawing(bool)) to init / stop the winning mode
    //    4. not checking for inputand collision

    //    //INTERGRATE VERSION 
    //    before => winningDrawing => winning => after
    //    +) before => winningDrawing
    //    1. condition: end of map + player still alive (health > 0)
    //    2. if condition == true => set winningDraw = true
    // 
    //    //3. set player to winning mode 
    //    //      + ) include winning mode in player class
    //    //      + ) a variable(bool m_winningDrawing) and a method(bool setWinningDrawing(bool)) to init / stop the winning mode
    //    //4. stop checking input + collision
    //
    //    ////////////////////
    //    +) winningDrawing = > winning
    //    1. condition: if player flied over the map(position > game width)
    //    2. if condition == true = > set winning true, winningDrawing == false
    //    + ) set winning mode of player = > false
    //    + ) winning = > after
    //    1. condition: winning == true
    //    2. if (condition == true) = > winning == false, change to new state(v1.1: change to game over state)
    //
    //    //possible improvements
    //    winning = > after state : more levels = > change to different levels

    if (m_winning) {
        onExit();
        TheGame::Instance()->getStateMachine()->pushState(new Level2());
        return;
    }

    if (pPlayer->getHealth() == 0) {
        onExit();
        TheGame::Instance()->getStateMachine()->pushState(new GameOverState());
        return;
    }

    if (m_winningAnimation) {
        pPlayer->setWinningDrawing(true);
        pPlayer->update();
        if (pPlayer->getPosition().getX() >= GAME_WIDTH) {
            m_winning = true;
            m_winningAnimation = false;
            pPlayer->setWinningDrawing(false);
        }
        return;
    }

    if (pPlayer->getPosition().getX() >= GAME_WIDTH / 2 && pPlayer->getHealth() > 0 && TheMapParser::Instance()->getTileLayers("level1")[0]->getPosition().getX() == TILE_LAYER_WIDTH - GAME_WIDTH) {
        m_winningAnimation = true;
        return;
    }

    //if (m_winningInit) {
    //    pPortal = new Portal(new ObjectParams("portal", 1318, 320 - PORTAL_WIDTH, PORTAL_WIDTH, PORTAL_HEIGHT, 8, 2));
    //    pPlayer->update();
    //    m_winningAnimation = true;
    //    return;
    //}
    //
    //if (pPlayer->getHealth() > 0 && TheMapParser::Instance()->getTileLayers("level1")[0]->getPosition().getX() == TILE_LAYER_WIDTH - GAME_WIDTH) {
    //    m_winningInit = true;
    //    return;
    //}

    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
        TheGame::Instance()->getStateMachine()->pushState(new PauseState());
    }

    TheMapParser::Instance()->getMaps("level1")->update();

    checkBullet_TileCollision(TheMapParser::Instance()->getTileLayers("level1"));
    checkEnemy_PlayerBulletCollision(m_gameObjects);
    checkEnemy_PlayerBulletCollision(*TheMapParser::Instance()->getObjectLayer("level1")[0]->getGameObjects());
    checkPlayer_EnemyBulletCollision(pPlayer);
    checkPlayer_EnemyCollision(pPlayer, *TheMapParser::Instance()->getObjectLayer("level1")[0]->getGameObjects());
    checkPlayer_TileCollision(pPlayer, TheMapParser::Instance()->getTileLayers("level1"));

    if (pPlayer->getCollision() == true && m_gameObjects.size() > 1) {
        m_gameObjects.pop_back();
        pPlayer->setCollision(false);
    }

    for (auto i : m_gameObjects) {
        i->update();
    }

    pPlayer->update();

    TheBulletHandler::Instance()->updateBullets();

}

bool Level1::onEnter() {
    //Sound Effects 
    if (!TheSoundManager::Instance()->load("res/boom.wav", "explosionEffect", SOUND_SFX)) {
        return false;
    }
    if (!TheSoundManager::Instance()->load("res/phaser.wav", "shootEffect", SOUND_SFX)) {
        return false;
    }

    //Bullets, explosion textures
    if (!TheTextureManager::Instance()->loadTexture("res/explosion.png", "explosion", TheGame::Instance()->getRenderer()), 0, 0, 0)
    {
        return false;
    }
    if (!TheTextureManager::Instance()->loadTexture("res/smallexplosion.png", "smallexplosion", TheGame::Instance()->getRenderer()))
    {
        return false;
    }
    if (!TheTextureManager::Instance()->loadTexture("res/largeexplosion.png", "largeexplosion", TheGame::Instance()->getRenderer()))
    {
        return false;
    }
    if (!TheTextureManager::Instance()->loadTexture("res/bossexplosion.png", "bossexplosion", TheGame::Instance()->getRenderer()))
    {
        return false;
    }
    if (!TheTextureManager::Instance()->loadTexture("res/bullet1.png", "bullet1", TheGame::Instance()->getRenderer()))
    {
        return false;
    }
    if (!TheTextureManager::Instance()->loadTexture("res/bullet2.png", "bullet2", TheGame::Instance()->getRenderer()))
    {
        return false;
    }
    if (!TheTextureManager::Instance()->loadTexture("res/bullet3.png", "bullet3", TheGame::Instance()->getRenderer()))
    {
        return false;
    }

    //Background textures
    if (!TheTextureManager::Instance()->loadTexture("res/mountain.png", "mountain", TheGame::Instance()->getRenderer()))
    {
        return false;
    }

    //Player and enemies textures
    if (!TheTextureManager::Instance()->loadTexture("res/helicopter.png", "helicopter", TheGame::Instance()->getRenderer()))
    {
        return false;
    }
    if (!TheTextureManager::Instance()->loadTexture("res/resurrect.png", "resurrect", TheGame::Instance()->getRenderer()))
    {
        return false;
    }
    if (!TheTextureManager::Instance()->loadTexture("res/slinger.png", "slinger", TheGame::Instance()->getRenderer()))
    {
        return false;
    }
    if (!TheTextureManager::Instance()->loadTexture("res/cyrer.png", "cyrer", TheGame::Instance()->getRenderer()))
    {
        return false;
    }
    if (!TheTextureManager::Instance()->loadTexture("res/glider.png", "glider", TheGame::Instance()->getRenderer()))
    {
        return false;
    }

    //Heart textures
    if (!TheTextureManager::Instance()->loadTexture("res/heart.png", "heart", TheGame::Instance()->getRenderer()))
    {
        return false;
    }

    //Background Objects
    GameObject* mountain = new ScrollingBackground(new ObjectParams("mountain", 0, 0, 1280, 640, 1), 3);
    GameObject* heart_1 = new Heart(new ObjectParams("heart", 20, 20, 36, 29, 1));
    GameObject* heart_2 = new Heart(new ObjectParams("heart", 20 + (36 + 2), 20, 36, 29, 1));
    GameObject* heart_3 = new Heart(new ObjectParams("heart", 20 + (36 + 2)*2 , 20, 36, 29, 1));

    //Player Object
    pPlayer = new Player(new ObjectParams("helicopter", 50, 500, 128, 55, 5));

    m_gameObjects.push_back(mountain);
    m_gameObjects.push_back(heart_1);
    m_gameObjects.push_back(heart_2);
    m_gameObjects.push_back(heart_3);

    if (!TheMapParser::Instance()->parse("level1", "res/Tile/level1.tmx")) {
        return false;
    }

    std::cout << "Entering level 1" << std::endl;
    return true;
}

bool Level1::onExit() {
    TheBulletHandler::Instance()->cleanBullets();
    TheTextureManager::Instance()->clearTextureFromMap("background1");
    TheTextureManager::Instance()->clearTextureFromMap("helicopter");
    TheTextureManager::Instance()->clearTextureFromMap("helicopter2");
    TheTextureManager::Instance()->clearTextureFromMap("bullet3");

    std::cout << "Exiting level 1" << std::endl;
    return true;
}

//Checking collision
void Level1::checkPlayer_EnemyBulletCollision(Player* pPlayer)
{
    if (pPlayer->getWinningDrawing()) {
        return;
    }

    SDL_Rect* pRect1 = new SDL_Rect();
    pRect1->x = pPlayer->getPosition().getX();
    pRect1->y = pPlayer->getPosition().getY();
    pRect1->w = pPlayer->getWidth();
    pRect1->h = pPlayer->getHeight();

    for (int i = 0; i < TheBulletHandler::Instance()->getEnemyBullets().size(); i++)
    {

        EnemyBullet* pEnemyBullet = TheBulletHandler::Instance()->getEnemyBullets()[i];
        if (pEnemyBullet->getDead()) {
            continue;
        }

        SDL_Rect* pRect2 = new SDL_Rect();
        pRect2->x = pEnemyBullet->getPosition().getX();
        pRect2->y = pEnemyBullet->getPosition().getY();

        pRect2->w = pEnemyBullet->getWidth();
        pRect2->h = pEnemyBullet->getHeight();

        if (RectRect(pRect1, pRect2))
        {
            if (!pPlayer->dying() && !pEnemyBullet->dying())
            {
                pEnemyBullet->setDead(true);
                pPlayer->collision();
            }
        }

        delete pRect2;
    }

    delete pRect1;
}
void Level1::checkEnemy_PlayerBulletCollision(const std::vector<GameObject*>& objects)
{

    for (int i = 0; i < objects.size(); i++)
    {
        GameObject* pObject = objects[i];

        for (int j = 0; j < TheBulletHandler::Instance()->getPlayerBullets().size(); j++)
        {
            if (pObject->type() != std::string("Enemy") || !pObject->updating())
            {
                continue;
            }

            SDL_Rect* pRect1 = new SDL_Rect();
            pRect1->x = pObject->getPosition().getX();
            pRect1->y = pObject->getPosition().getY();
            pRect1->w = pObject->getWidth();
            pRect1->h = pObject->getHeight();

            PlayerBullet* pPlayerBullet = TheBulletHandler::Instance()->getPlayerBullets()[j];

            if (pPlayerBullet->getDead()) {
                continue;
            }

            SDL_Rect* pRect2 = new SDL_Rect();
            pRect2->x = pPlayerBullet->getPosition().getX();
            pRect2->y = pPlayerBullet->getPosition().getY();
            pRect2->w = pPlayerBullet->getWidth();
            pRect2->h = pPlayerBullet->getHeight();

            if (RectRect(pRect1, pRect2))
            {
                if (!pObject->dying() && !pPlayerBullet->dying())
                {
                    pPlayerBullet->setDead(true);
                    pObject->collision();
                }

            }

            delete pRect1;
            delete pRect2;
        }
    }
}
void Level1::checkPlayer_EnemyCollision(Player* pPlayer, const std::vector<GameObject*>& objects)
{
    if (pPlayer->getWinningDrawing()) {
        return;
    }

    SDL_Rect* pRect1 = new SDL_Rect();
    pRect1->x = pPlayer->getPosition().getX();
    pRect1->y = pPlayer->getPosition().getY();
    pRect1->w = pPlayer->getWidth();
    pRect1->h = pPlayer->getHeight();

    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->type() != std::string("Enemy") || !objects[i]->updating())
        {
            continue;
        }

        SDL_Rect* pRect2 = new SDL_Rect();
        pRect2->x = objects[i]->getPosition().getX();
        pRect2->y = objects[i]->getPosition().getY();
        pRect2->w = objects[i]->getWidth();
        pRect2->h = objects[i]->getHeight();

        if (RectRect(pRect1, pRect2))
        {
            if (!objects[i]->dead() && !objects[i]->dying())
            {
                pPlayer->collision();
            }
        }

        delete pRect2;
    }

    delete pRect1;
}
void Level1::checkPlayer_TileCollision(Player* pPlayer, const std::vector<TileLayer*>& collisionLayers)
{
    if (pPlayer->getWinningDrawing()) {
        return;
    }

    for (std::vector<TileLayer*>::const_iterator it = collisionLayers.begin(); it != collisionLayers.end(); it++)
    {
        TileLayer* pTileLayer = (*it);
        std::vector<std::vector<int>> tiles = pTileLayer->getTileMap();

        Vector2D layerPos = pTileLayer->getPosition();

        int x, y, tileColumn, tileRow, tileID = 0;

        x = layerPos.getX() / pTileLayer->getTileSize();
        y = layerPos.getY() / pTileLayer->getTileSize();

        //if (pPlayer->getVelocity().getX() >= 0 || pPlayer->getVelocity().getY() >= 0)
        //{
        //    tileColumn = ((pPlayer->getPosition().getX() + pPlayer->getWidth()) / pTileLayer->getTileSize());
        //    tileRow = ((pPlayer->getPosition().getY() + pPlayer->getHeight()) / pTileLayer->getTileSize());
        //    tileID = tiles[tileRow + y][tileColumn + x];
        //}
        //else if (pPlayer->getVelocity().getX() < 0 || pPlayer->getVelocity().getY() < 0)
        //{
        //    tileColumn = pPlayer->getPosition().getX() / pTileLayer->getTileSize();
        //    tileRow = pPlayer->getPosition().getY() / pTileLayer->getTileSize();
        //    tileID = tiles[tileRow + y][tileColumn + x];
        //}
        //

        //Counters
        int i, j, i_max, j_max;
        i = j = 0;

        if (pPlayer->getVelocity().getX() >= 0.0) {
            tileColumn = (pPlayer->getPosition().getX() + pPlayer->getWidth()) / pTileLayer->getTileSize();
            i_max = 4;
        }
        else {
            tileColumn = pPlayer->getPosition().getX() / pTileLayer->getTileSize();
            i_max = 0;
        }

        if (pPlayer->getVelocity().getY() > 0.0) {
            tileRow = ((pPlayer->getPosition().getY() + pPlayer->getHeight()) / pTileLayer->getTileSize());
            j_max = 0;
        }
        else {
            tileRow = pPlayer->getPosition().getY() / pTileLayer->getTileSize();
            j_max = 1;
        }

        tileID = tiles[tileRow + y][tileColumn + x];

        tileID = tiles[tileRow + y][tileColumn + x];
        for (; j <= j_max; j++) {
            tileID = tiles[std::max(tileRow + y - i, 0)][tileColumn + x];
            if (tileID != 0) {

                pPlayer->collision();
                return;
            }
        }
        for (; i <= i_max; i++) {
            tileID = tiles[tileRow + y][std::max(tileColumn + x - i, 0)];
            if (tileID != 0) {
                pPlayer->collision();
                return;
            }
        }
        //if (tileID != 0) {
        //    pPlayer->collision();
        //}
    }
}
void Level1::checkBullet_TileCollision(const std::vector<TileLayer*>& collisionLayers) {
    for (std::vector<TileLayer*>::const_iterator it = collisionLayers.begin(); it != collisionLayers.end(); it++)
    {
        TileLayer* pTileLayer = (*it);
        std::vector<std::vector<int>> tiles = pTileLayer->getTileMap();

        Vector2D layerPos = pTileLayer->getPosition();

        int x, y, tileColumn, tileRow, tileID = 0;

        x = layerPos.getX() / pTileLayer->getTileSize();
        y = layerPos.getY() / pTileLayer->getTileSize();

        //if (pPlayer->getVelocity().getX() >= 0 || pPlayer->getVelocity().getY() >= 0)
        //{
        //    tileColumn = ((pPlayer->getPosition().getX() + pPlayer->getWidth()) / pTileLayer->getTileSize());
        //    tileRow = ((pPlayer->getPosition().getY() + pPlayer->getHeight()) / pTileLayer->getTileSize());
        //    tileID = tiles[tileRow + y][tileColumn + x];
        //}
        //else if (pPlayer->getVelocity().getX() < 0 || pPlayer->getVelocity().getY() < 0)
        //{
        //    tileColumn = pPlayer->getPosition().getX() / pTileLayer->getTileSize();
        //    tileRow = pPlayer->getPosition().getY() / pTileLayer->getTileSize();
        //    tileID = tiles[tileRow + y][tileColumn + x];
        //}
        //

        for (auto i : TheBulletHandler::Instance()->getPlayerBullets()) {
            if (i->getDead()) {
                continue;
            };

            tileColumn = i->getPosition().getX() / pTileLayer->getTileSize();
            tileRow = i->getPosition().getY() / pTileLayer->getTileSize();
            tileID = tiles[tileRow + y][tileColumn + x];
            if (tileID != 0) {
                i->setDead(true);
            }
        }

    }
}