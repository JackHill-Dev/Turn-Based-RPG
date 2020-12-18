#include "Player.h"

void Player::SetGold(int amount)
{
	mGold += amount;
}

int Player::GetGold()
{
	return mGold;
}

Inventory* Player::GetInventory()
{
	return &mInventory;
}

void Player::SetInventory(Inventory& inv)
{
	mInventory = inv;
}

void Player::SellItem(Item* item)
{
	mGold += item->GetCost();
	mInventory.RemoveItem(item);

}
