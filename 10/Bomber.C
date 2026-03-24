#include "Bomber.h"
#include "Torpedo.h"
#include <cstdlib>
#include <cmath> 

using namespace std;

Bomber::Bomber(int r, int c) : GameObject(r, c, "=="), bombCooldown(0) {
    flyDirection = (rand() % 2 == 0) ? LEFT : RIGHT;
    if (flyDirection == RIGHT) pos.c = 0;
    else pos.c = MAP_WIDTH - 1;
    pos.r = r; 
}

void Bomber::update() {

    if (flyDirection == RIGHT) pos.c++;
    else pos.c--;

    if (pos.c < 0 || pos.c >= MAP_WIDTH) active = false;
    
    if (bombCooldown > 0) bombCooldown--;
}


void Bomber::reverseDirection() {
    if (flyDirection == RIGHT) flyDirection = LEFT;
    else flyDirection = RIGHT;
}

string Bomber::getColor() const { return BLUE; }

void Bomber::draw(char map[MAP_HEIGHT][MAP_WIDTH], string colorMap[MAP_HEIGHT][MAP_WIDTH]) const {
    if (!active) return;
    
    string c = getColor();
    int r = pos.r;
    int col = pos.c;

    if (r < 1 || r >= MAP_HEIGHT - 1 || col < 0 || col >= MAP_WIDTH - 1) return;

    char topChar, botChar;

    if (flyDirection == RIGHT) {
  
        topChar = '\\'; 
        botChar = '/';
    } else {

        topChar = '/';
        botChar = '\\';
    }

    map[r-1][col] = topChar; colorMap[r-1][col] = c;
    map[r][col] = '='; colorMap[r][col] = c;
    if (col + 1 < MAP_WIDTH) { map[r][col+1] = '='; colorMap[r][col+1] = c; }
    map[r+1][col] = botChar; colorMap[r+1][col] = c;
}

vector<Projectile*> Bomber::attack(GameObject* target) {
    vector<Projectile*> projs;
    if (bombCooldown > 0) return projs;

    bool nearPlayer = target && abs(pos.c - target->getPos().c) < 3;
    
    if (nearPlayer && rand() % 3 == 0) {
        projs.push_back(new Torpedo(pos.r, pos.c, DOWN, false));
        bombCooldown = 5; 
    }
    
    return projs;
}