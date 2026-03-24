#ifndef ENEMY_H
#define ENEMY_H

#include "Ship.h"
#include "Projectile.h"
#include <vector>

using namespace std;

class Enemy : public Ship {
protected:
    int coinValue;
public:
    Enemy(int r, int c, string sym, int hp, int value);
    void update() override;
    string getColor() const override;
    int getCoinValue() const { return coinValue; }
    

    vector<Projectile*> attack(GameObject* target) override;
};

#endif