#pragma once

#include <iostream>
#include <vector>

class Player;
class GameObject;
class TileLayer;

class CollisionManager
{
public:
    static CollisionManager* Instance() {
        if (collisionInstance == NULL) {
            collisionInstance = new CollisionManager();
        }
        return collisionInstance;
    }

    //Check the following:
    //Player & (Enemy, Enemy Bullet, Tile)
    //Enemy & Player Bullet
    void checkPlayer_EnemyBulletCollision(Player* pPlayer);
    void checkPlayer_EnemyCollision(Player* pPlayer, const std::vector<GameObject*>& objects);
    void checkEnemy_PlayerBulletCollision(const std::vector<GameObject*>& objects);
    void checkPlayer_TileCollision(Player* pPlayer, const std::vector<TileLayer*>& collisionLayers);
 
private:
    CollisionManager() {};
    ~CollisionManager() {};

    static CollisionManager* collisionInstance;
};

typedef CollisionManager TheCollisionManager;
