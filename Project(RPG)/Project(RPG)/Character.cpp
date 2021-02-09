#include "Character.h"

Character::Character(std::string objectName, std::string portraitName)
{
	this->objectName = objectName;
	mPortraitName = portraitName;
}

Character::~Character()
{
	//delete object;
	//object = nullptr;
}	


int Character::GetHealth()
{
	return mStats.health.first;
}

void Character::SetArmour(Armour* armour)
{
	
	if (armour != nullptr)
	{
		mStats.health.first += armour->defence;
		mStats.health.second += armour->defence;
	}
	else
	{
		mStats.health.first -= ArmourEquipSlot->defence;
		mStats.health.second -= ArmourEquipSlot->defence;
	}
	ArmourEquipSlot = armour;

}

void Character::SetWeapon(Weapon* weapon)
{
	
	if (weapon != nullptr)
	{
		mStats.agility.first += weapon->GetAtkPower();
		mStats.agility.second += weapon->GetAtkPower();
	}

	else
	{
		mStats.agility.first -= mWeaponEquipSlot->GetAtkPower();
		mStats.agility.second -= mWeaponEquipSlot->GetAtkPower();
	}


	mWeaponEquipSlot = weapon;
}

void Character::UpdateCharacter()
{
	/*Armour* armour = static_cast<Armour*>(ArmourEquipSlot._item);
	Weapon* weapon = static_cast<Weapon*>(mWeaponEquipSlot._item);
	if (ArmourEquipSlot._item == nullptr)
	{
		mStats.movement = std::make_pair(5, 5);
		mStats.health = std::make_pair(15, 15);
	}
	if (mWeaponEquipSlot._item == nullptr)
	{
		mStats.agility = std::make_pair(10, 10);
	}*/

	/*if(ArmourEquipSlot._item != nullptr)
	{
			mStats.movement = std::make_pair(4, 4);
			mStats.health.first += armour->defence;
			mStats.health.second += armour->defence;
	}

	if (mWeaponEquipSlot.slotObj != nullptr)
	{
		mStats.agility.first += weapon->GetAtkPower();
		mStats.agility.second += weapon->GetAtkPower();
	}*/
	
}

bool Character::ModHealth(int mod)
{
	mStats.health.first -= mod;
	if (mStats.health.first > mStats.health.second)
		mStats.health.first = mStats.health.second;
	else
		if (mStats.health.first <= 0)
			return false;
	return true;
}