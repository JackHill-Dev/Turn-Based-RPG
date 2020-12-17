#pragma once
#include "RenderObject.h"
#include "Inventory.h"
class Player :
    public RenderObject
{
public:
    void SetGold(int& amount);
	int GetGold();
    Inventory& GetInventory();
private:
    int mGold;
    Inventory mInventory;
};

