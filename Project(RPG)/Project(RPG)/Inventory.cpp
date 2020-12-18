#include "Inventory.h"
#include <algorithm>
void Inventory::AddItem(Item* item)
{
	mItems.push_back(item);
}

void Inventory::RemoveItem(Item* item)
{
	mItems.erase( std::remove_if(mItems.begin(), mItems.end(), [item](Item* i) {return i == item; }));
}

Item* Inventory::GetItem(Item* item)
{
	auto i = std::find_if(mItems.begin(), mItems.end(), [item](Item* i) {return i == item; });
	return *i;
}

std::vector<Item*> Inventory::GetContents()
{
	return mItems;
}
