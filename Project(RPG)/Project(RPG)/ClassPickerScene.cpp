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

	pBackBtn = AddObject("backBtnObj", 140, 230, UI);

	pYesBtn = AddObject("yesTxtBtnObj", 800, 480, UI);
	pRejectBtn = AddObject("backTxtBtnObj", 480, 480, UI);

	Init();
}

void ClassPickerScene::Init()
{
	PartyCount = 1;
	SetUpSummaryView();
}

// Colour the object green 
/*(mPlayer.SetupParty(
	{ new Character("maleObj", "WizardObj"), 
	new Character("maleObj", "ClericObj"),
	new Character("maleObj", "RogueObj"),
	new Character("maleObj", "WarriorObj") });
*/
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
			if (IsFocused)
			{
				SetUpSummaryView();
				IsFocused = false;
				IsWarriorView = false;
				IsRogueView = false;
				IsMageView = false;
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

		if (pWarriorIcon->InBounds(mousePos.first, mousePos.second) && pWarriorIcon->IsVisible())
		{
			IsFocused = true;
			IsWarriorView = true;
			OnLeave(pWarriorIcon);
			SetUpWarriorView();
			
		}

		if (pRogueIcon->InBounds(mousePos.first, mousePos.second) && pRogueIcon->IsVisible())
		{
			IsFocused = true;
			IsRogueView = true;
			OnLeave(pRogueIcon);
			SetUpRogueView();		
		}

		if (pMageIcon->InBounds(mousePos.first, mousePos.second) && pMageIcon->IsVisible())
		{
			IsFocused = true;
			IsMageView = true;
			OnLeave(pMageIcon);
			SetUpMageView();			
		}

		if (pRejectBtn->InBounds(mousePos.first, mousePos.second) && pRejectBtn->IsVisible())
		{
			SetUpSummaryView();
			IsFocused = false;
			IsWarriorView = false;
			IsRogueView = false;
			IsMageView = false;
		}

		if (pYesBtn->InBounds(mousePos.first, mousePos.second) && pYesBtn->IsVisible())
		{
			// create a local vector of characters, push into that, then use setupParty
			if (PartyCount <= 3)
			{
				
				
				if (IsWarriorView)
				{
					//mgr->GetPlayer()->AddToParty(new Character("warSprObj", "WarriorObj"));
					mCharacters.push_back(new Character("warSprObj", "WarriorObj"));
				}
				if (IsRogueView)
				{
					//mgr->GetPlayer()->AddToParty(new Character("rogSprObj", "RogueObj"));
					mCharacters.push_back(new Character("rogSprObj", "RogueObj"));
				}
				if (IsMageView)
				{
					//mgr->GetPlayer()->AddToParty(new Character("mageSprObj", "ClericObj"));
					mCharacters.push_back(new Character("mageSprObj", "ClericObj"));				
				}
				++PartyCount;
				SetUpSummaryView();
				IsFocused = false;
				IsWarriorView = false;
				IsRogueView = false;
				IsMageView = false;

			}
			else
			{
				mgr->GetPlayer()->SetupParty(mCharacters);
				mgr->LoadScene(Scenes::Overworld);
			}
		}

	}

}

void ClassPickerScene::SetUpSummaryView()
{
	pWarriorIcon->SetVisible(true);
	pRogueIcon->SetVisible(true);
	pMageIcon->SetVisible(true);
	pRejectBtn->SetVisible(false);
	pYesBtn->SetVisible(false);

	pWarriorIcon->SetPos(std::make_pair(320, 360));
	pRogueIcon->SetPos(std::make_pair(640, 360));
	pMageIcon->SetPos(std::make_pair(960, 360));

	mSceneText.clear();

	mHeader.text = "CHARACTER CREATOR: " + std::to_string(PartyCount);
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
