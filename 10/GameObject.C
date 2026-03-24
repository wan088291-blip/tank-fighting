#include "GameObject.h"
#include <iostream>

using namespace std;

GameObject::GameObject(int r, int c, string sym) : pos{r, c}, symbol(sym), active(true) {}


void GameObject::draw(char map[MAP_HEIGHT][MAP_WIDTH], string colorMap[MAP_HEIGHT][MAP_WIDTH]) const {
    if (!active) return;

    int len = symbol.length();

    int startCol = pos.c - (len / 2); 

    for (int i = 0; i < len; ++i) {
        int r = pos.r;
        int c = startCol + i;

  
        if (r >= 0 && r < MAP_HEIGHT && c >= 0 && c < MAP_WIDTH) {
            map[r][c] = symbol[i];
            colorMap[r][c] = getColor();
        }
    }
}