#include "GunBoat.h"
#include "Shell.h"
#include <cstdlib>

using namespace std;

GunBoat::GunBoat(int r, int c) : Enemy(r, c, "o", 1, 1), lastMoveDir(DOWN) { 
    numShells = 10; 
}

void GunBoat::move() {
    if (rand() % 10 < 3) { 
        int d = rand() % 4;
        lastMoveDir = (Direction)d; 
        if (d == 0 && pos.r > 0) pos.r--;      
        else if (d == 1 && pos.r < MAP_HEIGHT - 1) pos.r++; 
        else if (d == 2 && pos.c > 0) pos.c--; 
        else if (d == 3 && pos.c < MAP_WIDTH - 1) pos.c++;  
    }
}

void GunBoat::fire() {} 

vector<Projectile*> GunBoat::attack(GameObject* target) {
    vector<Projectile*> projs;
    if (rand() % 20 == 0) {
        projs.push_back(new Shell(pos.r, pos.c, lastMoveDir, false));
    }
    return projs;
}