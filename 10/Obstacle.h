#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "GameObject.h"

using namespace std;

class Obstacle : public GameObject {
public:
    Obstacle(int r, int c);
    
    void update() override;
    string getColor() const override; 
};

#endif