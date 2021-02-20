#include "Consumable.h"

Consumable::Consumable(std::string name,std::string spriteName, int cost, int healAmount) : Item(name, cost)
{
	mType = ItemType::CONSUMABLE;
	mObjName = spriteName;
	mHealAmount = healAmount;
}

void Consumable::OnConsume()
{
}

std::string Consumable::GetDescription()
{
	return "Consumable tooltip";
}
