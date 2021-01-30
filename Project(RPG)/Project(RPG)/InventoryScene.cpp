#include "InventoryScene.h"

InventoryScene::InventoryScene(Interface* mgr) : Scene(mgr)
{
	AddObject("ShopBGObj", 640, 360, Background);
	pCloseBtn = AddObject("exitButtonObj", 1000, 50, UI);
	Init();
}

void InventoryScene::Load()
{
	mLayers[Game].clear();
	itemObjects.clear();
	int i = 0;
	for (Item* item : mgr->GetPlayer()->GetInventory().GetContents())
	{
		itemObjects.push_back(ItemObject(item, AddObject(item->GetObjName(), playerInvGrid[i]->GetPos().first, playerInvGrid[i]->GetPos().second, Game)));
		++i;
	}

	for (auto c : mParty)
	{
		// Currently causes item duping glitch (feature)
		if (c->ArmourEquipSlot._item != nullptr)
			itemObjects.push_back(ItemObject(c->ArmourEquipSlot._item, AddObject(c->ArmourEquipSlot._item->GetObjName(),
				c->ArmourEquipSlot.slotObj->GetPos().first, c->ArmourEquipSlot.slotObj->GetPos().second, Game)));
	}
}

void InventoryScene::Update(double dTime, Act act, std::pair<int, int> mousePos)
{
	if (act == Act::Click && pCloseBtn->InBounds(mousePos.first, mousePos.second))
		mgr->LoadPreviousScene();

	for (auto i : itemObjects)
	{
		if (act == Act::Click && i.obj->InBounds(mousePos.first, mousePos.second))
		{
			if (i.obj->bPickedUp)
			{
				for (auto c : mParty)
				{
					HandleArmourEquip(i, *c);
					HandleWeaponEquip(i, *c);

					if (c->ArmourEquipSlot._item == i._item && !i._item->bEquipped)
					{
						switch (i._item->GetType())
						{
						case ItemType::ARMOUR:
							c->SetArmour(nullptr);
							c->UpdateCharacter();
							mgr->GetPlayer()->GetInventory().AddItem(i._item);
							break;
						case ItemType::WEAPON:
							c->SetWeapon(nullptr);
							c->UpdateCharacter();
						default:
							std::cout << "\nUnknown item type";
							break;
						}

					}
				}

			}
			else
			{
				i.obj->bPickedUp = true; // Pickup the item
				i._item->bEquipped = false; // Make sure the item isn't equipped by a character
			}

		}

		if (act == Act::MouseUpdate && i.obj->InBounds(mousePos.first, mousePos.second))
		{
			if (i.obj->bPickedUp)
			{
				i.obj->SetPos(std::make_pair(mousePos.first, mousePos.second));
			}
		}
	}
}


void InventoryScene::GetCharacterPortraits()
{
	int testX;
	switch (mParty.size())
	{
	case 1: testX = 640; break;
	case 2: testX = 540; break;
	case 3: testX = 440; break;
	case 4: testX = 250; break;
	}
	
	int offsetX = testX; // Allows for equal seperation of portraits and frames

	// Get all party memebers from player
	for (Character* c : mParty)
	{
		AddObject(c->GetPortraitName(), offsetX, 180, UI)->SetScale(std::make_pair(0.8,0.8)); // Get all of their portrait render objects and add them to the scene

		c->ArmourEquipSlot.slotObj = AddObject("itemFrameObj", offsetX - 120, 150, Background);
		c->mWeaponEquipSlot.slotObj = AddObject("itemFrameObj", offsetX - 120, 260, Background);

		

		offsetX += 250;
	}
}

void InventoryScene::Init()
{
	mParty = mgr->GetPlayer()->GetParty();
	GetCharacterPortraits();
	playerInvGrid = DrawGrid(9, 3, 250, 400, 800);
	Load();
}

void InventoryScene::HandleArmourEquip(ItemObject & i, Character & c)
{
	// Check if what is under the item is an item frame
	if (i.obj->InBounds(c.ArmourEquipSlot.slotObj->GetPos().first, c.ArmourEquipSlot.slotObj->GetPos().second) && c.ArmourEquipSlot._item == nullptr)
	{
		// if type armour
		if (i._item->GetType() == ARMOUR) // Getting called twice and don't know why
		{
			if (!i._item->bEquipped)
			{
				c.SetArmour(static_cast<Armour*>(i._item)); // then check which character's equipment slot it is and then assign them that piece of equipment
				mgr->GetPlayer()->GetInventory().RemoveItem(i._item);
				i._item->bEquipped = true;
				i.obj->bPickedUp = false; // Dropped the item
			}

		}

	}
	else
	{
		i.obj->bPickedUp = false;
	}
}

	void InventoryScene::HandleWeaponEquip(ItemObject& i, Character& c)
{
	// Check if what is under the item is an item frame
	if (i.obj->InBounds(c.mWeaponEquipSlot.slotObj->GetPos().first, c.mWeaponEquipSlot.slotObj->GetPos().second) && c.mWeaponEquipSlot._item == nullptr)
	{
		// if type weapon
		if (i._item->GetType() == WEAPON) // Getting called twice and don't know why
		{
			if (!i._item->bEquipped)
			{
				c.SetWeapon(static_cast<Weapon*>(i._item)); // then check which character's equipment slot it is and then assign them that piece of equipment
				i._item->bEquipped = true; // Equipped item 
				i.obj->bPickedUp = false; // Dropped the item
			}
		}
	}
	else
	{
		i.obj->bPickedUp = false;
	}
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
