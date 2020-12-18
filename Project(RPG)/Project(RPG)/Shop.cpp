#include "Shop.h"

void Shop::SetGold(int& amount)
{
	mGold += amount;
}

int Shop::GetGold()
{
	return mGold;
}

Inventory* Shop::GetInventory()
{
	return &mInventory;
}
