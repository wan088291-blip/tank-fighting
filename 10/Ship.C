#include "Ship.h"

using namespace std;

Ship::Ship(int r, int c, string sym, int hp) 
    : GameObject(r, c, sym), health(hp), maxHealth(hp), numShells(0), numMissiles(0), moveCounter(0) {}

void Ship::takeDamage(int dmg) {
    health -= dmg;
    if (health <= 0) {
        active = false;
    }
}

bool Ship::isDestroyed() const {
    return health <= 0;
}