#include "Consumable.h"

Consumable::Consumable(std::string name,std::string spriteName, int lvlReq, int cost, int healAmount) : Item(name, lvlReq, cost)
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
	std::ostringstream desc;
	desc << "Name: " << mName << std::endl;
	desc << "Heals " << mHealAmount << " health" << std::endl;
	desc << "Lvl Req. " << mLevelRequirement;
	return desc.str();
}
