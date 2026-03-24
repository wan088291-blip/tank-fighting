#include "Projectile.h"

using namespace std;

Projectile::Projectile(int r, int c, Direction d, bool playerOwned, int dmg, string sym)
    : GameObject(r, c, sym), damage(dmg), dir(d), isPlayerOwner(playerOwned) {}

void Projectile::update() {
    if (!active) return;


    switch (dir) {
        case UP: pos.r--; break;
        case DOWN: pos.r++; break;
        case LEFT: pos.c--; break;
        case RIGHT: pos.c++; break;
        default: break;
    }

    if (pos.r < 0 || pos.r >= MAP_HEIGHT || pos.c < 0 || pos.c >= MAP_WIDTH) {
        active = false;
    }
}