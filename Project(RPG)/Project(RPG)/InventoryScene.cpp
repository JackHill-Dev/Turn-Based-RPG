#include "InventoryScene.h"


struct itemObj
{
	itemObj(Item* item, RenderObject* obj):item(item), obj(obj)
	{

	}
	Item* item;
	RenderObject* obj;
	bool pickedUp = false;
};
struct characterInventory
{
	characterInventory(Character* character,RenderObject* portrait, RenderObject* weaponSlot, RenderObject* armourSlot) :portrait(portrait), weaponSlot(weaponSlot), armourSlot(armourSlot), character(character)
	{

	}
	Character* character;
	RenderObject* portrait;
	RenderObject* weaponSlot;
	RenderObject* armourSlot;

};
std::vector<itemObj> items;
std::vector<characterInventory> characters;

InventoryScene::InventoryScene(Interface* mgr) : Scene(mgr)
{
	AddObject("ShopBGObj", 640, 360, Background);
	pCloseBtn = AddObject("exitButtonObj", 1000, 50, UI);
	button_SFX = Mix_LoadWAV("Assets/SFX/GenericClick.wav");
	Init();
}

void InventoryScene::Load()
{
	mParty = mgr->GetPlayer()->GetParty();
	mLayers[Game].clear();
	items.clear();
	
	int i = 0;
	for (Item* item : mgr->GetPlayer()->inventory)
	{
		items.push_back(itemObj(item, AddObject(item->GetObjName(), playerInvGrid[i]->GetPos().first, playerInvGrid[i]->GetPos().second, Game)));
		++i;
	}
	i = 0;
	for (auto &c : mParty)
	{

		int xOffset = 640 + ( (i - (mParty.size()) / 2 ) * 300);
		characters.push_back(characterInventory(c,AddObject(c->GetPortraitName(), xOffset,180, Background), AddObject("itemFrameObj", xOffset- 150, 220, Background), AddObject("itemFrameObj", xOffset - 150, 120, Background)));

		if (c->ArmourEquipSlot != nullptr)
		{
			items.push_back(itemObj(c->ArmourEquipSlot, 
			AddObject(c->ArmourEquipSlot->GetObjName(), characters.back().armourSlot->GetPos().first, characters.back().armourSlot->GetPos().second, Game)));
		}
		i++;
	}


}

void InventoryScene::Update(double dTime, Act act, std::pair<int, int> mousePos)
{
	if (act == Act::Click && pCloseBtn->InBounds(mousePos.first, mousePos.second))
	{
		mgr->PlaySFX(button_SFX, 0, 1);
		mgr->LoadPreviousScene();
	}

	for (auto &i : items)
	{
		if (act == Act::Click)
		{
			if (i.obj->InBounds(mousePos.first, mousePos.second) && i.item != nullptr)
			{
				if (i.pickedUp)
				{
					for (auto& c : characters)
					{
						if (c.armourSlot->InBounds(mousePos.first, mousePos.second) && i.pickedUp && c.character->ArmourEquipSlot == nullptr)
						{
							i.pickedUp = false;
							i.obj->SetPos(c.armourSlot->GetPos());
							c.character->SetArmour(static_cast<Armour*>(i.item));
							
							
						}
					}
					if (i.pickedUp)
					{
						for (auto g : playerInvGrid)
						{
							if (g->InBounds(mousePos.first, mousePos.second) && i.pickedUp)
							{
								i.obj->SetPos(g->GetPos());
								i.pickedUp = false;
								mgr->GetPlayer()->inventory.push_back(i.item);
							}
						}
					}
					if (i.pickedUp)
					{
						i.obj->SetPos(playerInvGrid[mgr->GetPlayer()->inventory.size()]->GetPos());
						i.pickedUp = false;
						mgr->GetPlayer()->inventory.push_back(i.item);
					}
				}
				else
				{
					i.pickedUp = true;

					bool partyItem = false;
					for (auto& c : characters)
					{
						if (c.character->ArmourEquipSlot == i.item && !partyItem)
						{
							c.character->SetArmour(nullptr);
							partyItem = true;
						}
					}
						if (!partyItem)
						{
							mgr->GetPlayer()->inventory.erase(std::remove(mgr->GetPlayer()->inventory.begin(), mgr->GetPlayer()->inventory.end(), i.item));
						}
					
						
				}
			}
		}

		if (act == Act::MouseUpdate)
		{
			if (i.pickedUp)
			{
				i.obj->SetPos(std::make_pair(mousePos.first, mousePos.second));
			}
		}
	}
}


void InventoryScene::GetCharacterPortraits()
{
	//int testX;
	//switch (mParty.size())
	//{
	//case 1: testX = 640; break;
	//case 2: testX = 540; break;
	//case 3: testX = 440; break;
	//case 4: testX = 250; break;
	//default: testX = 0; break;
	//}
	//
	//int offsetX = testX; // Allows for equal seperation of portraits and frames

	//// Get all party memebers from player
	//for (Character* c : mgr->GetPlayer()->GetParty())
	//{
	//	AddObject(c->GetPortraitName(), offsetX, 180, Background)->SetScale(std::make_pair(0.8,0.8)); // Get all of their portrait render objects and add them to the scene

	//	c->ArmourEquipSlot.slotObj = AddObject("itemFrameObj", offsetX - 120, 150, Background);
	//	c->mWeaponEquipSlot.slotObj = AddObject("itemFrameObj", offsetX - 120, 260, Background);

	//	

	//	offsetX += 250;
	//}
}

void InventoryScene::Init()
{
	mParty = mgr->GetPlayer()->GetParty();

	playerInvGrid = DrawGrid(9, 3, 250, 400, 800);
	Load();
}


std::vector<RenderObject*> InventoryScene::DrawGrid(int gridWidth, int gridHeight, int offsetX, int offsetY, int gridBoundsX)
{
	std::vector<RenderObject*> objs;
	int cellAmount = gridWidth * gridHeight;
	int initialX = offsetX;
	for (int i = 0; i < cellAmount; ++i)
	{
		if (offsetX >= gridBoundsX + initialX)
		{
			offsetX = initialX;
			offsetY += 110;
		}
		RenderObject* temp = AddObject("itemFrameObj", offsetX, offsetY, Background);
		objs.push_back(temp);
		offsetX += 90;
	}
	return objs;
}
