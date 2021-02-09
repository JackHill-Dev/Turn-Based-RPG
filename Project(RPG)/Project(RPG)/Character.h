#pragma once
#include "Globals.h"
#include "RenderObject.h"
#include "Inventory.h"
#include "Armour.h"
#include "Weapon.h"
struct Statistics
{
	std::pair<int, int> health = { 15,15 }; // current, max
	std::pair<int, int> mana = { 10,10 };
	std::pair<int, int> agility = { 10,10 };
	std::pair<int, int> stamina = { 10,10 };
	std::pair<int, int> movement = { 5,5 };
};

class Character
{
public:
	int GetHealth();
	Statistics& GetStats() { return mStats; }
	Character() {}
	Character(std::string objectName, std::string portraitName);
	~Character();
	std::string GetPortraitName() { return mPortraitName; }
	std::string GetObjName() { return objectName; };
	void SetArmour(Armour* armour);
	void SetWeapon(Weapon* weapon);
	void UpdateCharacter();
	bool ModHealth(int mod);
	bool moving = false;
	Armour* ArmourEquipSlot;
	Weapon* mWeaponEquipSlot;
protected:
	Statistics mStats;
	std::string mPortraitName;
	std::string objectName;
	
	
	std::pair<double, double> target;
private:


};

