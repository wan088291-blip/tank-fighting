#include "Shell.h"

using namespace std;

Shell::Shell(int r, int c, Direction d, bool playerOwned)
    : Projectile(r, c, d, playerOwned, 1, "") {
    
    symbol = (d == UP || d == DOWN) ? "|" : "-";
}

string Shell::getColor() const {
    return WHITE;
}