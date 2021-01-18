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

}

void MainMenuScene::Update(double dTime, Act act, std::pair<int, int> mouse)
{
	
	if (act == Act::Click)
	{
		if (start->InBounds(mouse.first, mouse.second) && start->IsActive())
			mgr->LoadScene(Scenes::Overworld);

		if (quit->InBounds(mouse.first, mouse.second) && quit->IsActive())
			mgr->Quit();
		
		if (settings->InBounds(mouse.first, mouse.second) && settings->IsActive())
			mgr->LoadScene(5);

	}

}





