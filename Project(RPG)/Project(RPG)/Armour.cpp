#include "Armour.h"
Armour::Armour(std::string name, std::string spriteName,  int def,int cost) : Item(name, cost)
{
	mType = ARMOUR;
	mName = name;
	defence = def;
	mObjName = spriteName;
}

std::string Armour::GetDescription()
{
	std::ostringstream desc;
	desc << "Name: " << mName << std::endl;
	desc << "Defence: " << defence << std::endl;
	desc << "Cost: " << mCost;

	return desc.str();
}

