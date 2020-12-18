#pragma once
#include "Inventory.h"
class Player
{
public:
	void SetGold(int amount);
	int GetGold();
	Inventory* GetInventory();
private:
	Inventory mInventory;
	int mGold;
};

