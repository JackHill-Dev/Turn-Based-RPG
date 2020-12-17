#pragma once
#include <vector>
#include "Item.h"
class Inventory
{
public:
	void AddItem(Item* item);
	void RemoveItem(Item* item);

	Item* GetItem(Item& item);

private:
	std::vector<Item*> mItems;
};

