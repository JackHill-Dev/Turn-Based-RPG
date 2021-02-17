#include "Character.h"

Character::Character(std::string portraitName, std::string objectName, std::string name, int level, std::pair<int, int> experience, bool isDead, std::pair<int, int> health, std::pair<int, int> strength, std::pair<int, int> intelligence, std::pair<int, int> agility)
{
	mPortraitName = portraitName;
	this->objectName = objectName;
	mStats.health = health;
	mStats.strength = strength;
	mStats.agility = agility;
	mStats.intelligence = intelligence;

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

std::string Character::GetClassName(UnitClass uClass)
{
	switch (uClass)
	{
		case UnitClass::Mage:
			return "MAGE";
			break;
		case UnitClass::Rogue:
			return "ROGUE";
			break;
		case UnitClass::Warrior:
			return "WARRIOR";
			break;
		default:
			return "MAI'Q THE LIAR";
	}
}

void Character::modStat(std::pair<int, int>& statToMod, std::pair<int,int> statMod)
{
	statToMod.first += statMod.first;
	statToMod.second += statMod.second;
}

void Character::LevelUp(int level, std::pair<int, int> characterHealth)
{
	++level;
	mStats.experience.second *= 2; //Temp change to required experience for next level.
	hasLevelled = false;
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
	// Changes status of defeated characters - EH
	if (isDead)
	{
		isDead = false;
	}

	health.first += healValue;

	if (health.first > health.second)
	{
		health.first = health.second;
	}
}

void Character::Die()
{
	// Health of character is reduced to one to penalise player letting characters die, no permadeath but you'll need to buy potions and heal your units - EH
	mStats.health.first = 1;

	isDead = true;
}

