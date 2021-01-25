#include "Armour.h"

Armour::Armour(std::string name, int cost, int def) : Item(name, cost)
{
	defence = def;
	mObjName = "armourObj";
}
