#pragma once
#include "Inventory.h"
#include "Character.h"
class Player
{
public:
	Player();
	~Player();
	
	int GetGold();
	Inventory& GetInventory();
	std::vector<Character*>& GetParty() { return mPartyMembers; }
	void SetInventory(Inventory inv);
	void SellItem(Item* item);
	void SetGold(int amount);
private:
	Inventory mInventory;
	std::vector<Character*> mPartyMembers;
	int mGold;
};

