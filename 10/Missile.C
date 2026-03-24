#include "Missile.h"

using namespace std;

Missile::Missile(int r, int c, Direction d, bool playerOwned, GameObject* t)
    : Projectile(r, c, d, playerOwned, 5, "*"), target(t) {}

void Missile::update() {
    if (!active) return;
    
    if (target && target->isActive()) {
        Point tPos = target->getPos();
        if (pos.r < tPos.r) pos.r++;
        else if (pos.r > tPos.r) pos.r--;
        
        if (pos.c < tPos.c) pos.c++;
        else if (pos.c > tPos.c) pos.c--;
    } else {
 s
        switch (dir) {
            case UP: pos.r--; break;
            case DOWN: pos.r++; break;
            case LEFT: pos.c--; break;
            case RIGHT: pos.c++; break;
            default: break;
        }
    }

    if (pos.r < 0 || pos.r >= MAP_HEIGHT || pos.c < 0 || pos.c >= MAP_WIDTH) {
        active = false;
    }
}

string Missile::getColor() const {
    return MAGENTA;
}