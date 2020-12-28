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

	// Temporary variables for testing
	void SetupShopInv();
	void SetupPlayerInv();
	void OutputInventories();
	Player mPlayer;

	bool printOnce = true;
	

};

