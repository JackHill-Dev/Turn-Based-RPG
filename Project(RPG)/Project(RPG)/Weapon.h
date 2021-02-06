#pragma once
#include "Item.h"
class Weapon :
    public Item
{
public:
    Weapon() {}
    Weapon(std::string name, int cost);
    int GetAtkPower();
    void SetAtkPower(int atk);

    std::string GetDescription() override;

private:
    int mAttackPower = 10;

};

