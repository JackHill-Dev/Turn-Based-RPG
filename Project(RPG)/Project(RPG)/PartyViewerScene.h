#pragma once
#include "Scene.h"

struct CharacterCard
{
	UIText stamina;
	UIText health;
	UIText mana;
	UIText agility;
	UIText movement;
};

struct ItemObject
{
	Item* _item;
	RenderObject* obj;

	ItemObject(Item* i, RenderObject* r) : _item(i), obj(r) {}
};

class PartyViewerScene :
    public Scene
{
public:
	PartyViewerScene(Interface* mgr);
	void Load();
protected:
	void Update(double dTime, Act act, std::pair<int, int> mousePos) override;
private:
	RenderObject* mCloseBtn;
	std::vector<ItemObject> itemObjects;
	void Init();

	void GetCharacterPortraits();
	void GetCharacterStatistics();
	void HandleArmourEquip(ItemObject& i, Character& c);
	void HandleWeaponEquip(ItemObject& i, Character& c);

	std::vector<RenderObject*> DrawGrid(int gridWidth, int gridHeight, int offsetX, int offsetY, int gridBoundsX);
	UIText DrawStat(std::string statName, int stat, SDL_Color textColor, std::pair<int,int> pos);
	std::vector<Character*> mParty;

	// Temp
	std::vector<RenderObject*> playerInvGrid;
	//RenderObject* armourEquipSlot;

};

