#include "Character.h"

Character::Character(std::string objectName, std::string portraitName, std::pair<int, int> health, std::pair<int, int> strength, std::pair<int, int> intelligence, std::pair<int, int> agility)
{
	mStats.health = health;
	mStats.strength = strength;
	mStats.agility = agility;
	mStats.intelligence = intelligence;
	this->objectName = objectName;
	mPortraitName = portraitName;
}

Character::~Character()
{
	//delete object;
	//object = nullptr;
}	


int Character::GetLevel()
{
	return mStats.level;
}

int Character::GetHealth()
{
	return mStats.health.first;
}

void Character::modStat(std::pair<int, int>& statToMod, std::pair<int,int> statMod)
{
	statToMod.first += statMod.first;
	statToMod.second += statMod.second;
}

void Character::LevelUp(int level, std::pair<int, int> characterHealth)
{
	++level;
	characterHealth.first += levelHealth;
	characterHealth.second += levelHealth;
}

void Character::SetBackground(UnitBackground background)
{
	mStats.bg = background;
}

void Character::SetClass(UnitClass uClass)
{
	mStats.cClass = uClass;
}

void Character::SetArmour(Armour* armour)
{
	ArmourEquipSlot._item = armour;
	if (armour != nullptr)
	{
		mStats.health.first += armour->defence;
		mStats.health.second += armour->defence;
	}

}

void Character::SetWeapon(Weapon* weapon)
{
	mWeaponEquipSlot._item = weapon;
	if (weapon != nullptr)
	{
		mStats.agility.first += weapon->GetAtkPower();
		mStats.agility.second += weapon->GetAtkPower();
	}
}

void Character::UpdateCharacter()
{
	Armour* armour = static_cast<Armour*>(ArmourEquipSlot._item);
	Weapon* weapon = static_cast<Weapon*>(mWeaponEquipSlot._item);

	if (ArmourEquipSlot._item == nullptr)
	{
		mStats.movement = std::make_pair(5, 5);
		mStats.health = std::make_pair(15, 15);
	}
	if (mWeaponEquipSlot._item == nullptr)
	{
		mStats.agility = std::make_pair(10, 10);
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

void Character::Heal(std::pair<int, int>& health, int healValue)
{
	health.first += healValue;

	if (health.first > health.second)
	{
		health.first = health.second;
	}
}

