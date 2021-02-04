#include "ClassPickerScene.h"

ClassPickerScene::ClassPickerScene(Interface* mObjMgr) : Scene(mObjMgr)
{
	pScrollBg = AddObject("scrollBgObj", 640, 360, Map);

	pWarriorIcon = AddObject("warSprObj", 320, 360, UI);
	pWarriorIcon->SetScale(std::make_pair(2, 2));

	pRogueIcon = AddObject("rogSprObj", 640, 360, UI);
	pRogueIcon->SetScale(std::make_pair(2, 2));

	pMageIcon = AddObject("mageSprObj", 960, 360, UI);
	pMageIcon->SetScale(std::make_pair(2, 2));

	pVillagerIcon = AddObject("villagerSpriteObj", 320, 360, UI);
	pVillagerIcon->SetScale(std::make_pair(2, 2));
	pVillagerIcon->SetVisible(false);

	pScholarIcon = AddObject("scholarSpriteObj", 640, 360, UI);
	pScholarIcon->SetScale(std::make_pair(2, 2));
	pScholarIcon->SetVisible(false);

	pNobleIcon = AddObject("nobleSpriteObj", 960, 360, UI);
	pNobleIcon->SetScale(std::make_pair(2, 2));
	pNobleIcon->SetVisible(false);

	pBackBtn = AddObject("backBtnObj", 140, 230, UI);

	pYesBtn = AddObject("yesTxtBtnObj", 800, 480, UI);
	pRejectBtn = AddObject("backTxtBtnObj", 480, 480, UI);

	bg_Music = Mix_LoadMUS("Assets/Music/ClassPicker.mp3");
	confirm_SFX = Mix_LoadWAV("Assets/SFX/confirmSound.wav");
	back_SFX = Mix_LoadWAV("Assets/SFX/BackSound.wav");

	Init();
}

void ClassPickerScene::Init()
{
	SetUpClassView();
}

void ClassPickerScene::Load()
{
	mgr->FadeInMusic(bg_Music, -1, mgr->fadeTime);
}


void ClassPickerScene::OnHover(RenderObject* rObj)
{
	rObj->Tint({ 0, 255, 0 });
}

void ClassPickerScene::OnLeave(RenderObject* rObj)
{
	rObj->Untint();
}

void ClassPickerScene::Update(double dTime, Act act, std::pair<int, int> mousePos)
{
	if (act == Act::MouseUpdate)
	{
		if (pWarriorIcon->InBounds(mousePos.first, mousePos.second) && !IsFocused)
		{
			OnHover(pWarriorIcon);
		}
		else OnLeave(pWarriorIcon);

		if (pRogueIcon->InBounds(mousePos.first, mousePos.second) && !IsFocused)
		{
			OnHover(pRogueIcon);
		}
		else OnLeave(pRogueIcon);

		if (pMageIcon->InBounds(mousePos.first, mousePos.second) && !IsFocused)
		{
			OnHover(pMageIcon);
		}
		else OnLeave(pMageIcon);

		if (pVillagerIcon->InBounds(mousePos.first, mousePos.second) && !IsFocused)
		{
			OnHover(pVillagerIcon);
		}
		else OnLeave(pVillagerIcon);

		if (pScholarIcon->InBounds(mousePos.first, mousePos.second) && !IsFocused)
		{
			OnHover(pScholarIcon);
		}
		else OnLeave(pScholarIcon);

		if (pNobleIcon->InBounds(mousePos.first, mousePos.second) && !IsFocused)
		{
			OnHover(pNobleIcon);
		}
		else OnLeave(pNobleIcon);
		
		if (pBackBtn->InBounds(mousePos.first, mousePos.second))
		{
			OnHover(pBackBtn);
		}
		else OnLeave(pBackBtn);

		if (pRejectBtn->InBounds(mousePos.first, mousePos.second))
		{
			OnHover(pRejectBtn);
		}
		else OnLeave(pRejectBtn);

		if (pYesBtn->InBounds(mousePos.first, mousePos.second))
		{
			OnHover(pYesBtn);
		}
		else OnLeave(pYesBtn);

	}

	if (act == Act::Click)
	{
		if (pBackBtn->InBounds(mousePos.first, mousePos.second))
		{
			mgr->PlaySFX(back_SFX, 0, 1);
			if (IsFocused)
			{
				if (PartyCount > 0)
				{
					mCharacters.pop_back();
					--PartyCount;
				}
				SetUpClassView();
				IsFocused = false;
				IsWarriorView = false;
				IsRogueView = false;
				IsMageView = false;
			}
			else
			{
				if (PartyCount > 0)
				{
					mCharacters.pop_back();
					--PartyCount;
					SetUpClassView();
				}
				else
				{
					mgr->LoadPreviousScene();
					IsFocused = false;
					IsWarriorView = false;
					IsRogueView = false;
					IsMageView = false;
				}
			}
		}

		if (pWarriorIcon->InBounds(mousePos.first, mousePos.second) && pWarriorIcon->IsVisible())
		{
			mgr->PlaySFX(confirm_SFX, 0, 1);
			IsFocused = true;
			IsWarriorView = true;
			OnLeave(pWarriorIcon);
			SetUpBackgroundView();
			//SetUpWarriorView();
			
		}

		if (pRogueIcon->InBounds(mousePos.first, mousePos.second) && pRogueIcon->IsVisible())
		{
			mgr->PlaySFX(confirm_SFX, 0, 1);
			IsFocused = true;
			IsRogueView = true;
			OnLeave(pRogueIcon);
			SetUpRogueView();		
		}

		if (pMageIcon->InBounds(mousePos.first, mousePos.second) && pMageIcon->IsVisible())
		{
			mgr->PlaySFX(confirm_SFX, 0, 1);
			IsFocused = true;
			IsMageView = true;
			OnLeave(pMageIcon);
			SetUpMageView();			
		}

		if (pRejectBtn->InBounds(mousePos.first, mousePos.second) && pRejectBtn->IsVisible())
		{
			mgr->PlaySFX(back_SFX, 0, 1);

			if (PartyCount > 0)
			{
				--PartyCount;
				mCharacters.pop_back();
			}
			IsFocused = false;
			IsWarriorView = false;
			IsRogueView = false;
			IsMageView = false;
			SetUpClassView();
		}

		if (pYesBtn->InBounds(mousePos.first, mousePos.second) && pYesBtn->IsVisible())
		{
			mgr->PlaySFX(confirm_SFX, 0, 1);
			++PartyCount;

			if (IsWarriorView)
			{
				mCharacters.push_back(new Character("warSprObj", "WarriorObj"));
			}
			if (IsRogueView)
			{
				mCharacters.push_back(new Character("rogSprObj", "RogueObj"));
			}
			if (IsMageView)
			{
				mCharacters.push_back(new Character("mageSprObj", "ClericObj"));
			}

			if (PartyCount < maxPartySize)
			{							
				IsFocused = false;
				IsWarriorView = false;
				IsRogueView = false;
				IsMageView = false;
				SetUpClassView();
			}
			else
			{
				IsFocused = false;
				IsWarriorView = false;
				IsRogueView = false;
				IsMageView = false;
				mgr->GetPlayer()->SetupParty(mCharacters);
				mgr->FadeOutMusic(mgr->fadeTime);
				mgr->LoadScene(Scenes::Overworld);
			}
		}

	}

}

void ClassPickerScene::SetUpClassView()
{
	pWarriorIcon->SetVisible(true);
	pRogueIcon->SetVisible(true);
	pMageIcon->SetVisible(true);
	pRejectBtn->SetVisible(false);
	pYesBtn->SetVisible(false);
	pVillagerIcon->SetVisible(false);
	pScholarIcon->SetVisible(false);
	pNobleIcon->SetVisible(false);



	pWarriorIcon->SetPos(std::make_pair(320, 360));
	pRogueIcon->SetPos(std::make_pair(640, 360));
	pMageIcon->SetPos(std::make_pair(960, 360));

	mSceneText.clear();

	mHeader.text = "CHARACTER CREATOR: " + std::to_string(PartyCount+1);
	mHeader.pos = std::make_pair<int>(640, 230);
	mHeader.textColor = SDL_Color{ 0,0,0 };
	mHeader.SetTextScale(300, 60);

	mHeaderInstruction.text = "CHOOSE YOUR CLASS";
	mHeaderInstruction.textColor = SDL_Color{ 0,0,0 };
	mHeaderInstruction.pos = std::make_pair<int>(640, 270);
	mHeaderInstruction.SetTextScale(250, 40);

	mFlavourText1.text = "WARRIOR";
	mFlavourText1.textColor = SDL_Color{ 0,0,0 };
	mFlavourText1.pos = std::make_pair<int>(320, 410);
	mFlavourText1.SetTextScale(100, 30);

	mFlavourText2.text = "ROGUE";
	mFlavourText2.textColor = SDL_Color{ 0,0,0 };
	mFlavourText2.pos = std::make_pair<int>(640, 410);
	mFlavourText2.SetTextScale(100, 30);

	mFlavourText3.text = "MAGE";
	mFlavourText3.textColor = SDL_Color{ 0,0,0 };
	mFlavourText3.pos = std::make_pair<int>(960, 410);
	mFlavourText3.SetTextScale(100, 30);

	mFooterInstruction.text = "PLEASE SELECT YOUR CHOICE WITH THE LEFT MOUSE BUTTON";
	mFooterInstruction.textColor = SDL_Color{ 0,0,0 };
	mFooterInstruction.pos = std::make_pair<int>(640, 550);
	mFooterInstruction.SetTextScale(700, 40);

	mSceneText.push_back(mHeader);
	mSceneText.push_back(mHeaderInstruction);
	mSceneText.push_back(mFlavourText1);
	mSceneText.push_back(mFlavourText2);
	mSceneText.push_back(mFlavourText3);
	mSceneText.push_back(mFooterInstruction);
}


void ClassPickerScene::SetUpWarriorView()
{
	pWarriorIcon->SetPos(std::make_pair(640, 320));

	pRogueIcon->SetVisible(false);
	pMageIcon->SetVisible(false);
	pRejectBtn->SetVisible(true);
	pYesBtn->SetVisible(true);

	mSceneText.clear();

	mHeader.text = "CHARACTER CREATOR";
	mHeader.pos = std::make_pair<int>(640, 230);
	mHeader.textColor = SDL_Color{ 0,0,0 };
	mHeader.SetTextScale(300, 60);

	mHeaderInstruction.text = "WILL YOU PICK WARRIOR?";
	mHeaderInstruction.textColor = SDL_Color{ 0,0,0 };
	mHeaderInstruction.pos = std::make_pair<int>(640, 270);
	mHeaderInstruction.SetTextScale(250, 40);

	mFlavourText1.text = "INTELLIGENCE - 1";
	mFlavourText1.textColor = SDL_Color{ 0,0,0 };
	mFlavourText1.pos = std::make_pair<int>(640, 400);
	mFlavourText1.SetTextScale(100, 30);

	mFlavourText2.text = "STRENGTH + 2";
	mFlavourText2.textColor = SDL_Color{ 0,0,0 };
	mFlavourText2.pos = std::make_pair<int>(640, 370);
	mFlavourText2.SetTextScale(100, 30);

	mFlavourText3.text = "A WARRIOR'S STRENGTH IS THEIR... STRENGTH";
	mFlavourText3.textColor = SDL_Color{ 0,0,0 };
	mFlavourText3.pos = std::make_pair<int>(640, 430);
	mFlavourText3.SetTextScale(300, 30);

	mFooterInstruction.text = "PLEASE SELECT YOUR CHOICE WITH THE LEFT MOUSE BUTTON";
	mFooterInstruction.textColor = SDL_Color{ 0,0,0 };
	mFooterInstruction.pos = std::make_pair<int>(640, 550);
	mFooterInstruction.SetTextScale(500, 70);

	mSceneText.push_back(mHeader);
	mSceneText.push_back(mHeaderInstruction);
	mSceneText.push_back(mFlavourText1);
	mSceneText.push_back(mFlavourText2);
	mSceneText.push_back(mFlavourText3);
	mSceneText.push_back(mFooterInstruction);


}

void ClassPickerScene::SetUpRogueView()
{
	pRogueIcon->SetPos(std::make_pair(640, 320));
	
	pWarriorIcon->SetVisible(false);
	pMageIcon->SetVisible(false);
	pRejectBtn->SetVisible(true);
	pYesBtn->SetVisible(true);

	mSceneText.clear();

	mHeader.text = "CHARACTER CREATOR";
	mHeader.pos = std::make_pair<int>(640, 230);
	mHeader.textColor = SDL_Color{ 0,0,0 };
	mHeader.SetTextScale(300, 60);

	mHeaderInstruction.text = "WILL YOU PICK ROGUE?";
	mHeaderInstruction.textColor = SDL_Color{ 0,0,0 };
	mHeaderInstruction.pos = std::make_pair<int>(640, 270);
	mHeaderInstruction.SetTextScale(250, 40);

	mFlavourText1.text = "STRENGTH - 1";
	mFlavourText1.textColor = SDL_Color{ 0,0,0 };
	mFlavourText1.pos = std::make_pair<int>(640, 400);
	mFlavourText1.SetTextScale(100, 30);

	mFlavourText2.text = "AGILITY + 2";
	mFlavourText2.textColor = SDL_Color{ 0,0,0 };
	mFlavourText2.pos = std::make_pair<int>(640, 370);
	mFlavourText2.SetTextScale(100, 30);

	mFlavourText3.text = "ROGUES FIGHT WITH SPEED AND CUNNING TO DEAL A KILLER BLOW";
	mFlavourText3.textColor = SDL_Color{ 0,0,0 };
	mFlavourText3.pos = std::make_pair<int>(640, 430);
	mFlavourText3.SetTextScale(300, 30);

	mFooterInstruction.text = "PLEASE SELECT YOUR CHOICE WITH THE LEFT MOUSE BUTTON";
	mFooterInstruction.textColor = SDL_Color{ 0,0,0 };
	mFooterInstruction.pos = std::make_pair<int>(640, 550);
	mFooterInstruction.SetTextScale(500, 70);

	mSceneText.push_back(mHeader);
	mSceneText.push_back(mHeaderInstruction);
	mSceneText.push_back(mFlavourText1);
	mSceneText.push_back(mFlavourText2);
	mSceneText.push_back(mFlavourText3);
	mSceneText.push_back(mFooterInstruction);

}

void ClassPickerScene::SetUpMageView()
{
	pMageIcon->SetPos(std::make_pair(640, 320));

	pWarriorIcon->SetVisible(false);
	pRogueIcon->SetVisible(false);
	pRejectBtn->SetVisible(true);
	pYesBtn->SetVisible(true);

	mSceneText.clear();

	mHeader.text = "CHARACTER CREATOR";
	mHeader.pos = std::make_pair<int>(640, 230);
	mHeader.textColor = SDL_Color{ 0,0,0 };
	mHeader.SetTextScale(300, 60);

	mHeaderInstruction.text = "WILL YOU PICK MAGE?";
	mHeaderInstruction.textColor = SDL_Color{ 0,0,0 };
	mHeaderInstruction.pos = std::make_pair<int>(640, 270);
	mHeaderInstruction.SetTextScale(250, 40);

	mFlavourText1.text = "AGILITY - 1";
	mFlavourText1.textColor = SDL_Color{ 0,0,0 };
	mFlavourText1.pos = std::make_pair<int>(640, 400);
	mFlavourText1.SetTextScale(100, 30);

	mFlavourText2.text = "INTELLIGENCE + 2";
	mFlavourText2.textColor = SDL_Color{ 0,0,0 };
	mFlavourText2.pos = std::make_pair<int>(640, 370);
	mFlavourText2.SetTextScale(100, 30);

	mFlavourText3.text = "MAGES DESTROY FOES WITH WEAPONISED INTELLECT";
	mFlavourText3.textColor = SDL_Color{ 0,0,0 };
	mFlavourText3.pos = std::make_pair<int>(640, 430);
	mFlavourText3.SetTextScale(300, 30);


	mFooterInstruction.text = "PLEASE SELECT YOUR CHOICE WITH THE LEFT MOUSE BUTTON";
	mFooterInstruction.textColor = SDL_Color{ 0,0,0 };
	mFooterInstruction.pos = std::make_pair<int>(640, 550);
	mFooterInstruction.SetTextScale(500, 70);

	mSceneText.push_back(mHeader);
	mSceneText.push_back(mHeaderInstruction);
	mSceneText.push_back(mFlavourText1);
	mSceneText.push_back(mFlavourText2);
	mSceneText.push_back(mFlavourText3);
	mSceneText.push_back(mFooterInstruction);
}

void ClassPickerScene::SetUpBackgroundView()
{
	pWarriorIcon->SetVisible(false);
	pRogueIcon->SetVisible(false);
	pMageIcon->SetVisible(false);
	pRejectBtn->SetVisible(false);
	pYesBtn->SetVisible(false);

	pVillagerIcon->SetVisible(true);
	pScholarIcon->SetVisible(true);
	pNobleIcon->SetVisible(true);

	pVillagerIcon->SetPos(std::make_pair(320, 360));
	pScholarIcon->SetPos(std::make_pair(640, 360));
	pNobleIcon->SetPos(std::make_pair(960, 360));

	mSceneText.clear();

	mHeader.text = "CHARACTER CREATOR: " + std::to_string(PartyCount + 1);
	mHeader.pos = std::make_pair<int>(640, 230);
	mHeader.textColor = SDL_Color{ 0,0,0 };
	mHeader.SetTextScale(300, 60);

	mHeaderInstruction.text = "CHOOSE YOUR ORIGIN";
	mHeaderInstruction.textColor = SDL_Color{ 0,0,0 };
	mHeaderInstruction.pos = std::make_pair<int>(640, 270);
	mHeaderInstruction.SetTextScale(250, 40);

	mFlavourText1.text = "VILLAGER";
	mFlavourText1.textColor = SDL_Color{ 0,0,0 };
	mFlavourText1.pos = std::make_pair<int>(320, 410);
	mFlavourText1.SetTextScale(100, 30);

	mFlavourText2.text = "SCHOLAR";
	mFlavourText2.textColor = SDL_Color{ 0,0,0 };
	mFlavourText2.pos = std::make_pair<int>(640, 410);
	mFlavourText2.SetTextScale(100, 30);

	mFlavourText3.text = "NOBLE";
	mFlavourText3.textColor = SDL_Color{ 0,0,0 };
	mFlavourText3.pos = std::make_pair<int>(960, 410);
	mFlavourText3.SetTextScale(100, 30);

	mFooterInstruction.text = "PLEASE SELECT YOUR CHOICE WITH THE LEFT MOUSE BUTTON";
	mFooterInstruction.textColor = SDL_Color{ 0,0,0 };
	mFooterInstruction.pos = std::make_pair<int>(640, 550);
	mFooterInstruction.SetTextScale(700, 40);

	mSceneText.push_back(mHeader);
	mSceneText.push_back(mHeaderInstruction);
	mSceneText.push_back(mFlavourText1);
	mSceneText.push_back(mFlavourText2);
	mSceneText.push_back(mFlavourText3);
	mSceneText.push_back(mFooterInstruction);
}

void ClassPickerScene::SetUpVillagerView()
{

	pVillagerIcon->SetPos(std::make_pair(640, 320));

	pScholarIcon->SetVisible(false);
	pNobleIcon->SetVisible(false);
	pRejectBtn->SetVisible(true);
	pYesBtn->SetVisible(true);

	mSceneText.clear();

	mHeader.text = "CHARACTER CREATOR";
	mHeader.pos = std::make_pair<int>(640, 230);
	mHeader.textColor = SDL_Color{ 0,0,0 };
	mHeader.SetTextScale(300, 60);

	mHeaderInstruction.text = "WILL YOU PICK VILLAGER?";
	mHeaderInstruction.textColor = SDL_Color{ 0,0,0 };
	mHeaderInstruction.pos = std::make_pair<int>(640, 270);
	mHeaderInstruction.SetTextScale(250, 40);

	mFlavourText1.text = "INTELLIGENCE - 2";
	mFlavourText1.textColor = SDL_Color{ 0,0,0 };
	mFlavourText1.pos = std::make_pair<int>(640, 400);
	mFlavourText1.SetTextScale(100, 30);

	mFlavourText2.text = "STRENGTH, AGILITY + 2";
	mFlavourText2.textColor = SDL_Color{ 0,0,0 };
	mFlavourText2.pos = std::make_pair<int>(640, 370);
	mFlavourText2.SetTextScale(100, 30);

	mFlavourText3.text = "STARTING GOLD: 50";
	mFlavourText3.textColor = SDL_Color{ 0,0,0 };
	mFlavourText3.pos = std::make_pair<int>(640, 430);
	mFlavourText3.SetTextScale(100, 30);

	mFlavourText4.text = "A COMMONER LIVES A SIMPLE LIFE WON WITH THEIR OWN HANDS";
	mFlavourText4.textColor = SDL_Color{ 0,0,0 };
	mFlavourText4.pos = std::make_pair<int>(640, 430);
	mFlavourText4.SetTextScale(300, 30);

	mFooterInstruction.text = "PLEASE SELECT YOUR CHOICE WITH THE LEFT MOUSE BUTTON";
	mFooterInstruction.textColor = SDL_Color{ 0,0,0 };
	mFooterInstruction.pos = std::make_pair<int>(640, 550);
	mFooterInstruction.SetTextScale(500, 70);

	mSceneText.push_back(mHeader);
	mSceneText.push_back(mHeaderInstruction);
	mSceneText.push_back(mFlavourText1);
	mSceneText.push_back(mFlavourText2);
	mSceneText.push_back(mFlavourText3);
	mSceneText.push_back(mFlavourText4);
	mSceneText.push_back(mFooterInstruction);

}

void ClassPickerScene::SetUpScholarView()
{
	pScholarIcon->SetPos(std::make_pair(640, 320));

	pVillagerIcon->SetVisible(false);
	pNobleIcon->SetVisible(false);
	pRejectBtn->SetVisible(true);
	pYesBtn->SetVisible(true);

	mSceneText.clear();

	mHeader.text = "CHARACTER CREATOR";
	mHeader.pos = std::make_pair<int>(640, 230);
	mHeader.textColor = SDL_Color{ 0,0,0 };
	mHeader.SetTextScale(300, 60);

	mHeaderInstruction.text = "WILL YOU PICK SCHOLAR?";
	mHeaderInstruction.textColor = SDL_Color{ 0,0,0 };
	mHeaderInstruction.pos = std::make_pair<int>(640, 270);
	mHeaderInstruction.SetTextScale(250, 40);

	mFlavourText1.text = "INTELLIGENCE + 1";
	mFlavourText1.textColor = SDL_Color{ 0,0,0 };
	mFlavourText1.pos = std::make_pair<int>(640, 400);
	mFlavourText1.SetTextScale(100, 30);

	mFlavourText2.text = "STARTING GOLD: 100 ";
	mFlavourText2.textColor = SDL_Color{ 0,0,0 };
	mFlavourText2.pos = std::make_pair<int>(640, 370);
	mFlavourText2.SetTextScale(100, 30);

	mFlavourText3.text = "A SCHOLAR ENJOYS A LIFE OF LEARNING AND CREATURE COMFORTS";
	mFlavourText3.textColor = SDL_Color{ 0,0,0 };
	mFlavourText3.pos = std::make_pair<int>(640, 430);
	mFlavourText3.SetTextScale(300, 30);

	mFooterInstruction.text = "PLEASE SELECT YOUR CHOICE WITH THE LEFT MOUSE BUTTON";
	mFooterInstruction.textColor = SDL_Color{ 0,0,0 };
	mFooterInstruction.pos = std::make_pair<int>(640, 550);
	mFooterInstruction.SetTextScale(500, 70);

	mSceneText.push_back(mHeader);
	mSceneText.push_back(mHeaderInstruction);
	mSceneText.push_back(mFlavourText1);
	mSceneText.push_back(mFlavourText2);
	mSceneText.push_back(mFlavourText3);
	mSceneText.push_back(mFooterInstruction);
}

void ClassPickerScene::SetUpNobleView()
{

	pVillagerIcon->SetPos(std::make_pair(640, 320));

	pScholarIcon->SetVisible(false);
	pNobleIcon->SetVisible(false);
	pRejectBtn->SetVisible(true);
	pYesBtn->SetVisible(true);

	mSceneText.clear();

	mHeader.text = "CHARACTER CREATOR";
	mHeader.pos = std::make_pair<int>(640, 230);
	mHeader.textColor = SDL_Color{ 0,0,0 };
	mHeader.SetTextScale(300, 60);

	mHeaderInstruction.text = "WILL YOU PICK VILLAGER?";
	mHeaderInstruction.textColor = SDL_Color{ 0,0,0 };
	mHeaderInstruction.pos = std::make_pair<int>(640, 270);
	mHeaderInstruction.SetTextScale(250, 40);

	mFlavourText1.text = "STRENGTH, AGILITY + 2 ";
	mFlavourText1.textColor = SDL_Color{ 0,0,0 };
	mFlavourText1.pos = std::make_pair<int>(640, 400);
	mFlavourText1.SetTextScale(100, 30);

	mFlavourText2.text = "INTELLIGENCE - 2";
	mFlavourText2.textColor = SDL_Color{ 0,0,0 };
	mFlavourText2.pos = std::make_pair<int>(640, 370);
	mFlavourText2.SetTextScale(100, 30);

	mFlavourText3.text = "STARTING GOLD: 150";
	mFlavourText3.textColor = SDL_Color{ 0,0,0 };
	mFlavourText3.pos = std::make_pair<int>(640, 430);
	mFlavourText3.SetTextScale(100, 30);

	mFlavourText4.text = "A NOBLE'S LIFE OF LEISURE HAS LED TO A STRONG MIND BUT A WEAK BODY";
	mFlavourText4.textColor = SDL_Color{ 0,0,0 };
	mFlavourText4.pos = std::make_pair<int>(640, 430);
	mFlavourText4.SetTextScale(300, 30);

	mFooterInstruction.text = "PLEASE SELECT YOUR CHOICE WITH THE LEFT MOUSE BUTTON";
	mFooterInstruction.textColor = SDL_Color{ 0,0,0 };
	mFooterInstruction.pos = std::make_pair<int>(640, 550);
	mFooterInstruction.SetTextScale(500, 70);

	mSceneText.push_back(mHeader);
	mSceneText.push_back(mHeaderInstruction);
	mSceneText.push_back(mFlavourText1);
	mSceneText.push_back(mFlavourText2);
	mSceneText.push_back(mFlavourText3);
	mSceneText.push_back(mFlavourText4);
	mSceneText.push_back(mFooterInstruction);
}
