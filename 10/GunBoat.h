#ifndef GUNBOAT_H
#define GUNBOAT_H

#include "Enemy.h"

class GunBoat : public Enemy {
private:
    Direction lastMoveDir;
public:
    GunBoat(int r, int c);
    void move() override;
    void fire() override; 
    vector<Projectile*> attack(GameObject* target) override;
};

#endif