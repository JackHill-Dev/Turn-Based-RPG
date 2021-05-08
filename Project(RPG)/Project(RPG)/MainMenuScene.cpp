#include "MainMenuScene.h"
#include "json.hpp"

RenderObject* LoadButton;

nlohmann::json saveFile;
MainMenuScene::MainMenuScene(Interface* rng) : Scene(rng)
{

	// Get all main menu button objects
	//pMenuBg = AddObject("ChalkBoardObj", 640, 360, Layer::Background);
	pNoughtsAndCrossesGraphic = AddObject("tictactoeObj", 640, 360, Layer::Game);
	pBanner = AddObject("NoughtsAndCrossesBannerObj", 640, 220, Layer::UI);

	pStartButton  = AddObject("StartButtonObj", 630, 300, UI);
	pHostGameButton = AddObject("HostGameButtonObj", 630, 370, UI);
	pJoinGameButton = AddObject("JoinButtonObj", 630, 440, UI);

	pQuitButton = AddObject("QuitButtonObj", 630, 580, UI);
	pQuitButton->SetScale({ 1.5,1.2 });


	buttons.push_back(pStartButton);
	buttons.push_back(pHostGameButton);
	buttons.push_back(pJoinGameButton);
	buttons.push_back(pQuitButton);
	

	//mStartMus = Mix_LoadMUS("Assets/Music/GameStart.mp3");
	confirm_SFX = Mix_LoadWAV("Assets/SFX/confirmSound.wav");
	back_SFX = Mix_LoadWAV("Assets/SFX/BackSound.wav");

	//mgr->FadeInMusic(mStartMus, -1, mgr->fadeTime); // Cheeky solution as this one starts as current scene without using load scene method - EH

	
}

void MainMenuScene::Load()
{
	
	/*(mStartMus = Mix_LoadMUS("Assets/Music/GameStart.mp3");
	confirm_SFX = Mix_LoadWAV("Assets/SFX/confirmSound.wav");
	back_SFX = Mix_LoadWAV("Assets/SFX/BackSound.wav");*/
}

void MainMenuScene::OnHover(RenderObject* rObj)
{
	rObj->tint = SDL_Color{ 0,255,0 };
}

void MainMenuScene::OnLeave(RenderObject* rObj)
{
	rObj->Untint();
}

void MainMenuScene::Update(double dTime, Act act, std::pair<int, int> mouse)
{

	if (act == Act::MouseUpdate)
	{
		for (auto button : buttons)
		{
			if (button->InBounds(mouse.first, mouse.second))
			{
				OnHover(button);
			}
			else
			{
				OnLeave(button);
			}
		}
	}
	
	if (act == Act::Click)
	{
		if (pStartButton->InBounds(mouse.first, mouse.second) && pStartButton->IsVisible() == true)
		{
			mgr->LoadScene(Scenes::NoughtsAndCrosses);
			mgr->PlaySFX(confirm_SFX, 0, 1);
		}

		else if (pHostGameButton->InBounds(mouse.first, mouse.second) && pHostGameButton->IsVisible() == true)
		{

		}

		else if (pJoinGameButton->InBounds(mouse.first, mouse.second) && pJoinGameButton->IsVisible() == true)
		{

		}

		else if (pQuitButton->InBounds(mouse.first, mouse.second) && pQuitButton->IsVisible() == true)
		{			
			mgr->Quit();
		}
	}
}







