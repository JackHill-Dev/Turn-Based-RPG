#include "ShopScene.h"
#include "Sword.h"


ShopScene::ShopScene(ObjectManager* rng) : Scene(rng)
{
	SetupPlayerInv();
	SetupShopInv();
}

void ShopScene::Update(double dTime, Act act, std::pair<int, int> mousePos)
{
	/*if (printOnce)
	{
		auto i = &mPlayer.GetInventory()->GetContents();
		std::cout << "Player inventory" << std::endl;
		for (Item* i : mPlayer.GetInventory()->GetContents())
		{
			std::cout << i->GetName() << " " << i->GetCost() << std::endl;
		}

		std::cout << "Shop inventory" << std::endl;
		for (Item* i : mShop.GetInventory()->GetContents())
		{
			std::cout << i->GetName() << " " << i->GetCost() << std::endl;
		}

		printOnce = false;
	}*/
}

void ShopScene::SetupShopInv()
{
	Sword longSword("Long Sword", 50);
	Sword shortSword("Short Sword", 100);
	Sword greatSword("Great Sword", 500);

	mShopInv.AddItem(&longSword);
	mShopInv.AddItem(&shortSword);
	mShopInv.AddItem(&greatSword);

	mShop.SetInventory(mShopInv);
}

void ShopScene::SetupPlayerInv()
{
	Sword bigSword("Big Sword", 50);
	Sword simpSword("simp Sword", 100);
	Sword massiveSword("Massive Sword", 500);
	

	mPlayerInv.AddItem(&bigSword);
	mPlayerInv.AddItem(&simpSword);
	mPlayerInv.AddItem(&massiveSword);

	mPlayer.SetInventory(mPlayerInv);
}
