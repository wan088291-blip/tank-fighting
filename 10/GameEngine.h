#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <vector>
#include <sstream> 
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Item.h"
#include "Obstacle.h"
using namespace std;

class GameEngine {
private:
    char map[MAP_HEIGHT][MAP_WIDTH];
    string colorMap[MAP_HEIGHT][MAP_WIDTH]; 
    
    Player* player;
    vector<GameObject*> enemies;
    vector<Projectile*> projectiles;
    vector<Item*> items;
    vector<Obstacle*> obstacles; 
    
    bool isRunning;
    int gameTick;
    int currentLevel; 
    int targetCoins;  

    void loadLevel();   
    void spawnEnemies();
    void spawnItems();
    void checkCollisions();
    void render();
    void handleInput();
    
 
    bool isBlocked(int r, int c);
    

    bool isFootprintBlocked(GameObject* obj, int r, int c);

public:
    GameEngine();
    ~GameEngine();
    
    void run(); 
};

#endif