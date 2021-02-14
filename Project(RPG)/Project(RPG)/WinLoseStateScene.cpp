#include "WinLoseStateScene.h"

WinLoseStateScene::WinLoseStateScene(Interface* mObjMgr) : Scene(mgr)
{
	pBackground = AddObject("scrollBgObj", 640, 360, Map);

	pMenuButton = AddObject("menuButtonObj", 800, 510, UI);
	pMenuButton->SetVisible(false);

	pQuitButton = AddObject("exitButtonObj", 480, 510, UI);
	pQuitButton->SetVisible(false);

	Victory_Music = Mix_LoadMUS("Assets/Music/VictoryWindlessSlopes.mp3");
	Defeat_Music = Mix_LoadMUS("Assets/Music/Game-over-silence.mp3");

	Victory_Sfx = Mix_LoadWAV("Assets/SFX/VictorySfx.wav");
	Button_Sfx = Mix_LoadWAV("Assets/SFX/GenericClick.wav");

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

	if (act == Act::MouseUpdate)
	{
		if (pQuitButton->InBounds(mousePos.first, mousePos.second))
		{
			OnHover(pQuitButton);
		}

		if (pMenuButton->InBounds(mousePos.first, mousePos.second))
		{
			OnHover(pMenuButton);
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

void WinLoseStateScene::SetUpLoseState()
{

	pLeftSprite->tint = DimGray;
	pCentreSprite->tint = DimGray;
	pLeftSprite->tint = DimGray;
	
	pMenuButton->SetVisible(true);
	pQuitButton->SetVisible(true);

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
}


