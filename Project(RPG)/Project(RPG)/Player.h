#pragma once
#include "Inventory.h"
class Player
{
public:
	void SetGold(int amount);
	int GetGold();
	Inventory* GetInventory();
	void SetInventory(Inventory& inv);
private:
	Inventory mInventory;
	int mGold;
};

