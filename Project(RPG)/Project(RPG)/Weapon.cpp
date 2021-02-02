#include "Weapon.h"

Weapon::Weapon(std::string name, int cost) : Item(name, cost)
{
	mType = WEAPON;
	SetObjName("swordObj");
}

int Weapon::GetAtkPower()
{
	return mAttackPower;
}

void Weapon::SetAtkPower(int atk)
{
	mAttackPower = atk;
}
