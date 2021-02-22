#include "MainMenuScene.h"
#include "json.hpp"

RenderObject* LoadButton;

nlohmann::json saveFile;
MainMenuScene::MainMenuScene(Interface* rng) : Scene(rng)
{

	// Get all main menu button objects
	start  = AddObject("newGameButtonObj", 110, 100, UI);
	LoadButton = AddObject("ContinueButtonObj", 110, 170, UI);
	settings = AddObject("settingsBtnObj", 110, 240, UI);
	quit = AddObject("quitBtnObj", 110, 310, UI);


	buttons.push_back(start);
	buttons.push_back(quit);
	buttons.push_back(settings);
	
	// Get Background object
	AddObject("mainMenuBGObj", 640, 360, Background);

	mStartMus = Mix_LoadMUS("Assets/Music/GameStart.mp3");
	confirm_SFX = Mix_LoadWAV("Assets/SFX/confirmSound.wav");
	back_SFX = Mix_LoadWAV("Assets/SFX/BackSound.wav");
	
	mgr->FadeInMusic(mStartMus, -1, mgr->fadeTime); // Cheeky solution as this one starts as current scene without using load scene method - EH

	buttons.push_back(LoadButton);

	if (mgr->GetSeed() != 0)
	{
		LoadButton->SetVisible(true);
	}
	else
	{
		settings->SetPos({ 110,170 });
		quit->SetPos({ 110,240 });
		LoadButton->SetPos({110,310});
		LoadButton->SetVisible(false);
	}
}

void MainMenuScene::Load()
{

	//std::ifstream ifs("Savedata.json");

	if (mgr->GetSeed() != 0)
	{
		LoadButton->SetPos({110,170});
		settings->SetPos({110,240});
		quit->SetPos({110,310});
		LoadButton->SetVisible(true);
	}
	else
	{
		settings->SetPos({ 110,170 });
		quit->SetPos({ 110,240 });
		LoadButton->SetPos({ 110,310 });
		LoadButton->SetVisible(false);
	}

	
	if (mgr->GetPreviousScene() != Scenes::SettingsPage)
	{
		mgr->FadeInMusic(mStartMus, -1, mgr->fadeTime);
	}
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
		if (start->InBounds(mouse.first, mouse.second) && start->IsVisible() == true)
		{
			mgr->PlaySFX(confirm_SFX, 0, 1);
			mgr->LoadScene(Scenes::ClassPicker);
			OnLeave(start);
		}

		else if (quit->InBounds(mouse.first, mouse.second) && quit->IsVisible() == true)
		{
			mgr->Quit();
		}
		
		else if (settings->InBounds(mouse.first, mouse.second) && settings->IsVisible() == true)
		{
			mgr->PlaySFX(confirm_SFX, 0, 1);
			mgr->LoadScene(Scenes::SettingsPage);
			OnLeave(settings);
		}
		else if (LoadButton->InBounds(mouse.first, mouse.second) && LoadButton->IsVisible() == true)
		{
			mgr->PlaySFX(confirm_SFX, 0, 1);
			mgr->LoadScene(Scenes::Overworld);
			OnLeave(LoadButton);
		}

	}

}







