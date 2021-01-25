#pragma once
#include "Item.h"
class Armour :
    public Item
{
public:
    Armour() {}
    Armour(std::string name, int cost, int def = 10);
private:
    int defence = 10;
};

