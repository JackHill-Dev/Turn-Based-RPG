#include "Shop.h"

Shop::Shop()
{
	mInventory.SetInitialGridPos(850);
}

void Shop::SetGold(int amount)
{
	mGold += amount;
}

int Shop::GetGold()
{
	return mGold;
}

Inventory& Shop::GetInventory()
{
	return mInventory;
}

void Shop::BuyItem(Item* item)
{
	SetGold(item->GetCost());
	mInventory.RemoveItem(item);

	// Check if shop has item
	// Check if player has sufficient gold
	// Check that player meets level requirements
		// Add item to player inventory
		// Take the cost of the item off the player's gold amount
		// Add cost of item to shop
		// Remove item from shop inventory
		
}

void Shop::SetInventory(Inventory& i)
{
	mInventory = i;
}
