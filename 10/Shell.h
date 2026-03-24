#ifndef SHELL_H
#define SHELL_H

#include "Projectile.h"

class Shell : public Projectile {
public:
    Shell(int r, int c, Direction d, bool playerOwned);
    string getColor() const override;
};

#endif