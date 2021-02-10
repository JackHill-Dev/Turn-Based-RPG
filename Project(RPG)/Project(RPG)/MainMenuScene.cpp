#include "MainMenuScene.h"
#include "json.hpp"
MainMenuScene::MainMenuScene(Interface* rng) : Scene(rng)
{
	// Get all main menu button objects
	start  = AddObject("StartBtnObj", 70, 90, UI);
	quit = AddObject("quitBtnObj", 70, 400, UI);
	settings = AddObject("settingsBtnObj", 70, 250, UI);

	// Get Background object
	AddObject("mainMenuBGObj", 1280 / 2, 720 / 2, Background);

	mStartMus = Mix_LoadMUS("Assets/Music/GameStart.mp3");
	confirm_SFX = Mix_LoadWAV("Assets/SFX/confirmSound.wav");
	back_SFX = Mix_LoadWAV("Assets/SFX/BackSound.wav");

	mgr->FadeInMusic(mStartMus, -1, mgr->fadeTime); // Cheeky solution as this one starts as current scene without using load scene method - EH
}

void MainMenuScene::Load()
{
	if (mgr->GetPreviousScene() != Scenes::SettingsPage)
	{
		mgr->FadeInMusic(mStartMus, -1, mgr->fadeTime);
	}
}

void MainMenuScene::Update(double dTime, Act act, std::pair<int, int> mouse)
{
	
	if (act == Act::Click)
	{
		if (start->InBounds(mouse.first, mouse.second) && start->IsActive())
		{
			mgr->PlaySFX(confirm_SFX, 0, 1);
			mgr->LoadScene(Scenes::ClassPicker);
		}

		if (quit->InBounds(mouse.first, mouse.second) && quit->IsActive())
		{
			mgr->Quit();
		}
		
		if (settings->InBounds(mouse.first, mouse.second) && settings->IsActive())
		{
			mgr->PlaySFX(confirm_SFX, 0, 1);
			mgr->LoadScene(Scenes::SettingsPage);
		}

	}

}







