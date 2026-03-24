#include "Destroyer.h"
#include "Shell.h"
#include "Torpedo.h"
#include <cstdlib>

using namespace std;

Destroyer::Destroyer(int r, int c) : Enemy(r, c, "O", 10, 1), lastMoveDir(DOWN) { 
    numShells = 10; 
}

void Destroyer::move() {
    if (rand() % 10 < 5) { 
        int dr = (rand() % 3) - 1;
        int dc = (rand() % 3) - 1;
        pos.r += dr;
        pos.c += dc;
        
        if (dr < 0) lastMoveDir = UP;
        else if (dr > 0) lastMoveDir = DOWN;
        else if (dc < 0) lastMoveDir = LEFT;
        else if (dc > 0) lastMoveDir = RIGHT;

        if(pos.r < 0) pos.r = 0; 
        if(pos.r >= MAP_HEIGHT) pos.r = MAP_HEIGHT-1;
        if(pos.c < 0) pos.c = 0; 
        if(pos.c >= MAP_WIDTH) pos.c = MAP_WIDTH-1;
    }
}

void Destroyer::fire() {}

vector<Projectile*> Destroyer::attack(GameObject* target) {
    vector<Projectile*> projs;
    if (rand() % 20 == 0) {
        projs.push_back(new Shell(pos.r, pos.c, lastMoveDir, false));
        if (rand() % 5 == 0) {
             projs.push_back(new Torpedo(pos.r, pos.c, lastMoveDir, false));
        }
    }
    return projs;
}