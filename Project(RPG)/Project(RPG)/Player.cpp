#include "Player.h"

Player::Player()
{
	mInventory.SetInitialGridPos(10);
}

Player::~Player()
{
}

void Player::SetGold(int amount)
{
	mGold += amount;
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
	mGold += item->GetCost();
	mInventory.RemoveItem(item);

}
