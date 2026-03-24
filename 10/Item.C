#include "Item.h"
#include <cmath>

using namespace std;

Item::Item(int r, int c, ItemType t) : GameObject(r, c, ""), type(t) {
    symbol = (t == MEDICAL_PACK) ? "+" : "W";
}

void Item::update() {
   
}

bool Item::canPickUp(const Point& p) {
    s
    return (abs(pos.r - p.r) <= 1 && abs(pos.c - p.c) <= 1);
}

string Item::getColor() const {
    return YELLOW;
}