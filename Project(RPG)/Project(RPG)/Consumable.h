#pragma once
#include "Item.h"
class Consumable :
    public Item
{
public:
    Consumable(std::string name, int cost);
    void OnConsume();
private:


};

