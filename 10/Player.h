#ifndef PLAYER_H
#define PLAYER_H

#include "Ship.h"

using namespace std;

class Player : public Ship {
private:
    int coins;
    int updateCount;
    bool isVertical; 

public:
    Player(int r, int c);

    void update() override;
    void move() override; 
    void fire() override; 

    void addCoins(int amount);
    void heal(int amount);
    void addAmmo(int shells, int missiles);
    
 s
    bool useShells(int count);
    bool useMissiles(int count);
    
    int getCoins() const { return coins; }
    int getNumShells() const { return numShells; }
    int getNumMissiles() const { return numMissiles; }
    
    void setVertical(bool v) { isVertical = v; }
    bool getVertical() const { return isVertical; }

    void draw(char map[MAP_HEIGHT][MAP_WIDTH], string colorMap[MAP_HEIGHT][MAP_WIDTH]) const override;
    string getColor() const override;
};

#endif