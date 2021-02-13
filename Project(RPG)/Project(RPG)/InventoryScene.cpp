#include "InventoryScene.h"

InventoryScene::InventoryScene(Interface* mgr) : Scene(mgr)
{
	AddObject("ShopBGObj", 640, 360, Background);
	pCloseBtn = AddObject("exitButtonObj", 1000, 50, UI);
	button_SFX = Mix_LoadWAV("Assets/SFX/GenericClick.wav");
	Init();
}

InventoryScene::~InventoryScene()
{
	pCloseBtn = nullptr;
	delete pCloseBtn;

	button_SFX = nullptr;
	delete button_SFX;

	for (auto r : playerInvGrid)
	{
		r = nullptr;
		delete r;
	}
}

void InventoryScene::Init()
{
	mParty = mgr->GetPlayer()->GetParty();
	playerInvGrid = DrawGrid(9, 3, 250, 400, 800);

	UIText defaultText;
	defaultText.text = "This is default tooltip text";
	mToolTip = ToolTip(AddObject("defaultItemObj", 640, 650, UI),
		AddObject("toolTipBgObj", 640, 650, UI), defaultText, std::make_pair(640, 600));
	mToolTip.mDescription.scale = { 140, 100 };
	mToolTip.mDescription.bWrapped = true;
	

	//Load();
}


void InventoryScene::Load()
{
	mParty = mgr->GetPlayer()->GetParty();
	mLayers[Game].clear();
	itemObjects.clear();
	mSceneText.clear();
	GetCharacterPortraits();
	int i = 0;
	for (Item* item : mgr->GetPlayer()->GetInventory().GetContents())
	{
		itemObjects.push_back(ItemObject(item, AddObject(item->GetObjName(), playerInvGrid[i]->GetPos().first, playerInvGrid[i]->GetPos().second, Game)));
		++i;
	}
	
	// if a character has an equip slot filled then draw them to the screen and add them the the scene's item objects
	for (auto c : mParty)
	{
		if (c->ArmourEquipSlot._item != nullptr)
			itemObjects.push_back(ItemObject(c->ArmourEquipSlot._item, AddObject(c->ArmourEquipSlot._item->GetObjName(),
				c->ArmourEquipSlot.slotObj->GetPos().first, c->ArmourEquipSlot.slotObj->GetPos().second, Game)));

		if (c->mWeaponEquipSlot._item != nullptr)
			itemObjects.push_back(ItemObject(c->mWeaponEquipSlot._item, AddObject(c->mWeaponEquipSlot._item->GetObjName(),
				c->mWeaponEquipSlot.slotObj->GetPos().first, c->mWeaponEquipSlot.slotObj->GetPos().second, Game)));
	}

	mToolTip.mDescription.textColor = SDL_Color{ 255,255,255 };
	mSceneText.push_back(&mToolTip.mDescription);

}


void InventoryScene::Update(double dTime, Act act, std::pair<int, int> mousePos)
{
	
	if (act == Act::Click && pCloseBtn->InBounds(mousePos.first, mousePos.second))
	{
		mgr->PlaySFX(button_SFX, 0, 1);
		mgr->LoadPreviousScene();
	}
	ItemObject* current = nullptr;


	if (act == Act::Click)
	{
		for (auto& i : itemObjects)
		{
			if (i.obj->InBounds(mousePos.first, mousePos.second))
			{

				if (i.obj->bPickedUp)
				{
					for (auto c : mParty)
					{
						HandleArmourEquip(i, *c);
						HandleWeaponEquip(i, *c);

						if ((c->ArmourEquipSlot._item == i._item || c->mWeaponEquipSlot._item == i._item) && !i._item->bEquipped)
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
								mgr->GetPlayer()->GetInventory().AddItem(i._item);
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

		}
	}

	if (act == Act::MouseUpdate)
	{
		for (auto& i : itemObjects)
		{
			
				if (i.obj->bPickedUp)
				{
					i.obj->SetPos(std::make_pair(mousePos.first, mousePos.second));
					current = nullptr;
				}

				if (i.obj->InBounds(mousePos.first, mousePos.second))
				{
					current = &i;
					
				}
				

		}

		if (current != nullptr)
		{
			mToolTip.pItemImage->SetTexture(current->obj->GetSheet());
			mToolTip.mDescription.text = current->_item->GetDescription();

			mToolTip.SetPos({ current->obj->GetPos().first - 120, current->obj->GetPos().second });

			mToolTip.Show();

		}
		else
		{
			mToolTip.Hide();
			current = nullptr;
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
	default: testX = 0; break;
	}
	
	int offsetX = testX; // Allows for equal seperation of portraits and frames

	// Get all party memebers from player
	for (Character* c : mgr->GetPlayer()->GetParty())
	{
		AddObject(c->GetPortraitName(), offsetX, 180, Background)->SetScale(std::make_pair(0.8,0.8)); // Get all of their portrait render objects and add them to the scene

		c->ArmourEquipSlot.slotObj = AddObject("itemFrameObj", offsetX - 120, 150,	Game);
		c->mWeaponEquipSlot.slotObj = AddObject("itemFrameObj", offsetX - 120, 260, Game);

		offsetX += 250;
	}
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
				i.obj->SetPos(std::make_pair(c.ArmourEquipSlot.slotObj->GetPos().first, c.ArmourEquipSlot.slotObj->GetPos().second));
			
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
				i.obj->SetPos(std::make_pair(c.mWeaponEquipSlot.slotObj->GetPos().first, c.mWeaponEquipSlot.slotObj->GetPos().second));
				mgr->GetPlayer()->GetInventory().RemoveItem(i._item);
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
