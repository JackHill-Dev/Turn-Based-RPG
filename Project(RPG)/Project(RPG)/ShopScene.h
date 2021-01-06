#pragma once
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Scene.h"
#include "Shop.h"
#include "Player.h"
#include "Weapon.h"
#include "Armour.h"
#include "Consumable.h"

class ShopScene :
    public Scene
{
public:
	ShopScene(Interface* rng);
	void Init();
protected:
	void Update(double dTime, Act act, std::pair<int, int> mousePos) override;
private:
	
	Shop mShop;
	void PlaceItems(Inventory& inv);
	void SetupShopInv(); // For testing
	void SetupPlayerInv(); // For testing
	void ManageShopInventory(Inventory& inv, Act act, std::pair<int, int> mousePos);
	void ManagePlayerInventory(Inventory& inv, Act act, std::pair<int, int> mousePos);
	void GenerateGrids();
	void DrawGrid(int gridWidth, int gridHeight, int offsetX, int offsetY);

	Player mPlayer;
	UIText mPlayerGoldText;
	UIText mShopGoldText;
	Mix_Music* bg_Music;
	Mix_Chunk* buySell_SFX;
	bool startOnce = false;

	

};

