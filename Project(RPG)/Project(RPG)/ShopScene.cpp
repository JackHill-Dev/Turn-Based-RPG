#include "ShopScene.h"
#include <random>
#include <chrono>

std::mt19937 random_number_engine(time(0));

ShopScene::ShopScene(Interface* rng) : Scene(rng)
{
	bg_Music = Mix_LoadMUS("Assets/Music/MedievalLoop.mp3");
	buySell_SFX = Mix_LoadWAV("Assets/SFX/coin.wav");
	leave_SFX = Mix_LoadWAV("Assets/SFX/DoorClose.wav");

	Init();
}

void ShopScene::Update(double dTime, Act act, std::pair<int, int> mousePos)
{

	if (act == Act::Click)
	{
		if (pExitButton->InBounds(mousePos.first, mousePos.second))
		{
			mgr->PlaySFX(leave_SFX, 0, 1);
			mgr->LoadPreviousScene();
		}
	}
	ManagePlayerInventory(mgr->GetPlayer()->GetInventory(), act, mousePos);
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
	
	AddObject("merchantPortraitObj", 725, 225, UI);
	pExitButton = AddObject("exitButtonObj", 620, 600, UI);

	GenerateGrids();
	
}

void ShopScene::Load()
{
	AddObject(mgr->GetPlayer()->GetParty().at(0)->GetPortraitName(), 505, 225, UI); // Now loads portrait of 1st in party. These need matching in scale to merchant - EH

	mSceneText.clear();

	mShop.SetGold(-mShop.GetGold());
	mShop.SetGold(RandomRange(300, 2000));

	mPlayerGoldText.text = "Gold: " + std::to_string(mgr->GetPlayer()->GetGold());
	mPlayerGoldText.pos = std::make_pair(550, 415);
	mPlayerGoldText.textColor = SDL_Color{ 255, 215, 0 }; // Gold

	mShopGoldText.text = "Gold: " + std::to_string(mShop.GetGold());
	mShopGoldText.pos = std::make_pair(680, 415);
	mShopGoldText.textColor = SDL_Color{ 255, 215, 0 }; // Gold
	
	mSceneText.push_back(&mPlayerGoldText);
	mSceneText.push_back(& mShopGoldText);


	mgr->FadeInMusic(bg_Music, -1, mgr->fadeTime);
	mLayers[Game].clear();
	PlaceItems(mgr->GetPlayer()->GetInventory());
	PlaceItems(mShop.GetInventory());
}

void ShopScene::SetupShopInv()
{
	for (int f = 0; f < 20; ++f)
	{

		int i = RandomRange(0, 99);
		if (i >= 0 && i <= 24)
		{
			mShop.GetInventory().AddItem(new Weapon("Sword", 50));
		}
		else if (i > 24 && i <= 49)
		{
			mShop.GetInventory().AddItem(new Armour("Armor", 150));
		}
		else
		{
			mShop.GetInventory().AddItem(new Consumable("Potion", 25));
		}
	}


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
			if (!(mgr->GetPlayer()->GetGold() < i->GetCost())) // If player can't afford item they can't buy it
			{
				mShop.BuyItem(i);
				mgr->GetPlayer()->SetGold(-i->GetCost());	// Remove cost of item from player's gold
				mgr->GetPlayer()->GetInventory().AddItem(i);// Add bought item to player's inventory
				mgr->PlaySFX(buySell_SFX, 0, 1);
				i->GetRenderObject()->SetPos(i->inventoryPos.pos);
				mSceneText[0]->text = "Gold: " + std::to_string(mgr->GetPlayer()->GetGold());; // Display player gold
				mSceneText[1]->text = "Gold: " + std::to_string(mShop.GetGold());;	// Display shop gold
			}

		}
	}
	
}

void ShopScene::ManagePlayerInventory(Inventory& inv, Act act, std::pair<int, int> mousePos)
{
	// for each item in player's inventory on screen
	for (Item* i : inv.GetContents())
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
				mgr->GetPlayer()->SellItem(i);	 // Remove item from player's inventory and add to its gold
				mShop.SetGold(-i->GetCost());	 // Remove cost of sold item from shop gold
				mShop.GetInventory().AddItem(i); // Add sold item to shop inventory
				mgr->PlaySFX(buySell_SFX, 0, 1); // Play buy sfx on channel 1 and don't loop
				i->GetRenderObject()->SetPos(i->inventoryPos.pos); // Update the render object position 
				// Update the gold text for both player and shop
				mSceneText[0]->text = "Gold: " + std::to_string(mgr->GetPlayer()->GetGold());;
				mSceneText[1]->text = "Gold: " + std::to_string(mShop.GetGold());;
			}
		}
	}
}

void ShopScene::GenerateGrids()
{
	mShop.GetInventory().SetInitialGridPos(880);

	mShop.GetInventory().GeneratePositions();

	SetupShopInv();

	DrawGrid(4, 5, 80, 110); // Draw item frames for player inventory
	DrawGrid(4, 5, 880, 110); // Draw item frames for shop inventory

	PlaceItems(mgr->GetPlayer()->GetInventory());
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



int ShopScene::RandomRange(int min, int max)
{
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(random_number_engine);
}


