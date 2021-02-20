#pragma once
#include "Character.h"
#include "Card.h"
#include "Item.h"
#include <deque>
class Player
{
public:
	int currentNode = 0;
	Player();
	~Player();
	std::deque<Card*> deck;
	int GetGold();
	std::vector<Character*>& GetParty() { return mPartyMembers; }
	void SellItem(Item* item);
	void SetGold(int amount);
	void ClearGold() { mGold = 0; }
	void AddToXpPool(const int& xp);
	int& GetXpPool() { return mPartyExperiencePool; }
	void ClearXpPool() { mPartyExperiencePool = 0; }
	void GameCleared() { gameCleared = true; }
	bool GetGameCleared() { return gameCleared; }
	void AddToParty(Character* character);
	void SetupParty(std::vector<Character*> characters);
	void SetDeck(std::deque<Card*> newDeck)
	{
		deck = newDeck;
	}

	// Inventory related functions
	void AddItem(Item* item);
	void RemoveItem(Item* item);

	std::vector<Item*> inventory;
	// Shop position grid pos calculation
	void SetInitialGridPos(int pos);
	void GeneratePositions();
private:
	//Inventory mInventory;
	std::vector<Character*> mPartyMembers;
	int mPartyExperiencePool = 0;
	int mGold = 0;

	// Grid pos variables
	std::vector<std::pair<int, int>> gridPositions;
	int mInitialGridPos = 0;
	int mItemCount;
	bool gameCleared = false;

};

