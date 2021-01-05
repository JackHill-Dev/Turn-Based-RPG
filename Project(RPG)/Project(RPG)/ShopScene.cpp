#include "ShopScene.h"



ShopScene::ShopScene(ObjectManager* rng) : Scene(rng)
{
	bg_Music = Mix_LoadMUS("Assets/Music/MedievalLoop.mp3");
	buySell_SFX = Mix_LoadWAV("Assets/SFX/coin.wav");

	Mix_Volume(1, 5);

	mShop.SetGold(2000);

	
}

void ShopScene::Update(double dTime, Act act, std::pair<int, int> mousePos)
{
	// Uncomment to hear the shop music, currently disabled as it was getting annoying while testing  - JP
	/*if (!startOnce)
	{
		mgr->GetManagers()->AudioMgr->PlayMusic(bg_Music, -1);
		Mix_VolumeMusic(10);
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
	AddObject("ShopBGObj", 1280 / 2, 720 / 2, Background);
	AddObject("playerPortraitObj", 505, 225, UI);
	AddObject("merchantPortraitObj", 725, 225, UI);

	
	GenerateGrids();

	
	mPlayerGoldText.text = "Gold: " + std::to_string( mPlayer.GetGold());
	mPlayerGoldText.pos = std::make_pair(520, 385);
	mPlayerGoldText.textColor = SDL_Color{ 255, 215, 0 }; // Gold

	mShopGoldText.text = "Gold: " + std::to_string(mShop.GetGold());
	mShopGoldText.pos = std::make_pair(620, 385);
	mShopGoldText.textColor = SDL_Color{ 255, 215, 0 }; // Gold
	
	mSceneText["PlayerGoldText"] = mPlayerGoldText;
	mSceneText["ShopGoldText"] = mShopGoldText;

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
				mPlayer.SetGold(-i->GetCost());
				mPlayer.GetInventory().AddItem(i);
				mgr->GetManagers()->AudioMgr->PlaySFX(buySell_SFX, 0, 1);
				i->GetRenderObject()->SetPos(i->inventoryPos.pos);
				mSceneText["PlayerGoldText"].text = "Gold: " + std::to_string(mPlayer.GetGold());;
				mSceneText["ShopGoldText"].text = "Gold: " + std::to_string(mShop.GetGold());;
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
			if (!(mShop.GetGold() < i->GetCost())) // Can only sell to the shop if the shop can give you the moeny for the item
			{
				mPlayer.SellItem(i);
				mShop.SetGold(-i->GetCost());
				mShop.GetInventory().AddItem(i);
				mgr->GetManagers()->AudioMgr->PlaySFX(buySell_SFX, 0, 1); // Play buy sfx on channel 1 and don't loop
				i->GetRenderObject()->SetPos(i->inventoryPos.pos); // Update the render object position 
				mSceneText["PlayerGoldText"].text = "Gold: " + std::to_string(mPlayer.GetGold());;
				mSceneText["ShopGoldText"].text = "Gold: " + std::to_string(mShop.GetGold());;
			}
		}
	}

}

void ShopScene::GenerateGrids()
{
	mPlayer.GetInventory().SetInitialGridPos(80);
	mShop.GetInventory().SetInitialGridPos(880);

	mPlayer.GetInventory().GeneratePositions();
	mShop.GetInventory().GeneratePositions();

	SetupPlayerInv();
	SetupShopInv();

	DrawGrid(4, 5, 80, 110); // Draw item frames for player inventory
	DrawGrid(4, 5, 880, 110); // Draw item frames for shop inventory

	PlaceItems(mPlayer.GetInventory());
	PlaceItems(mShop.GetInventory());
}


void ShopScene::DrawGrid(int gridWidth, int gridHeight, int offsetX, int offsetY)
{
	int cellAmount = gridWidth * gridHeight;
	int initialX = offsetX;
	for (int i = 0; i < cellAmount; ++i)
	{
		if (offsetX >= 360 + initialX)
		{
			offsetX = initialX;
			offsetY += 110;
		}
		AddObject("itemFrameObj", offsetX, offsetY, Background);
		offsetX += 90;
	}
}


