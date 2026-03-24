#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Common.h"
#include <string>
#include <vector>

using namespace std;


class Projectile; 

class GameObject {
protected:
    Point pos;
    string symbol;
    bool active; 

public:
    GameObject(int r, int c, string sym);
    virtual ~GameObject() {}

    virtual void update() = 0; 

    virtual vector<Projectile*> attack(GameObject* target) { return {}; }
    
    virtual void draw(char map[MAP_HEIGHT][MAP_WIDTH], string colorMap[MAP_HEIGHT][MAP_WIDTH]) const;
    virtual string getColor() const { return RESET; }

    Point getPos() const { return pos; }
    void setPos(int r, int c) { pos.r = r; pos.c = c; } 
    bool isActive() const { return active; }
    void deactivate() { active = false; }
    string getSymbol() const { return symbol; }
};

#endif