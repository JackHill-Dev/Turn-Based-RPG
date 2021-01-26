#pragma once
#include "Globals.h"
#include "RenderObject.h"
#include "Inventory.h"
#include "Armour.h"
struct Statistics
{
	std::pair<int, int> health = { 15,15 }; // max, current
	std::pair<int, int> mana = { 10,10 };
	std::pair<int, int> agility = { 10,10 };
	std::pair<int, int> stamina = { 10,10 };
	std::pair<int, int> movement = { 5,5 };
};
struct EquipSlot
{
	RenderObject* slotObj = nullptr;
	Item* _item = nullptr;
};
class Character
{
public:
	int GetHealth();
	Statistics& GetStats() { return mStats; }
	Inventory& GetInventory(){ return mInventory; }
	Character() {}
	Character(std::string objectName, std::string portraitName);
	~Character();
	std::string GetPortraitName() { return mPortraitName; }
	std::string GetObjName() { return objectName; };
	void SetArmour(Armour* armour) { ArmourEquipSlot._item = armour; }
	void UpdateCharacter();
	bool ModHealth(int mod);
	bool moving = false;
	EquipSlot ArmourEquipSlot;
protected:
	Statistics mStats;
	std::string mPortraitName;
	std::string objectName;
	RenderObject* object;
	
	std::pair<double, double> target;
private:
	Inventory mInventory;

};

