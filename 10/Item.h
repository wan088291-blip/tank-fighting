#ifndef ITEM_H
#define ITEM_H

#include "GameObject.h"

using namespace std;

enum ItemType { MEDICAL_PACK, WEAPON_PACK };

class Item : public GameObject {
private:
    ItemType type;

public:
    Item(int r, int c, ItemType t);
    
    void update() override;
    ItemType getType() const { return type; }
    bool canPickUp(const Point& playerPos);
    
   
    string getColor() const override;
};

#endif