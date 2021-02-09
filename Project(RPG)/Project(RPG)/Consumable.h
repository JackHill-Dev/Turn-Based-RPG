#pragma once
#include "Item.h"
class Consumable :
    public Item
{
public:
    Consumable() {}
    Consumable(std::string name, int cost);
    void OnConsume();

    std::string GetDescription() override;

private:


};

