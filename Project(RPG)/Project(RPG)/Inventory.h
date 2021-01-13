#pragma once
#include <vector>
#include "Item.h"
class Inventory
{
public:
	Inventory();
	~Inventory();
	void AddItem(Item* item);
	void RemoveItem(Item* item);
	Item* GetItem(Item* item);
	std::vector<Item*>& GetContents();

	void SetInitialGridPos(int pos);
	void GeneratePositions();
private:

	std::vector<Item*> mItems;
	std::vector<std::pair<int, int>> gridPositions;
	int mInitialGridPos = 0;
	int mItemCount;

};

