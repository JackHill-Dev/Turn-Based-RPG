#pragma once
#include "Inventory.h"
class Shop
{
public:
	void SetGold(int& amount);
	int GetGold();
	Inventory* GetInventory();
	void BuyItem(Item* item);
private:
	Inventory mInventory;
	int mGold;
};

