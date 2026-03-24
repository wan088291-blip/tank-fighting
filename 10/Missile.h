#ifndef MISSILE_H
#define MISSILE_H

#include "Projectile.h"

class Missile : public Projectile {
private:
    GameObject* target;
public:
    Missile(int r, int c, Direction d, bool playerOwned, GameObject* t);
    void update() override;
    string getColor() const override;
    
  
    GameObject* getTarget() const { return target; }
    void clearTarget() { target = nullptr; }
};

#endif