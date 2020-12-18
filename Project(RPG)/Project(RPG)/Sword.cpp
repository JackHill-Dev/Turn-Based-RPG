#include "Sword.h"

Sword::Sword(std::string name, int cost) : Item(name, cost)
{
}

int Sword::GetAtkPower()
{
	return mAttackPower;
}

void Sword::SetAtkPower(int atk)
{
	mAttackPower = atk;
}
