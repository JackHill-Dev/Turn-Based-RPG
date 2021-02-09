#include "Consumable.h"

Consumable::Consumable(std::string name, int cost) : Item(name, cost)
{
	mObjName = "potionObj";
}

void Consumable::OnConsume()
{
}

std::string Consumable::GetDescription()
{
	return "Consumable tooltip";
}
