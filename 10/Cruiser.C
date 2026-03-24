#include "Cruiser.h"
#include "Shell.h"
#include "Missile.h"
#include <cstdlib>

using namespace std;

Cruiser::Cruiser(int r, int c) : Enemy(r, c, "<>", 100, 10), lastMoveDir(LEFT) { 
    numShells = 30; numMissiles = 2; 
}

void Cruiser::move() {
    if (rand() % 10 < 4) {
        int move = (rand() % 3) - 1; 
        pos.c += move;
        
        if (move < 0) lastMoveDir = LEFT;
        if (move > 0) lastMoveDir = RIGHT;

        if(pos.c < 0) pos.c = 0; 
        if(pos.c >= MAP_WIDTH) pos.c = MAP_WIDTH-1;
    }
}

void Cruiser::fire() {}

vector<Projectile*> Cruiser::attack(GameObject* target) {
    vector<Projectile*> projs;
    
    if (rand() % 10 == 0) {
        projs.push_back(new Shell(pos.r, pos.c, lastMoveDir, false));
    }

    if (rand() % 50 == 0) {
        projs.push_back(new Missile(pos.r, pos.c, lastMoveDir, false, target));
    }

    return projs;
}