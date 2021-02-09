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
	std::deque<Item*> inventory;
	std::vector<Character*>& GetParty() { return mPartyMembers; }
	int mGold;
	void AddToParty(Character* character);
	void SetupParty(std::vector<Character*> characters);
	void SetDeck(std::deque<Card*> newDeck)
	{
		deck = newDeck;
	}
	std::vector<Character*> mPartyMembers;
};

