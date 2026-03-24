#ifndef DESTROYER_H
#define DESTROYER_H

#include "Enemy.h"

class Destroyer : public Enemy {
private:
    Direction lastMoveDir;
public:
    Destroyer(int r, int c);
    void move() override;
    void fire() override;
    vector<Projectile*> attack(GameObject* target) override;
};

#endif