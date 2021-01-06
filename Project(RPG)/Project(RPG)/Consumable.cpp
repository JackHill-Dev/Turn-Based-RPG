#include "Consumable.h"

Consumable::Consumable(std::string name, int cost) : Item(name, cost)
{
	SetObjName("potionObj");
}

void Consumable::OnConsume()
{
}
