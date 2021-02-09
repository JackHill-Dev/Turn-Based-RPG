#include "Inventory.h"
#include <algorithm>
Inventory::Inventory()
{
	gridPositions.reserve(100);
	//GeneratePositions();
}
Inventory::~Inventory()
{
	for (Item* i : mItems)
	{
		delete i;
	}
}
void Inventory::AddItem(Item* item)
{
	// Add item to inventory
	mItems.push_back(item);

	// Assign inventory position 
	for (auto p : gridPositions)
	{
		if (item->inventoryPos.gridPosFilled == false)
		{
			item->inventoryPos.pos = p; // Set the item's inventory position to a free grid slot
			item->inventoryPos.gridPosFilled = true; // Make the grid position unavaliable
			 // Remove it from the current grid positions otherwise it will assgin the first grid pos for every item
			gridPositions.erase(std::remove(gridPositions.begin(), gridPositions.end(), p));
		}
	}
		
	
	//Update inventory item count for save data
	mItemCount = mItems.size();
}

void Inventory::RemoveItem(Item* item)
{
	// Free up grid position and add it back to the grid positions
	gridPositions.insert(gridPositions.begin(), item->inventoryPos.pos);

	item->inventoryPos.gridPosFilled = false;

	mItems.erase(std::remove_if(mItems.begin(), mItems.end(), [item](Item* i) {return i == item; }));

	//Update inventory item count for save data
	mItemCount = mItems.size();
}

Item* Inventory::GetItem(Item* item)
{
	auto i = std::find_if(mItems.begin(), mItems.end(), [item](Item* i) {return i == item; });
	return *i;
}

std::vector<Item*>& Inventory::GetContents()
{
	return mItems;
}

void Inventory::SetInitialGridPos(int pos)
{
	mInitialGridPos = pos;
}

void Inventory::GeneratePositions()
{
	int offsetX = mInitialGridPos;
	int offsetY = 100;

	for (int i = 0; i < gridPositions.capacity(); ++i)
	{
		gridPositions.push_back(std::make_pair(0, 0));
	}

	for (std::pair<int,int>& p : gridPositions)
	{

		if (offsetX >= 360 + mInitialGridPos)
		{
			offsetX = mInitialGridPos;
			offsetY += 110;
		}
		
		p.first = offsetX;
		p.second = offsetY;

		offsetX += 90;
	}


}
