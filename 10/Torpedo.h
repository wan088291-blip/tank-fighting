#ifndef TORPEDO_H
#define TORPEDO_H

#include "Projectile.h"

class Torpedo : public Projectile {
public:
    Torpedo(int r, int c, Direction d, bool playerOwned);
    string getColor() const override;
};

#endif