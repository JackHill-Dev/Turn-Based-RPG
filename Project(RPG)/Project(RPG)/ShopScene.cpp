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

ShopScene::~ShopScene()
{
	bg_Music = nullptr;
	delete bg_Music;

	buySell_SFX = nullptr;
	delete buySell_SFX;

	button_Click_SFX = nullptr;
	delete button_Click_SFX;

	leave_SFX = nullptr;
	delete leave_SFX;

	pExitButton = nullptr;
	delete pExitButton;

	playerItemHovered = nullptr;
	delete playerItemHovered;

	shopItemHovered = nullptr;
	delete shopItemHovered;
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
	for (auto i : mgr->GetPlayer()->GetInventory().GetContents())
	{
		// Display item to screen and set its render object to the correct image
		playerInv.push_back(ItemObject(i, AddObject(i->GetObjName(), i->inventoryPos.pos.first, i->inventoryPos.pos.second, Game)));
		
	}

	for (auto i : mShop.GetInventory().GetContents())
	{
		// Display item to screen and set its render object to the correct image
		shopInv.push_back(ItemObject(i, AddObject(i->GetObjName(), i->inventoryPos.pos.first, i->inventoryPos.pos.second, Game)));

	}
}

void ShopScene::Init()
{
	AddObject("ShopBGObj", 1280 / 2, 720 / 2, Background);
	
	AddObject("merchantPortraitObj", 725, 225, UI);
	pExitButton = AddObject("exitButtonObj", 620, 600, UI);


	UIText defaultText;
	defaultText.text = "This is default tooltip text";
	mTooltip = ToolTip(AddObject("defaultItemObj", 640, 650, UI),
		AddObject("toolTipBgObj", 640, 650, UI), defaultText, std::make_pair(640, 600));
	mTooltip.mDescription.scale = { 140, 100 };
	mTooltip.mDescription.bWrapped = true;

	playerToolTip = ToolTip(AddObject("defaultItemObj", 640, 650, UI),
		AddObject("toolTipBgObj", 640, 650, UI), defaultText, std::make_pair(640, 600));
	playerToolTip.mDescription.scale = { 140, 100 };
	playerToolTip.mDescription.bWrapped = true;


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
	mSceneText.push_back(&mTooltip.mDescription);
	mSceneText.push_back(&playerToolTip.mDescription);

	mgr->FadeInMusic(bg_Music, -1, mgr->fadeTime);

	mLayers[Game].clear();
	playerInv.clear();
	shopInv.clear();
	PlaceItems(mgr->GetPlayer()->GetInventory());
	//PlaceItems(mShop.GetInventory());
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
	shopItemHovered = nullptr;
	// check if mouse is hovering over it
	if (act == Act::MouseUpdate)
	{
		for (auto& i : shopInv)
		{
			if (i.obj->InBounds(mousePos.first, mousePos.second))
			{
				shopItemHovered = &i;
				i.obj->tint = SDL_Color{ 0,255,0 };
			}
			else
				i.obj->tint = SDL_Color{ 255,255,255 };
		
		}
		if (shopItemHovered != nullptr)
		{
			//current->OnHover();
			mTooltip.pItemImage->SetTexture(shopItemHovered->obj->GetSheet());
			mTooltip.mDescription.text = shopItemHovered->_item->GetDescription();

			mTooltip.Show();
		}
		else
		{
			mTooltip.Hide();
			shopItemHovered = nullptr;
		}
		//HandleTooltip(shopItemHovered);
	}
	
	for (ItemObject i : shopInv)
	{
		
		
		if (act == Act::RClick && i.obj->InBounds(mousePos.first, mousePos.second))
		{
			if (!(mgr->GetPlayer()->GetGold() < i._item->GetCost())) // If player can't afford item they can't buy it
			{
				mShop.BuyItem(i._item);
				playerInv.push_back(i);
				shopInv.erase(std::remove_if(shopInv.begin(), shopInv.end(), [&i](ItemObject item_) {return item_._item == i._item; }));
				mgr->GetPlayer()->SetGold(-i._item->GetCost());	// Remove cost of item from player's gold
				mgr->GetPlayer()->GetInventory().AddItem(i._item);// Add bought item to player's inventory
				mgr->PlaySFX(buySell_SFX, 0, 1);
				i.obj->SetPos(i._item->inventoryPos.pos);
				mSceneText[0]->text = "Gold: " + std::to_string(mgr->GetPlayer()->GetGold());; // Display player gold
				mSceneText[1]->text = "Gold: " + std::to_string(mShop.GetGold());;	// Display shop gold
			}

		}
	}
	
}

void ShopScene::ManagePlayerInventory(Inventory& inv, Act act, std::pair<int, int> mousePos)
{
	playerItemHovered = nullptr;
	if (act == Act::MouseUpdate)
	{
		for (auto& i : playerInv)
		{
			if (i.obj->InBounds(mousePos.first, mousePos.second))
			{
				playerItemHovered = &i;
				i.obj->tint = SDL_Color{ 0,255,0 };
			}
			else
				i.obj->tint = SDL_Color{ 255,255,255 };

		}
		if (playerItemHovered != nullptr)
		{
			playerToolTip.pItemImage->SetTexture(playerItemHovered->obj->GetSheet());
			playerToolTip.mDescription.text = playerItemHovered->_item->GetDescription();

			playerToolTip.Show();
		}
		else
		{
			playerToolTip.Hide();
		}
	}

	

	// for each item in player's inventory on screen
	for (ItemObject i : playerInv)
	{
		// check if mouse is hovering over it
		
		
		if (act == Act::RClick && i.obj->InBounds(mousePos.first, mousePos.second))
		{
			if (!(mShop.GetGold() < i._item->GetCost())) // Can only sell to the shop if the shop can give you the moeny for the item
			{
				mgr->GetPlayer()->SellItem(i._item);	 // Remove item from player's inventory and add to its gold
				shopInv.push_back(i);
				playerInv.erase(std::remove_if(playerInv.begin(), playerInv.end(), [&i](ItemObject nI) { return nI._item == i._item; })); // remove from local container as well
				mShop.SetGold(-i._item->GetCost());	 // Remove cost of sold item from shop gold
				mShop.GetInventory().AddItem(i._item); // Add sold item to shop inventory
				mgr->PlaySFX(buySell_SFX, 0, 1); // Play buy sfx on channel 1 and don't loop
				i.obj->SetPos(i._item->inventoryPos.pos); // Update the render object position 
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

void ShopScene::HandleTooltip(ItemObject* hovered)
{
	if (hovered != nullptr)
	{
		//current->OnHover();
		mTooltip.pItemImage->SetTexture(hovered->obj->GetSheet());
		mTooltip.mDescription.text = hovered->_item->GetDescription();

		mTooltip.Show();
	}
	else
	{
		mTooltip.Hide();
	
	}
}



int ShopScene::RandomRange(int min, int max)
{
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(random_number_engine);
}


