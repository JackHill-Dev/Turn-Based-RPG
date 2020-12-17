#include "Inventory.h"
#include <algorithm>

void Inventory::AddItem(Item* item)
{
	mItems.push_back(item);
}

void Inventory::RemoveItem(Item* item)
{
	std::remove_if(mItems.begin(), mItems.end(), [&item](Item* i) {return item == i; });
}

