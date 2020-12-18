#pragma once
#include "Item.h"
class Sword :
    public Item
{
public:
    Sword(std::string name, int cost);
    int GetAtkPower();
    void SetAtkPower(int atk);
private:
    int mAttackPower;

};

