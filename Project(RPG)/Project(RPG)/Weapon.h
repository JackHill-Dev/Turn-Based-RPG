#pragma once
#include "Item.h"
class Weapon :
    public Item
{
public:
    Weapon(std::string name, int cost);
    int GetAtkPower();
    void SetAtkPower(int atk);
private:
    int mAttackPower;

};

