#pragma once
#include "Scene.h"

class InventoryScene :
    public Scene
{
public:
	InventoryScene(Interface* mgr);
	~InventoryScene();
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
	Mix_Chunk* button_SFX;
	ToolTip mToolTip;
	std::vector<RenderObject*> playerInvGrid;
	std::vector<ItemObject> itemObjects;
	std::vector<Character*> mParty;

};

