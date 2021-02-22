#include "InventoryScene.h"

InventoryScene::InventoryScene(Interface* mgr) : Scene(mgr)
{
	AddObject("ShopBGObj", 640, 360, Background);
	pCloseBtn = AddObject("CloseBtnObj", 1200, 50, UI);
	pDrink_SFX = Mix_LoadWAV("Assets/SFX/potiondrinklong.wav");
	button_SFX = Mix_LoadWAV("Assets/SFX/GenericClick.wav");
	Init();
}

InventoryScene::~InventoryScene()
{
	delete pCloseBtn;
	pCloseBtn = nullptr;


	delete button_SFX;
	button_SFX = nullptr;


	delete pDrink_SFX;
	pDrink_SFX = nullptr;

	for (auto& g : playerInvGrid)
	{
		delete g.first;
		g.first = nullptr;

		g.second = nullptr;

	}
}

void InventoryScene::Init()
{
	mParty = mgr->GetPlayer()->GetParty();
	DrawGrid(250, 400, 800);

	UIText defaultText;
	defaultText.text = "This is default tooltip text";
	mToolTip = ToolTip(AddObject("defaultItemObj", 640, 650, UI),
		AddObject("toolTipBgObj", 640, 650, UI), defaultText, std::make_pair(640, 600));
	mToolTip.mDescription.scale = { 140, 100 };
	mToolTip.mDescription.bWrapped = true;
}


void InventoryScene::Load()
{
	mParty = mgr->GetPlayer()->GetParty();
	// To avoid items duplicating clear the layer they are on
	mLayers[Game].clear();
	itemObjects.clear();
	mSceneText.clear();
	characters.clear();

	int i = 0;



	for (auto& c : mParty)
	{
		// Dynamically work out the x pos of the portraits and equip slots based how the amount in the party
		int xOffset = 640 + ((i - (mParty.size()) / 2) * 300);
		characters.push_back(characterInventory(c, AddObject(c->GetPortraitName(), xOffset, 180, Game), AddObject("itemFrameObj", xOffset - 150, 230, Game), AddObject("itemFrameObj", xOffset - 150, 120, Game)));

		// if a character has an equip slot filled then draw them to the screen and add them the the scene's item objects
		if (c->ArmourEquipSlot != nullptr)
		{
			itemObjects.push_back(ItemObject(c->ArmourEquipSlot,
				AddObject(c->ArmourEquipSlot->GetObjName(), characters.back().armourSlot->GetPos().first, characters.back().armourSlot->GetPos().second, Game)));
		}

		if (c->mWeaponEquipSlot != nullptr)
		{
			itemObjects.push_back(ItemObject(c->mWeaponEquipSlot,
				AddObject(c->mWeaponEquipSlot->GetObjName(), characters.back().weaponSlot->GetPos().first, characters.back().weaponSlot->GetPos().second, Game)));
		}
		i++;
	}
	i = 0;
	// Draw the player's inventory 
	for (Item* item : mgr->GetPlayer()->inventory)
	{
		itemObjects.push_back(ItemObject(item, AddObject(item->GetObjName(), playerInvGrid[i].first->GetPos().first, playerInvGrid[i].first->GetPos().second, Game)));
		playerInvGrid[i].second = &itemObjects.back();
		++i;
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
		pCloseBtn->Untint();
	}
	ItemObject* current = nullptr;



	if (act == Act::Click)
	{
		int temp = 0;
		for (ItemObject& i : itemObjects)
		{

			if (temp < itemObjects.size())
			{
				if (i.obj->InBounds(mousePos.first, mousePos.second) && i._item != nullptr)
				{
					if (i.bPickedUp)
					{
						for (auto& c : characters)
						{
							if (c.armourSlot->InBounds(mousePos.first, mousePos.second) && i.bPickedUp && c.character->ArmourEquipSlot == nullptr && (dynamic_cast<Armour*>(i._item)))
							{
								i.bPickedUp = false;
								i.obj->SetPos(c.armourSlot->GetPos());
								c.character->SetArmour(static_cast<Armour*>(i._item)); // Equip the armour selected


							}
							else
								if (c.weaponSlot->InBounds(mousePos.first, mousePos.second) && i.bPickedUp && c.character->mWeaponEquipSlot == nullptr && (dynamic_cast<Weapon*>(i._item)))
								{
									i.bPickedUp = false;
									i.obj->SetPos(c.weaponSlot->GetPos());
									c.character->SetWeapon(static_cast<Weapon*>(i._item)); // Equip the weapon selected


								}

							if (c.portrait->InBounds(mousePos.first, mousePos.second) && i._item->GetType() == CONSUMABLE)
							{
								c.character->Heal(c.character->GetStats().health, static_cast<Consumable*>(i._item)->mHealAmount);
								mgr->PlaySFX(pDrink_SFX, 0, 0);
								i.bPickedUp = false;
								//i.obj->SetVisible(false);

								mLayers[Game].erase(std::find_if(mLayers[Game].begin(), mLayers[Game].end(), [&i](RenderObject* iobj) {return iobj == i.obj; }));
								itemObjects.erase(std::find_if(itemObjects.begin(), itemObjects.end(), [&i](ItemObject& iobj) {return iobj._item == i._item; }));

								//mgr->GetPlayer()->RemoveItem(i._item);

							}
						}
						if (i.bPickedUp)
						{
							// if inbound of a grid renderobject then place it there
							for (auto& g : playerInvGrid)
							{
								if (g.first->InBounds(mousePos.first, mousePos.second) && i.bPickedUp && g.second == nullptr)
								{
									i.obj->SetPos(g.first->GetPos());
									i.bPickedUp = false;
									g.second = &i;
									mgr->GetPlayer()->AddItem(i._item);
								}
							}
						}
						//if (i.bPickedUp)
						//{
							// if not placed a grid and then snap back to grid and make sure items don't overlap
							//pos = mgr->GetPlayer()->inventory.size() + it;

							//auto& pos = *std::find_if(playerInvGrid.begin(), playerInvGrid.end(), [](std::pair<RenderObject*, ItemObject*> p) {return p.second == nullptr; });


							/*if (pos >= playerInvGrid.size())
							{
								pos = 0;
								it = 0;
							}*/
							//i.obj->SetPos(pos.first->GetPos());
							//pos.second = &i;
							//it++;

							//i.taken = true;
							//i.bPickedUp = false;
							//mgr->GetPlayer()->AddItem(i._item);
						//}
					}
					else
					{
						i.bPickedUp = true;
						playerInvGrid[temp].second = nullptr;
						bool partyItem = false;
						for (auto& c : characters)
						{
							if (c.character->ArmourEquipSlot == i._item && !partyItem)
							{
								c.character->SetArmour(nullptr); // Unequip armour
								partyItem = true;
							}

							if (c.character->mWeaponEquipSlot == i._item && !partyItem)
							{
								c.character->SetWeapon(nullptr); // Unequip weapon
								partyItem = true;
							}


						}

						if (!partyItem)
						{
							// Once equipped remove from global player inventory
							if (i._item != nullptr)
							{
								//playerInvGrid[temp].second = nullptr;
								auto index = std::find_if(playerInvGrid.begin(), playerInvGrid.end(), [&i](std::pair<RenderObject*, ItemObject*> p) { return i._item == p.second->_item; });
								/*if (index != playerInvGrid.end())
									index->second = nullptr;*/
								mgr->GetPlayer()->RemoveItem(i._item);

							}
						}


					}
				}
			}
			temp++;
		}
	}


	if (act == Act::MouseUpdate)
	{
		for (auto& i : itemObjects)
		{
			if (pCloseBtn->InBounds(mousePos.first, mousePos.second))
			{
				pCloseBtn->Tint({ 0,255,0 });
			}
			else
			{
				pCloseBtn->Untint();
			}


			if (i.bPickedUp)
			{
				// While item is picked up stay at the mouse's screen position
				i.obj->SetPos(std::make_pair(mousePos.first / i.obj->sceneScale.first, mousePos.second / i.obj->sceneScale.second));
				current = nullptr;
			}

			if (i.obj->InBounds(mousePos.first, mousePos.second))
			{
				current = &i;

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


}




void InventoryScene::DrawGrid(int offsetX, int offsetY, int gridBoundsX)
{
	//std::vector<RenderObject*> objs;
	//int cellAmount = gridWidth * gridHeight;

	int initialX = offsetX;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 9; j++)
		{
			RenderObject* temp = AddObject("itemFrameObj", offsetX + 90 * j, offsetY + 110 * i, Background);
			playerInvGrid.push_back(std::make_pair(temp, nullptr));
		}
		/*if (offsetX >= gridBoundsX + initialX)
		{
			offsetX = initialX;
			offsetY += 110;
		}*/

		//objs.push_back(temp);
		//offsetX += 90;
	}

}
