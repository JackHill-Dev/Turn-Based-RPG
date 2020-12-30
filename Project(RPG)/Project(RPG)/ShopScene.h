#pragma once
#include "Scene.h"
#include "Shop.h"
#include "Player.h"

class ShopScene :
    public Scene
{
public:
	ShopScene(ObjectManager* rng);
protected:
	void Update(double dTime, Act act, std::pair<int, int> mousePos) override;
private:
	
	Shop mShop;
	void PlaceItems(Inventory& inv, int startX);
	// Temporary variables for testing
	void SetupShopInv();
	void SetupPlayerInv();
	void OutputInventories();
	void ManageShopInventory(Inventory& inv, Act act, std::pair<int, int> mousePos);
	void ManagePlayerInventory(Inventory& inv, Act act, std::pair<int, int> mousePos);
	Player mPlayer;

	bool printOnce = true;
	

};

