#ifndef SHIP_H
#define SHIP_H

#include "GameObject.h"

using namespace std;

class Ship : public GameObject {
protected:
    int health;
    int maxHealth;
    int numShells;
    int numMissiles;
    int moveCounter;

public:
    Ship(int r, int c, string sym, int hp);
    
    void takeDamage(int dmg);
    bool isDestroyed() const;
    
    virtual void move() = 0; 
    virtual void fire() = 0;
    
    int getHealth() const { return health; }
};

#endif