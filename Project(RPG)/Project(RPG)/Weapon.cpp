#include "Weapon.h"

Weapon::Weapon(std::string name, std::string spriteName, int lvlReq, int atk, int cost) : Item(name, lvlReq, cost)
{
	mType = WEAPON;
	mName = name;
	mAttackPower = atk;
	mObjName = spriteName;
	
}

int Weapon::GetAtkPower()
{
	return mAttackPower;
}



std::string Weapon::GetDescription()
{
	std::ostringstream desc; 
	desc << "Name: " << mName << std::endl;
	desc << "Atk Power: " << mAttackPower << std::endl;
	desc << "Cost: " << mCost;
	return desc.str();
}
