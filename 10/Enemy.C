#include "Enemy.h"

using namespace std;

Enemy::Enemy(int r, int c, string sym, int hp, int value) 
    : Ship(r, c, sym, hp), coinValue(value) {}

void Enemy::update() { move(); }

string Enemy::getColor() const { return BLUE; }

vector<Projectile*> Enemy::attack(GameObject* target) {
    return {}; 
}