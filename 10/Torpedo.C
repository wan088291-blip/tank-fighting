#include "Torpedo.h"

using namespace std;

Torpedo::Torpedo(int r, int c, Direction d, bool playerOwned)
    : Projectile(r, c, d, playerOwned, 10, "=") {}

string Torpedo::getColor() const {
    return CYAN;
}