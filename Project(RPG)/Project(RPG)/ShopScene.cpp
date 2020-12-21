#include "ShopScene.h"
#include "Sword.h"


ShopScene::ShopScene(ObjectManager* rng) : Scene(rng)
{
	SetupPlayerInv();
	SetupShopInv();
}

void ShopScene::Update(double dTime, Act act, std::pair<int, int> mousePos)
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
	
	mPlayer.GetInventory().AddItem(bigSword);
	mPlayer.GetInventory().AddItem(twitchSword);
	mPlayer.GetInventory().AddItem(massiveSword);

}
