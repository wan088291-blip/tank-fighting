#include "Player.h"
#include <algorithm> // for min

using namespace std;

Player::Player(int r, int c) : Ship(r, c, "<=>", 1000), coins(0), updateCount(0), isVertical(false) {
    numShells = 100;
    numMissiles = 5;
}

void Player::addCoins(int amount) { coins += amount; }
void Player::heal(int amount) { health = min(health + amount, maxHealth + 1000); }
void Player::addAmmo(int shells, int missiles) { numShells += shells; numMissiles += missiles; }

// === 新增：消耗弹药实现 ===
bool Player::useShells(int count) {
    if (numShells >= count) {
        numShells -= count;
        return true;
    }
    return false;
}

bool Player::useMissiles(int count) {
    if (numMissiles >= count) {
        numMissiles -= count;
        return true;
    }
    return false;
}

void Player::update() {
    updateCount++;
  
    if (updateCount % 10 == 0) numShells++;
    if (updateCount % 1000 == 0) numMissiles++;
}

void Player::move() {} 
void Player::fire() {}

string Player::getColor() const {
    return RED; 
}

void Player::draw(char map[MAP_HEIGHT][MAP_WIDTH], string colorMap[MAP_HEIGHT][MAP_WIDTH]) const {
    if (!active) return;
    
    string c = getColor();

    if (isVertical) {
        if (pos.r - 1 >= 0) { map[pos.r - 1][pos.c] = '^'; colorMap[pos.r - 1][pos.c] = c; }
        if (pos.r >= 0 && pos.r < MAP_HEIGHT) { map[pos.r][pos.c] = '"'; colorMap[pos.r][pos.c] = c; }
        if (pos.r + 1 < MAP_HEIGHT) { map[pos.r + 1][pos.c] = 'v'; colorMap[pos.r + 1][pos.c] = c; }
    } else {
        int startCol = pos.c - 1;
        string sym = "<=>";
        for (int i = 0; i < 3; ++i) {
            int col = startCol + i;
            if (pos.r >= 0 && pos.r < MAP_HEIGHT && col >= 0 && col < MAP_WIDTH) {
                map[pos.r][col] = sym[i];
                colorMap[pos.r][col] = c;
            }
        }
    }
}