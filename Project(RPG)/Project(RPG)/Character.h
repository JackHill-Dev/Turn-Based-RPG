#pragma once
#include "Globals.h"
#include "RenderObject.h"
#include "Inventory.h"
#include "Armour.h"
#include "Weapon.h"

struct Statistics
{
	int level;
	std::pair<int, int> health = { 15,15 }; // current, max
	std::pair<int, int> intelligence = { 10,10 };
	std::pair<int, int> agility = { 10,10 };
	std::pair<int, int> strength = { 10,10 };
	std::pair<int, int> movement = { 5,5 };
	std::pair<int, int> experience = { 0, 100 }; // current, next level - EH
};

struct EquipSlot
{
	RenderObject* slotObj = nullptr;
	Item* _item = nullptr;
};

class Character
{
public:

	Character() {}
	Character(std::string objectName, std::string portraitName);
	~Character();

	int GetLevel();
	int GetHealth();
	Statistics& GetStats() { return mStats; }
	std::string GetPortraitName() { return mPortraitName; }
	std::string GetObjName() { return objectName; };


	void modStat(std::pair<int, int> statToMod, int statMod);
	void LevelUp(int level, std::pair<int, int> characterHealth);

	void SetArmour(Armour* armour);
	void SetWeapon(Weapon* weapon);
	void UpdateCharacter();

	bool ModHealth(int mod);
	void Heal(std::pair<int,int> health, int healValue);
	
	
	bool moving = false;
	EquipSlot ArmourEquipSlot;
	EquipSlot mWeaponEquipSlot;

protected:

	Statistics mStats;
	std::string mPortraitName;
	std::string objectName;
	RenderObject* object;
	std::pair<double, double> target;

private:

	const int levelHealth = 10;

};

