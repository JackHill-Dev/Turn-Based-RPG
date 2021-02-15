#include "Consumable.h"

Consumable::Consumable(std::string name,std::string spriteName, int cost) : Item(name, cost)
{
	ItemType::CONSUMABLE;
	mObjName = spriteName;
}

void Consumable::OnConsume()
{
}

std::string Consumable::GetDescription()
{
	return "Consumable tooltip";
}
