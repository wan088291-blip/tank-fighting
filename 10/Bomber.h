#ifndef BOMBER_H
#define BOMBER_H

#include "GameObject.h"
#include "Projectile.h" 
#include <vector>

using namespace std;

class Bomber : public GameObject {
private:
    Direction flyDirection;
    int bombCooldown;
public:
    Bomber(int r, int c);
    void update() override;
    string getColor() const override;
    vector<Projectile*> attack(GameObject* target) override;
    void draw(char map[MAP_HEIGHT][MAP_WIDTH], string colorMap[MAP_HEIGHT][MAP_WIDTH]) const override;
    
    void reverseDirection();
};

#endif