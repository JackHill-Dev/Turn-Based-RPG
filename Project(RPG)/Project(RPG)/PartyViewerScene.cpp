#include "PartyViewerScene.h"

PartyViewerScene::PartyViewerScene(Interface* mgr) : Scene(mgr)
{
	// Add background to scene
	AddObject("mainMenuBGObj", 640, 360, Background);
	// Add close button to scene
	mCloseBtn = AddObject("CloseBtnObj", 1200, 50, UI);

	Init();

}

void PartyViewerScene::Update(double dTime, Act act, std::pair<int, int> mousePos)
{
	// Check if close button has been pressed 
	if (act == Act::Click && mCloseBtn->InBounds(mousePos.first, mousePos.second))
		mgr->LoadPreviousScene(); 	// Go to previous scene that opened the party viewer

	
	//for (auto i : itemObjects)
	//{
	//	if (act == Act::Click && i.obj->InBounds(mousePos.first, mousePos.second))
	//	{
	//		if (i.obj->bPickedUp)
	//		{
	//			for (auto c : mParty)
	//			{
	//				HandleArmourEquip(i, *c);
	//				HandleWeaponEquip(i, *c);

	//				if (!i._item->bEquipped)
	//				{
	//					switch (i._item->GetType())
	//					{
	//					case ItemType::ARMOUR:
	//						c->SetArmour(nullptr);
	//						c->UpdateCharacter();
	//						break;
	//					case ItemType::WEAPON:
	//						 c->SetWeapon(nullptr);
	//						 c->UpdateCharacter();
	//					default:
	//						std::cout << "\nUnknown item type";
	//						break;
	//					}
	//				
	//				}
	//			}
	//		
	//		}
	//		else
	//		{
	//			i.obj->bPickedUp = true; // Pickup the item
	//			i._item->bEquipped = false; // Make sure the item isn't equipped by a character
	//		}


	//	}

	//	if (act == Act::MouseUpdate && i.obj->InBounds(mousePos.first, mousePos.second))
	//	{
	//		if (i.obj->bPickedUp)
	//		{
	//			i.obj->SetPos(std::make_pair(mousePos.first, mousePos.second));
	//			
	//			
	//		}
	//	}
	mSceneText.clear();

	GetCharacterStatistics();
}


void PartyViewerScene::Init()
{
	mParty = mgr->GetPlayer()->GetParty();

	GetCharacterPortraits();
	GetCharacterStatistics();

	// Player inventory
//	playerInvGrid = DrawGrid(4, 5, 300, 450, 160);
//	Load();



}

void PartyViewerScene::Load()
{
	mParty = mgr->GetPlayer()->GetParty();
	/*mLayers[Game].clear();
	int i = 0;
	for (Item* item : mgr->GetPlayer()->GetInventory().GetContents())
	{
		itemObjects.push_back(ItemObject(item, AddObject(item->GetObjName(), playerInvGrid[i]->GetPos().first, playerInvGrid[i]->GetPos().second, Game)));
		++i;
	}*/

}

void PartyViewerScene::GetCharacterPortraits()
{
	int offsetX = 250; // Allows for equal seperation of portraits and frames
	
	// Get all party memebers from player
	for (Character* c : mParty)
	{
		AddObject(c->GetPortraitName(), offsetX, 180, UI); // Get all of their portrait render objects and add them to the scene
		offsetX += 250;							
	}
	offsetX = 250;
	// Add character frame object for each party memeber
	for (int i = 0; i < mParty.size(); ++i)
	{
		AddObject("characterFrameObj", offsetX, 350, Background);
		offsetX += 250;
	}
}

void PartyViewerScene::GetCharacterStatistics()
{
	int offsetX = 200;
	int offsetY = 330;
	for (Character* c  : mParty) 
	{
		CharacterCard cc;
		cc.health = DrawStat("Health", c->GetStats().health.second, SDL_Color{255,0,0}, std::make_pair(offsetX, offsetY));
		offsetY += 50;

		cc.mana = DrawStat("Mana", c->GetStats().mana.second, SDL_Color{ 0,0,200 }, std::make_pair(offsetX, offsetY));

		offsetY += 50;
		cc.agility = DrawStat("Agility", c->GetStats().agility.second, SDL_Color{ 0,200,0 }, std::make_pair(offsetX, offsetY));

		offsetY += 50;
		cc.stamina = DrawStat("Stamina", c->GetStats().stamina.second, SDL_Color{ 50, 143, 23 }, std::make_pair(offsetX, offsetY));

		offsetY += 50;
		cc.movement = DrawStat("Movement", c->GetStats().movement.second, SDL_Color{ 50,50,150 }, std::make_pair(offsetX, offsetY));

		mSceneText.push_back(cc.health);
		mSceneText.push_back(cc.mana);
		mSceneText.push_back(cc.agility);
		mSceneText.push_back(cc.stamina);
		mSceneText.push_back(cc.movement);


		offsetX += 250;
		offsetY = 330;
	}
}

//void PartyViewerScene::HandleArmourEquip(ItemObject& i, Character& c)
//{
//	// Check if what is under the item is an item frame
//	if (i.obj->InBounds(c.ArmourEquipSlot.slotObj->GetPos().first, c.ArmourEquipSlot.slotObj->GetPos().second) && c.ArmourEquipSlot._item == nullptr)
//	{
//		// if type armour
//		if (i._item->GetType() == ARMOUR) // Getting called twice and don't know why
//		{
//			if (!i._item->bEquipped)
//			{
//				c.SetArmour(static_cast<Armour*>(i._item)); // then check which character's equipment slot it is and then assign them that piece of equipment
//				i._item->bEquipped = true;
//				i.obj->bPickedUp = false; // Dropped the item
//			}
//
//		}
//
//	}
//	else
//	{
//		i.obj->bPickedUp = false;
//	}
//}

//void PartyViewerScene::HandleWeaponEquip(ItemObject& i, Character& c)
//{
//	// Check if what is under the item is an item frame
//	if (i.obj->InBounds(c.mWeaponEquipSlot.slotObj->GetPos().first, c.mWeaponEquipSlot.slotObj->GetPos().second) && c.mWeaponEquipSlot._item == nullptr)
//	{
//		// if type weapon
//		if (i._item->GetType() == WEAPON) // Getting called twice and don't know why
//		{
//			if (!i._item->bEquipped)
//			{
//				c.SetWeapon(static_cast<Weapon*>(i._item)); // then check which character's equipment slot it is and then assign them that piece of equipment
//				i._item->bEquipped = true; // Equipped item 
//				i.obj->bPickedUp = false; // Dropped the item
//			}
//		}
//	}
//	else
//	{
//		i.obj->bPickedUp = false;
//	}
//}

UIText PartyViewerScene::DrawStat(std::string statName, int stat, SDL_Color textColor, std::pair<int, int> pos)
{
	std::string statTxt = statName + ": " + std::to_string(stat);
	return UIText{statTxt, pos,std::make_pair(70,50), textColor};
}

//std::vector<RenderObject*> PartyViewerScene::DrawGrid(int gridWidth, int gridHeight, int offsetX, int offsetY, int gridBoundsX)
//{
//	std::vector<RenderObject*> objs;
//	int cellAmount = gridWidth * gridHeight;
//	int initialX = offsetX;
//	for (int i = 0; i < cellAmount; ++i)
//	{
//		if (offsetX >= gridBoundsX + initialX)
//		{
//			offsetX = initialX;
//			offsetY += 60;
//		}
//		RenderObject* temp = AddObject("itemFrameObj", offsetX, offsetY, Background);
//		temp->SetScale(std::make_pair(0.5,0.5));
//		objs.push_back(temp);
//		offsetX += 50;
//	}
//	return objs;
//}
