#pragma once
#include <vector>
#include "Item.h"
class Inventory
{
public:
	void AddItem(Item* item);
	void RemoveItem(Item* item);
	Item* GetItem(Item* item);
	std::vector<Item*> GetContents();
private:
	std::vector<Item*> mItems;

};

