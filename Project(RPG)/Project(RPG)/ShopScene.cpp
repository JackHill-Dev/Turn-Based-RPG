#include "ShopScene.h"
#include "Sword.h"
#include "Armour.h"

ShopScene::ShopScene(ObjectManager* rng) : Scene(rng)
{
	SetupPlayerInv();
	SetupShopInv();

	AddObject("playerPortraitObj", 400, 100, Game);
	AddObject("merchantPortraitObj", 620, 100, Game);

	int gridOffset = 0; // current way of serparting them need them to form grid 
	for (auto i : mPlayer.GetInventory().GetContents())
	{
		i->SetRenderObject(*AddObject(i->GetObjName(), 0 + gridOffset, 0, Game)); // Display item to screen and set its render object to the correct image
		// if x > 5th grid postion on row 0
			// then add to y offset and reset x offset
		gridOffset += 30;
	}
}

void ShopScene::Update(double dTime, Act act, std::pair<int, int> mousePos)
{
	OutputInventories();
}

void ShopScene::SetupShopInv()
{
	Sword* longSword = new Sword("Long Sword", 50);
	Sword* shortSword = new Sword("Short Sword", 100);
	Sword* greatSword = new Sword("Great Sword", 500);

	mShop.GetInventory().AddItem(longSword);
	mShop.GetInventory().AddItem(shortSword);
	mShop.GetInventory().AddItem(greatSword);

}

void ShopScene::SetupPlayerInv()
{
	Sword* bigSword = new Sword("Big Sword", 50);
	bigSword->SetAtkPower(10);

	Sword* twitchSword = new Sword("Twitch Sword", 100);
	twitchSword->SetAtkPower(100);

	Sword* massiveSword = new Sword("Massive Sword", 500);
	massiveSword->SetAtkPower(500);

	Armour* plateArmour = new Armour("Plate Armour", 150);
	
	mPlayer.GetInventory().AddItem(bigSword);
	mPlayer.GetInventory().AddItem(twitchSword);
	mPlayer.GetInventory().AddItem(plateArmour);
	mPlayer.GetInventory().AddItem(massiveSword);
	

}

void ShopScene::OutputInventories()
{
	if (printOnce)
	{
		auto i = mPlayer.GetInventory().GetContents();
		std::cout << "Player inventory" << std::endl;
		for (Item* i : mPlayer.GetInventory().GetContents())
		{
			std::cout << i->GetName() << " " << i->GetCost() << std::endl;
		}

		std::cout << "Shop inventory" << std::endl;
		for (Item* i : mShop.GetInventory().GetContents())
		{
			std::cout << i->GetName() << " " << i->GetCost() << std::endl;
		}

		printOnce = false;
	}
}
