#include "ShopScene.h"
#include "Weapon.h"
#include "Armour.h"
#include "Consumable.h"

ShopScene::ShopScene(ObjectManager* rng) : Scene(rng)
{
	bg_Music = Mix_LoadMUS("Assets/Music/MedievalLoop.mp3");
	buySell_SFX = Mix_LoadWAV("Assets/SFX/coin.wav");
}

void ShopScene::Update(double dTime, Act act, std::pair<int, int> mousePos)
{
	// Uncomment to hear the shop music, currently disabled as it was getting annoying while testing  - JP
	/*if (!startOnce)
	{
		mgr->GetManagers()->AudioMgr->PlayMusic(bg_Music, -1);
		startOnce = true;
	}*/

	ManagePlayerInventory(mPlayer.GetInventory(), act, mousePos);
	ManageShopInventory(mShop.GetInventory(), act, mousePos);
}

void ShopScene::PlaceItems(Inventory& inv)
{
	for (auto i : inv.GetContents())
	{
		// Display item to screen and set its render object to the correct image
		i->SetRenderObject(AddObject(i->GetObjName(), i->inventoryPos.pos.first, i->inventoryPos.pos.second, Game)); 
	}
}

void ShopScene::Init()
{
	AddObject("ShopBGObj", 0, 0, Background);
	AddObject("playerPortraitObj", 400, 100, UI);
	AddObject("merchantPortraitObj", 620, 100, UI);

	GenerateGrids();
	DrawGrids();

}

void ShopScene::SetupShopInv()
{
	Weapon* longSword = new Weapon("Long Sword", 50);
	Weapon* shortSword = new Weapon("Short Sword", 100);
	Weapon* greatSword = new Weapon("Great Sword", 500);
	Consumable* healthPotion = new Consumable("health potion", 25);
	Consumable* healthPotion2 = new Consumable("health potion", 25);

	mShop.GetInventory().AddItem(longSword);
	mShop.GetInventory().AddItem(shortSword);
	mShop.GetInventory().AddItem(greatSword);
	mShop.GetInventory().AddItem(healthPotion2);

}

void ShopScene::SetupPlayerInv()
{
	Weapon* bigSword = new Weapon("Big Sword", 50);
	bigSword->SetAtkPower(10);

	Weapon* twitchSword = new Weapon("Twitch Sword", 100);
	twitchSword->SetAtkPower(100);

	Weapon* massiveSword = new Weapon("Massive Sword", 500);
	massiveSword->SetAtkPower(500);

	Armour* plateArmour = new Armour("Plate Armour", 150);
	Armour* platArmour = new Armour("Plat Armour", 150);
	
	mPlayer.GetInventory().AddItem(bigSword);
	mPlayer.GetInventory().AddItem(twitchSword);
	mPlayer.GetInventory().AddItem(massiveSword);
	mPlayer.GetInventory().AddItem(plateArmour);
	mPlayer.GetInventory().AddItem(platArmour);

}


void ShopScene::ManageShopInventory(Inventory& inv, Act act, std::pair<int, int> mousePos)
{
	for (Item* i : inv.GetContents())
	{
		// check if mouse is hovering over it
		if (act == Act::MouseUpdate )
		{
			if (i->GetRenderObject()->InBounds(mousePos.first, mousePos.second))
				i->OnHover();
			else
				i->OnLeave();

		}
		
		if (act == Act::RClick && i->GetRenderObject()->InBounds(mousePos.first, mousePos.second))
		{
			if (!(mPlayer.GetGold() < i->GetCost())) // If player can't afford item they can't buy it
			{
				mShop.BuyItem(i);
				mPlayer.GetInventory().AddItem(i);
				mgr->GetManagers()->AudioMgr->PlaySFX(buySell_SFX, 0, 0);
				i->GetRenderObject()->SetPos(i->inventoryPos.pos);
				mPlayer.SetGold(-i->GetCost());
			}

		}
	}
	
}

void ShopScene::ManagePlayerInventory(Inventory& inv, Act act, std::pair<int, int> mousePos)
{
	// for each item in player's inventory on screen
	for (Item* i : mPlayer.GetInventory().GetContents())
	{
		// check if mouse is hovering over it
		if (act == Act::MouseUpdate)
		{
			if (i->GetRenderObject()->InBounds(mousePos.first, mousePos.second))
				i->OnHover();
			else
				i->OnLeave();
			
		}
		
		if (act == Act::RClick && i->GetRenderObject()->InBounds(mousePos.first, mousePos.second))
		{
			mPlayer.SellItem(i);
			mShop.GetInventory().AddItem(i);
			mgr->GetManagers()->AudioMgr->PlaySFX(buySell_SFX, 0, 1);
			i->GetRenderObject()->SetPos(i->inventoryPos.pos);
		}
	}

}

void ShopScene::GenerateGrids()
{
	mPlayer.GetInventory().SetInitialGridPos(10);
	mShop.GetInventory().SetInitialGridPos(850);

	mPlayer.GetInventory().GeneratePositions();
	mShop.GetInventory().GeneratePositions();

	SetupPlayerInv();
	SetupShopInv();

	PlaceItems(mPlayer.GetInventory());
	PlaceItems(mShop.GetInventory());
}

void ShopScene::DrawGrids()
{
	for (auto i : mPlayer.GetInventory().GetContents())
	{
		AddObject("itemFrameObj", i->inventoryPos.pos.first, i->inventoryPos.pos.second , Background);
	}

	for (auto i : mShop.GetInventory().GetContents())
	{
		AddObject("itemFrameObj", i->inventoryPos.pos.first, i->inventoryPos.pos.second, Background);
	}
}

