#pragma once
#include "Item.h"
class Weapon :
    public Item
{
public:
    Weapon() {}
    Weapon(std::string name, std::string spriteName, int atk, int cost);
    int GetAtkPower();
    void SetAtkPower(int atk);

    std::string GetDescription() override;
    Item* Clone() override { return new Weapon(*this); }
private:
    int mAttackPower = 10;

};

