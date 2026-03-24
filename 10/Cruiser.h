#ifndef CRUISER_H
#define CRUISER_H

#include "Enemy.h"

class Cruiser : public Enemy {
private:
    Direction lastMoveDir;
public:
    Cruiser(int r, int c);
    void move() override;
    void fire() override;
    vector<Projectile*> attack(GameObject* target) override;
};

#endif