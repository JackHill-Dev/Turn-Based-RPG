#pragma once
#include "Inventory.h"
#include "Character.h"
#include "Card.h"
#include <deque>
class Player
{
public:
	Player();
	~Player();
	std::deque<Card*> deck;
	int GetGold();
	Inventory& GetInventory();
	std::vector<Character*>& GetParty() { return mPartyMembers; }
	void SetInventory(Inventory inv);
	void SellItem(Item* item);
	void SetGold(int amount);
	void SetupParty(std::vector<Character*> characters);
	void SetDeck(std::deque<Card*> newDeck)
	{
		deck = newDeck;
	}
private:
	Inventory mInventory;
	std::vector<Character*> mPartyMembers;
	int mGold;
};

