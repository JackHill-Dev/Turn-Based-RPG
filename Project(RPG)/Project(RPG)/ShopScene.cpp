#include "ShopScene.h"
#include "Sword.h"
#include "Armour.h"

ShopScene::ShopScene(ObjectManager* rng) : Scene(rng)
{
	SetupPlayerInv();
	SetupShopInv();

	AddObject("playerPortraitObj", 400, 100, UI);
	AddObject("merchantPortraitObj", 620, 100, UI);

	PlaceItems(mPlayer.GetInventory(), 10);
	PlaceItems(mShop.GetInventory(), 850);

}

void ShopScene::Update(double dTime, Act act, std::pair<int, int> mousePos)
{
	ManagePlayerInventory(mPlayer.GetInventory(), act, mousePos);
	ManageShopInventory(mShop.GetInventory(), act, mousePos);

	
}

void ShopScene::PlaceItems(Inventory& inv, int startX)
{
	int gridOffsetX = startX; // current way of serparting them need them to form grid 
	int gridOffsetY = 0;
	for (auto i : inv.GetContents())
	{
		// if x > 4th grid postion on row 0
		if (gridOffsetX >= 360 + startX)
		{
			gridOffsetX = startX; // reset x offset
			gridOffsetY += 90; // move y offset down
		}

		i->SetRenderObject(*AddObject(i->GetObjName(), 10 + gridOffsetX, 100 + gridOffsetY, Game)); // Display item to screen and set its render object to the correct image

		// then add to y offset and reset x offset
		gridOffsetX += 90;
	}
}

// Clear items from screen and redraw items with updated inventories 
void ShopScene::UpdateItems()
{
	ClearGameObjects();
	PlaceItems(mPlayer.GetInventory(), 10);
	PlaceItems(mShop.GetInventory(), 850);
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
	mPlayer.GetInventory().AddItem(massiveSword);
	mPlayer.GetInventory().AddItem(plateArmour);

	

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

void ShopScene::ManageShopInventory(Inventory& inv, Act act, std::pair<int, int> mousePos)
{
	for (Item* i : inv.GetContents())
	{
		// check if mouse is hovering over it
		if (act == Act::MouseUpdate && i->GetRenderObject()->InBounds(mousePos.first, mousePos.second))
		{
			// call onHover on item
			//i->OnHover();
		}

		if (act == Act::RClick && i->GetRenderObject()->InBounds(mousePos.first, mousePos.second))
		{
			if (!(mPlayer.GetGold() < i->GetCost())) // If player can't afford item they can't buy it
			{
				mShop.BuyItem(i);
				mPlayer.GetInventory().AddItem(i);
				mPlayer.SetGold(-i->GetCost());
			}

		}
		UpdateItems();
	}
	

}

void ShopScene::ManagePlayerInventory(Inventory& inv, Act act, std::pair<int, int> mousePos)
{
	// for each item in player's inventory on screen
	for (Item* i : mPlayer.GetInventory().GetContents())
	{
		// check if mouse is hovering over it
		if (act == Act::MouseUpdate && i->GetRenderObject()->InBounds(mousePos.first, mousePos.second))
		{
			// call onHover on item
			//i->OnHover();
		}
		
		if (act == Act::RClick && i->GetRenderObject()->InBounds(mousePos.first, mousePos.second))
		{
			mShop.GetInventory().AddItem(i);
			mPlayer.SellItem(i);
			
		}
		UpdateItems();
	}
	

}

