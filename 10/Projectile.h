#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "GameObject.h"

using namespace std;



class Projectile : public GameObject {
protected:
    int damage;
    Direction dir;
    bool isPlayerOwner;

public:
    Projectile(int r, int c, Direction d, bool playerOwned, int dmg, string sym);
    virtual ~Projectile() {}
    
    virtual void update() override;
    int getDamage() const { return damage; }
    bool isFriendly() const { return isPlayerOwner; }
    
    virtual string getColor() const override { return WHITE; }
};

#endif