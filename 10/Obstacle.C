#include "Obstacle.h"
using namespace std;
Obstacle::Obstacle(int r, int c) : GameObject(r, c, "#") {}
void Obstacle::update() {}
string Obstacle::getColor() const {
    return GREEN; 
}