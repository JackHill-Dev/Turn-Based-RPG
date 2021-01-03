#pragma once
#include "Scene.h"
#include "Shop.h"
#include "Player.h"
#include "AudioManager.h"
#include <SDL_mixer.h>
class ShopScene :
    public Scene
{
public:
	ShopScene(ObjectManager* rng);
	void Init();
protected:
	void Update(double dTime, Act act, std::pair<int, int> mousePos) override;
private:
	
	Shop mShop;
	void PlaceItems(Inventory& inv);
	
	// Temporary variables for testing
	void SetupShopInv();
	void SetupPlayerInv();
	void ManageShopInventory(Inventory& inv, Act act, std::pair<int, int> mousePos);
	void ManagePlayerInventory(Inventory& inv, Act act, std::pair<int, int> mousePos);
	void GenerateGrids();
	void DrawGrid(int gridWidth, int gridHeight, int offsetX, int offsetY);
	Player mPlayer;
	Mix_Music* bg_Music;
	Mix_Chunk* buySell_SFX;
	bool startOnce = false;

	

};

