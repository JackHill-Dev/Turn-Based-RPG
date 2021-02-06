#include "Armour.h"

Armour::Armour(std::string name, int cost, int def) : Item(name, cost)
{
	defence = def;
	mType = ARMOUR;
	mObjName = "armourObj";
}

std::string Armour::GetDescription()
{
	return "Armour tooltip";
}
