#pragma once
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Scene.h"
#include "Shop.h"
#include "Player.h"
#include "Weapon.h"
#include "Armour.h"
#include "Consumable.h"

struct ItemObjects
{
	Item* _item;
	RenderObject* obj;

	ItemObjects() {}
	ItemObjects(Item* i, RenderObject* r) : _item(i), obj(r) {}
};

class ShopScene :
    public Scene
{
public:
	ShopScene(Interface* rng);
	void Init();
	void Load();
protected:
	void Update(double dTime, Act act, std::pair<int, int> mousePos) override;
private:
	

	void PlaceItems(Inventory& inv);
	void SetupShopInv(); // For testing
	void ManageShopInventory(Inventory& inv, Act act, std::pair<int, int> mousePos);
	void ManagePlayerInventory(Inventory& inv, Act act, std::pair<int, int> mousePos);
	void GenerateGrids();
	void DrawGrid(int gridWidth, int gridHeight, int offsetX, int offsetY);
	void HandleTooltip();

	Shop mShop;
	UIText mPlayerGoldText;
	UIText mShopGoldText;
	Mix_Music* bg_Music;
	Mix_Chunk* buySell_SFX;
	Mix_Chunk* button_Click_SFX;
	Mix_Chunk* leave_SFX;
	RenderObject* pExitButton;
	ToolTip mTooltip;
	Item* current = nullptr;
	bool startOnce = false;

	//Temp
	int RandomRange(int min, int max);	
	std::vector<ItemObjects> playerInv;
	std::vector<ItemObjects> shopInv;
};

