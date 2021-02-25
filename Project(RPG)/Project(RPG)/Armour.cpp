#include "Armour.h"
Armour::Armour(std::string name, std::string spriteName, int lvlReq, int def,int cost) : Item(name, lvlReq, cost)
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
	desc << "Health + " << defence << std::endl;
	desc << "Lvl Req. " << mLevelRequirement << std::endl;
	desc << "Cost: " << mCost;

	return desc.str();
}

