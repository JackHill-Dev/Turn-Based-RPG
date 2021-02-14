#include "Player.h"

Player::Player()
{
	// Workaround for shop grid positioning until i rework it - JP
	mInventory.SetInitialGridPos(80);
	mInventory.GeneratePositions();
}

Player::~Player()
{
	for (Character* c : mPartyMembers)
	{
		delete c;
		c = nullptr;
	}
}

void Player::SetGold(int amount)
{
	mGold += amount;
}

void Player::AddToXpPool(int& xp)
{
	mPartyExperiencePool += xp;
}

void Player::AddToParty(Character* character)
{
	GetParty().push_back(character);
}

void Player::SetupParty(std::vector<Character*> characters)
{
	mPartyMembers = characters;
}

int Player::GetGold()
{
	return mGold;
}

Inventory& Player::GetInventory()
{
	return mInventory;
}

// Currently loses item data, don't use until fixed, instead just add straight to inventory - JP
void Player::SetInventory(Inventory inv)
{
	mInventory = inv;
}

void Player::SellItem(Item* item)
{
	SetGold(item->GetCost());
	mInventory.RemoveItem(item);

}
