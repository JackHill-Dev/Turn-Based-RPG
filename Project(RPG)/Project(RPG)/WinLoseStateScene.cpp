#include "WinLoseStateScene.h"

WinLoseStateScene::WinLoseStateScene(Interface* mObjMgr) : Scene(mObjMgr)
{
	pBackground = AddObject("scrollBgObj", 640, 360, Map);

	pMenuButton = AddObject("menuButtonObj", 800, 510, UI);
	pMenuButton->SetVisible(false);

	pQuitButton = AddObject("exitButtonObj", 480, 510, UI);
	pQuitButton->SetVisible(false);

	pContinueButton = AddObject("ContinueButtonObj", 640, 510, UI);
	pContinueButton->SetScale({ 2,2 });
	pContinueButton->SetVisible(false);

	pConfirmButton = AddObject("ConfirmButtonObj", 800, 510, UI);
	pConfirmButton->SetScale({ 2,2 });
	pConfirmButton->SetVisible(false);

	pRejectButton = AddObject("resetButtonObj", 480, 510, UI);
	pRejectButton->SetScale({ 2,2 });
	pRejectButton->SetVisible(false);

	StrengthButton = AddObject("upButtonObj", 780, 440, UI);
	StrengthButton->SetScale({ 2, 2 });
	AgilityButton = AddObject("upButtonObj", 780, 470, UI);
	AgilityButton->SetScale({ 2, 2 });
	IntelligenceButton = AddObject("upButtonObj", 780, 500, UI);
	IntelligenceButton->SetScale({ 2, 2 });

	pStatButtons.push_back(StrengthButton);
	pStatButtons.push_back(AgilityButton);
	pStatButtons.push_back(IntelligenceButton);

	pAllButtons.push_back(pMenuButton);
	pAllButtons.push_back(pQuitButton);
	pAllButtons.push_back(pContinueButton);
	pAllButtons.push_back(pConfirmButton);
	pAllButtons.push_back(pRejectButton);
	pAllButtons.push_back(StrengthButton);
	pAllButtons.push_back(AgilityButton);
	pAllButtons.push_back(IntelligenceButton);

	for (auto button : pAllButtons)
	{
		button->SetVisible(false);
	}

	Victory_Music = Mix_LoadMUS("Assets/Music/VictoryWindlessSlopes.mp3");
	Defeat_Music = Mix_LoadMUS("Assets/Music/Game-over-silence.mp3");

	Victory_Sfx = Mix_LoadWAV("Assets/SFX/VictorySfx.wav");
	Button_Sfx = Mix_LoadWAV("Assets/SFX/GenericClick.wav");
	Error_Sfx = Mix_LoadWAV("Assets/SFX/ErrorSound.wav");

}

void WinLoseStateScene::Init()
{

}

void WinLoseStateScene::Load()
{
	// Checks if any are alive(You win) or if the party is all dead(Game over) and then calls the relevant starting view,
	// Win state or lose state 
	std::vector<Character*> party = mgr->GetPlayer()->GetParty();

	for (auto member : party)
	{
		names.push_back(member->GetClassName(member->GetClass()));
	}

	for (auto button : pAllButtons)
	{
		button->SetVisible(false);
	}

	pCharacters.clear();

	pLeftSprite = AddObject(party[0]->GetObjName(), 320, 360, UI);
	pLeftSprite->SetScale(std::make_pair(2, 2));
	firstCharacter->pCharacter = party[0];
	firstCharacter->rObj = pLeftSprite;
	pCharacters.push_back(firstCharacter);

	pCentreSprite = AddObject(party[1]->GetObjName(), 640, 360, UI);
	pCentreSprite->SetScale(std::make_pair(2, 2));
	SecondCharacter->pCharacter = party[1];
	SecondCharacter->rObj = pCentreSprite;
	pCharacters.push_back(SecondCharacter);

	pRightSprite = AddObject(party[2]->GetObjName(), 960, 360, UI);
	pRightSprite->SetScale(std::make_pair(2, 2));
	ThirdCharacter->pCharacter = party[2];
	ThirdCharacter->rObj = pRightSprite;
	pCharacters.push_back(ThirdCharacter);

	if (std::any_of(party.begin(), party.end(), [party](Character* pCharacter) 
		{
			return pCharacter->GetDeadStatus() == false;
		}))
	{
		mgr->FadeInMusic(Victory_Music, -1, mgr->fadeTime);
		SetUpWinState();
	}
	else
	{
		mgr->FadeInMusic(Defeat_Music, 1, mgr->fadeTime); // This one doesn't loop - EH
		SetUpLoseState();
	}

}

void WinLoseStateScene::Update(double dTime, Act act, std::pair<int, int> mousePos)
{
	for (auto character : pCharacters)
	{
		if (character->pCharacter->hasLevelled == false)
		{
			character->rObj->Untint();
		}
	}
	pContinueButton->tint = SDL_Color{ 0,0,0 };
	pConfirmButton->tint = SDL_Color{ 0,0,0 };
	pRejectButton->tint = SDL_Color{ 0,0,0 };

	if (act == Act::MouseUpdate)
	{
		for (auto button : pAllButtons)
		{
			if (button->InBounds(mousePos.first, mousePos.second))
			{
				OnHover(button);
			}
		}
	}

	if (act == Act::Click)
	{
		if (pMenuButton->InBounds(mousePos.first, mousePos.second))
		{
			mgr->PlaySFX(Button_Sfx, 0, 1);
			mgr->LoadScene(Scenes::MainMenu);
		}
		if (pQuitButton->InBounds(mousePos.first, mousePos.second))
		{
			mgr->PlaySFX(Button_Sfx, 0, 1);
			mgr->Quit();
		}
		if (pContinueButton->InBounds(mousePos.first, mousePos.second) &&
			std::any_of(pCharacters.begin(), pCharacters.end(), [](PlayerCharacter* pc)
				{
					return pc->pCharacter->hasLevelled == true;
				}))
		{
			mgr->PlaySFX(Error_Sfx, 0, 1);
			mFooterInstruction.text = "PLEASE LEVEL UP ALL CHARACTERS";
		}
		else
		{
			mgr->PlaySFX(Button_Sfx, 0, 1);
			mgr->LoadScene(Scenes::Overworld);
		}

		for (auto character : pCharacters)
		{
			if (character->rObj->InBounds(mousePos.first, mousePos.second) && character->pCharacter->hasLevelled == true)
			{
				mgr->PlaySFX(Button_Sfx, 0, 1);
				SetUpLevelUpState(character);
			}
			else
			{
				mgr->PlaySFX(Error_Sfx, 0, 1);
			}
		}

		if (StrengthButton->InBounds(mousePos.first, mousePos.second) && statPoints != 0)
		{

		}

		if (AgilityButton->InBounds(mousePos.first, mousePos.second) && statPoints != 0)
		{

		}

		if (IntelligenceButton->InBounds(mousePos.first, mousePos.second) && statPoints != 0)
		{

		}

		if (pConfirmButton->InBounds(mousePos.first, mousePos.second) && statPoints == 0)
		{
			SetUpWinState();
		}


	}
}

void WinLoseStateScene::OnHover(RenderObject* rObj)
{
	rObj->Tint(Lime);
}

void WinLoseStateScene::OnLeave(RenderObject* rObj)
{
	rObj->Untint();
}

void WinLoseStateScene::SetUpWinState()
{
	int dividedXp = mgr->GetPlayer()->GetXpPool() / pCharacters.size();

	pContinueButton->SetVisible(true);
	pConfirmButton->SetVisible(false);
	pRejectButton->SetVisible(false);

	for (auto button : pStatButtons)
	{
		button->SetVisible(false);
	}

	pLeftSprite->SetPos({320, 360});
	pCentreSprite->SetPos({640, 360});
	pRightSprite->SetPos({960, 360});


	for (auto character : pCharacters)
	{
		character->pCharacter->modStat(character->pCharacter->GetStats().experience, {dividedXp, 0});

		if (character->pCharacter->GetStats().experience.second <= character->pCharacter->GetStats().experience.first)
		{
			character->rObj->tint = Gold;
			character->pCharacter->hasLevelled = true;
		}

		if (character->pCharacter->GetDeadStatus() == true && character->pCharacter->hasLevelled != false)
		{
			character->rObj->tint = DimGray;
		}

	}

	mgr->GetPlayer()->ClearXpPool();
	mSceneText.clear();

	pMenuButton->SetVisible(false);
	pQuitButton->SetVisible(false);

	mHeader.text = "YOU WIN";
	mHeader.pos = std::make_pair<int>(640, 230);
	mHeader.textColor = SDL_Color{ 0,0,0 };
	mHeader.SetTextScale(300, 60);

	mHeaderInstruction.text = "SPOILS OF WAR";
	mHeaderInstruction.textColor = SDL_Color{ 0,0,0 };
	mHeaderInstruction.pos = std::make_pair<int>(640, 270);
	mHeaderInstruction.SetTextScale(250, 40);

	mFlavourText1.text = names[0];
	mFlavourText1.textColor = SDL_Color{ 0,0,0 };
	mFlavourText1.pos = std::make_pair<int>(320, 410);
	mFlavourText1.SetTextScale(100, 30);

	mFlavourText4.text = "XP + " + std::to_string(dividedXp);
	mFlavourText4.textColor = SDL_Color{ 0,0,0 };
	mFlavourText4.pos = std::make_pair<int>(320, 440);
	mFlavourText4.SetTextScale(100, 30);

	mFlavourText2.text = names[1];
	mFlavourText2.textColor = SDL_Color{ 0,0,0 };
	mFlavourText2.pos = std::make_pair<int>(640, 410);
	mFlavourText2.SetTextScale(100, 30);

	mFlavourText5.text = "XP + " + std::to_string(dividedXp);
	mFlavourText5.textColor = SDL_Color{ 0,0,0 };
	mFlavourText5.pos = std::make_pair<int>(640, 440);
	mFlavourText5.SetTextScale(100, 30);

	mFlavourText3.text = names[2];
	mFlavourText3.textColor = SDL_Color{ 0,0,0 };
	mFlavourText3.pos = std::make_pair<int>(960, 410);
	mFlavourText3.SetTextScale(100, 30);

	mFlavourText6.text = "XP + " + std::to_string(dividedXp);
	mFlavourText6.textColor = SDL_Color{ 0,0,0 };
	mFlavourText6.pos = std::make_pair<int>(960, 440);
	mFlavourText6.SetTextScale(100, 30);


	mFooterInstruction.text = "PLEASE SELECT YOUR CHOICE WITH THE LEFT MOUSE BUTTON";
	mFooterInstruction.textColor = SDL_Color{ 0,0,0 };
	mFooterInstruction.pos = std::make_pair<int>(640, 550);
	mFooterInstruction.SetTextScale(700, 40);

	mSceneText.push_back(&mHeader);
	mSceneText.push_back(&mHeaderInstruction);
	mSceneText.push_back(&mFlavourText1);
	mSceneText.push_back(&mFlavourText2);
	mSceneText.push_back(&mFlavourText3);
	mSceneText.push_back(&mFlavourText4);
	mSceneText.push_back(&mFlavourText5);
	mSceneText.push_back(&mFlavourText6);
	mSceneText.push_back(&mFooterInstruction);
}

void WinLoseStateScene::SetUpLoseState()
{

	pLeftSprite->tint = DimGray;
	pCentreSprite->tint = DimGray;
	pLeftSprite->tint = DimGray;

	pLeftSprite->SetPos({ 320, 360 });
	pCentreSprite->SetPos({ 640, 360 });
	pRightSprite->SetPos({ 960, 360 });
	
	pMenuButton->SetVisible(true);
	pQuitButton->SetVisible(true);
	mSceneText.clear();

	mHeader.text = "YOU LOSE";
	mHeader.pos = std::make_pair<int>(640, 230);
	mHeader.textColor = SDL_Color{ 0,0,0 };
	mHeader.SetTextScale(300, 60);

	mHeaderInstruction.text = "TRY AGAIN?";
	mHeaderInstruction.textColor = SDL_Color{ 0,0,0 };
	mHeaderInstruction.pos = std::make_pair<int>(640, 270);
	mHeaderInstruction.SetTextScale(250, 40);

	mFlavourText1.text = names[0];
	mFlavourText1.textColor = SDL_Color{ 0,0,0 };
	mFlavourText1.pos = std::make_pair<int>(320, 410);
	mFlavourText1.SetTextScale(100, 30);

	mFlavourText2.text = names[1];
	mFlavourText2.textColor = SDL_Color{ 0,0,0 };
	mFlavourText2.pos = std::make_pair<int>(640, 410);
	mFlavourText2.SetTextScale(100, 30);

	mFlavourText3.text = names[2];
	mFlavourText3.textColor = SDL_Color{ 0,0,0 };
	mFlavourText3.pos = std::make_pair<int>(960, 410);
	mFlavourText3.SetTextScale(100, 30);

	mFooterInstruction.text = "PLEASE SELECT YOUR CHOICE WITH THE LEFT MOUSE BUTTON";
	mFooterInstruction.textColor = SDL_Color{ 0,0,0 };
	mFooterInstruction.pos = std::make_pair<int>(640, 550);
	mFooterInstruction.SetTextScale(700, 40);

	mSceneText.push_back(&mHeader);
	mSceneText.push_back(&mHeaderInstruction);
	mSceneText.push_back(&mFlavourText1);
	mSceneText.push_back(&mFlavourText2);
	mSceneText.push_back(&mFlavourText3);
	mSceneText.push_back(&mFooterInstruction);

}

void WinLoseStateScene::SetUpLevelUpState(PlayerCharacter* pc)
{

	statPoints = 2;

	for (auto character : pCharacters)
	{
		if (character != pc)
		{
			character->rObj->SetVisible(false);
		}
	}

	pConfirmButton->SetVisible(true);
	pRejectButton->SetVisible(true);
	pContinueButton->SetVisible(false);

	for (auto button : pStatButtons)
	{
		button->SetVisible(true);
	}

	pc->rObj->SetPos({ 640,360 });

	mHeader.text = "LEVEL UP!";
	mHeader.pos = std::make_pair<int>(640, 230);
	mHeader.textColor = SDL_Color{ 0,0,0 };
	mHeader.SetTextScale(300, 60);

	mHeaderInstruction.text = pc->pCharacter->GetClassName(pc->pCharacter->GetClass()) + " GAINED A LEVEL" ;
	mHeaderInstruction.textColor = SDL_Color{ 0,0,0 };
	mHeaderInstruction.pos = std::make_pair<int>(640, 270);
	mHeaderInstruction.SetTextScale(250, 40);

	mFlavourText1.text = "STAT POINTS: " + std::to_string(statPoints);
	mFlavourText1.textColor = SDL_Color{ 0,0,0 };
	mFlavourText1.pos = std::make_pair<int>(320, 310);
	mFlavourText1.SetTextScale(100, 30);

	mFlavourText2.text = "STRENGTH:\t" + std::to_string(pc->pCharacter->GetStats().strength.second);
	mFlavourText2.textColor = SDL_Color{ 0,0,0 };
	mFlavourText2.pos = std::make_pair<int>(640, 440);
	mFlavourText2.SetTextScale(100, 30);

	mFlavourText3.text = "AGILITY:\t" + std::to_string(pc->pCharacter->GetStats().agility.second);
	mFlavourText3.textColor = SDL_Color{ 0,0,0 };
	mFlavourText3.pos = std::make_pair<int>(640, 470);
	mFlavourText3.SetTextScale(100, 30);

	mFlavourText4.text = "INTELLIGENCE:\t" + std::to_string(pc->pCharacter->GetStats().intelligence.second);
	mFlavourText4.textColor = SDL_Color{ 0,0,0 };
	mFlavourText4.pos = std::make_pair<int>(640, 500);
	mFlavourText4.SetTextScale(100, 30);

	mFooterInstruction.text = "PLEASE SELECT YOUR CHOICE WITH THE LEFT MOUSE BUTTON";
	mFooterInstruction.textColor = SDL_Color{ 0,0,0 };
	mFooterInstruction.pos = std::make_pair<int>(640, 550);
	mFooterInstruction.SetTextScale(700, 40);

	mSceneText.push_back(&mHeader);
	mSceneText.push_back(&mHeaderInstruction);
	mSceneText.push_back(&mFlavourText1);
	mSceneText.push_back(&mFlavourText2);
	mSceneText.push_back(&mFlavourText3);
	mSceneText.push_back(&mFlavourText4);
	mSceneText.push_back(&mFooterInstruction);
}


