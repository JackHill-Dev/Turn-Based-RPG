#pragma once
#include "Inventory.h"
class Shop
{
public:
	Shop();
	void SetGold(int amount);
	void BuyItem(Item* item);
	void SetInventory(Inventory& i);
	int GetGold();
	Inventory& GetInventory();
private:
	Inventory mInventory;
	int mGold;
};

