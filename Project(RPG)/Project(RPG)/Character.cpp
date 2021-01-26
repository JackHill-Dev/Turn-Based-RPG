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

void Character::UpdateCharacter()
{
	if (ArmourEquipSlot._item == nullptr)
	{
		mStats.movement = std::make_pair(5, 5);
		mStats.health = std::make_pair(15, 15);
	}
	Armour* armour = static_cast<Armour*>(ArmourEquipSlot._item);
	if(ArmourEquipSlot._item != nullptr)
	{
			mStats.movement = std::make_pair(4, 4);
			mStats.health.first += armour->defence;
			mStats.health.second += armour->defence;
	}
			
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