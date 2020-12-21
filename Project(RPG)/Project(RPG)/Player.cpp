#include "Player.h"

Player::Player()
{
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

// Currently lose item data, don't use until fixed, instead just add straight to inventory
void Player::SetInventory(Inventory inv)
{
	mInventory = inv;
}

void Player::SellItem(Item* item)
{
	mGold += item->GetCost();
	mInventory.RemoveItem(item);

}
