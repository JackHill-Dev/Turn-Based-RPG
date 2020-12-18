#pragma once
#include "Inventory.h"
class Player
{
public:
	void SetGold(int amount);
	int GetGold();
	Inventory* GetInventory();
	void SetInventory(Inventory& inv);
	void SellItem(Item* item);
private:
	Inventory mInventory;
	int mGold;
};

