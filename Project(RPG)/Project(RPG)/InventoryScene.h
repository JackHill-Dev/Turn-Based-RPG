#pragma once
#include "Scene.h"

struct ItemObject
{
	Item* _item;
	RenderObject* obj;

	ItemObject(Item* i, RenderObject* r) : _item(i), obj(r) {}
};

class InventoryScene :
    public Scene
{
public:
	InventoryScene(Interface* mgr);
	void Load();
protected:
	void Update(double dTime, Act act, std::pair<int, int> mousePos) override;
private:
	void GetCharacterPortraits();
	void Init();
	void HandleArmourEquip(ItemObject& i, Character& c);
	void HandleWeaponEquip(ItemObject& i, Character& c);
	std::vector<RenderObject*> DrawGrid(int gridWidth, int gridHeight, int offsetX, int offsetY, int gridBoundsX);
private:
	RenderObject* pCloseBtn;

	std::vector<RenderObject*> playerInvGrid;
	std::vector<ItemObject> itemObjects;
	std::vector<Character*> mParty;
};

