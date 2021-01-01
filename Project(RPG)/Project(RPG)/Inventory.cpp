#include "Inventory.h"
#include <algorithm>
Inventory::Inventory()
{
	gridPositions.reserve(1000);
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
		// for each item currently in inventory
	for (Item* i : mItems)
	{
		for (auto p : gridPositions)
		{
			if (item->inventoryPos.gridPosFilled == false)
			{
				item->inventoryPos.pos = p;
				item->inventoryPos.gridPosFilled = true;
				gridPositions.erase(std::remove(gridPositions.begin(), gridPositions.end(), p));
			}
		}
		
	}
	// if i->invPos->GridPosFilled is false
		// then item->invPos->Pos = i->invPos->pos
			// item->GetRenderObject()->SetPos(item->invPos->pos)

	
	
	//Update inventory item count for save data
	mItemCount = mItems.size();
}

void Inventory::RemoveItem(Item* item)
{
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
	int offsetY = 90;

	for (int i = 0; i < gridPositions.capacity(); ++i)
	{
		gridPositions.push_back(std::make_pair(0, 0));
	}

	for (std::pair<int,int>& p : gridPositions)
	{

		if (offsetX >= 360 + mInitialGridPos)
		{
			offsetX = mInitialGridPos;
			offsetY += 90;
		}

		p.first = offsetX;
		p.second = offsetY;

		offsetX += 90;
	}


}
