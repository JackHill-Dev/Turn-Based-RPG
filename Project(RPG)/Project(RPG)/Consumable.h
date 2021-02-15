#pragma once
#include "Item.h"
class Consumable :
    public Item
{
public:
    Consumable() {}
    Consumable(std::string name,std::string spriteName, int cost);
    void OnConsume();

    std::string GetDescription() override;
    Item* Clone() override { return new Consumable(*this); }
private:


};

