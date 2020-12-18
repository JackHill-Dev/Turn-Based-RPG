#pragma once
#include "Inventory.h"
class Shop
{
public:
	void SetGold(int& amount);
	int GetGold();
	Inventory* GetInventory();
private:
	Inventory mInventory;
	int mGold;
};

