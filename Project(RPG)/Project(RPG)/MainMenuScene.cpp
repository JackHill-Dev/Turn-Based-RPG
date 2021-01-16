#include "MainMenuScene.h"

MainMenuScene::MainMenuScene(Interface* rng) : Scene(rng)
{
	// Get all main menu button objects
	start  = AddObject("StartBtnObj", 70, 90, UI);
	quit = AddObject("quitBtnObj", 70, 400, UI);
	settings = AddObject("settingsBtnObj", 70, 250, UI);

	// Get Background object
	AddObject("mainMenuBGObj", 1280 / 2, 720 / 2, Background);

	SetupSettings();

	// Get all SFX objects
	// Get Music object
	// Play music on loop (set loops to -1)

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
			ShowSettings(true);

		UpdateSettings(act, mouse);
	}

	
}

void MainMenuScene::SetupSettings()
{
	settingsOverlay = AddObject("settingsOverlayObj", 640, 360, Background);
	SettingsCloseBtn = AddObject("CloseBtnObj", 940, 140, UI);
	dropDownCollapsed = AddObject("resCollapsedObj", 640, 300, UI);
	dropDownUnCollapsed = AddObject("resUnCollapsedObj", 640, 330, UI);

	settingsOverlay->SetVisible(false);
	SettingsCloseBtn->SetVisible(false);
	SettingsCloseBtn->SetActive(false);
	dropDownCollapsed->SetVisible(false);
	dropDownUnCollapsed->SetVisible(false);
}

void MainMenuScene::UpdateSettings(Act act, std::pair<int, int> mouse)
{
	if (SettingsCloseBtn->InBounds(mouse.first, mouse.second) && SettingsCloseBtn->IsActive())
	{
		ShowSettings(false);
	}

	if (dropDownCollapsed->InBounds(mouse.first, mouse.second) && dropDownCollapsed->IsActive())
		Collapse(false);
	else 
		if (settingsOverlay->InBounds(mouse.first, mouse.second) && !SettingsCloseBtn->InBounds(mouse.first, mouse.second))
		{
			if (settingsOverlay->IsVisible())
			{
				Collapse(true);
			}
		}

}

void MainMenuScene::ShowSettings( bool actvis)
{
	start->SetActive(!actvis);
	quit->SetActive(!actvis);
	settings->SetActive(!actvis);

	settingsOverlay->SetVisible(actvis);
	SettingsCloseBtn->SetVisible(actvis);
	dropDownCollapsed->SetVisible(actvis);

	SettingsCloseBtn->SetActive(actvis);
	dropDownUnCollapsed->SetActive(actvis);
	dropDownCollapsed->SetActive(actvis);
}

void MainMenuScene::Collapse(bool collapsed)
{
	dropDownUnCollapsed->SetVisible(!collapsed);
	dropDownUnCollapsed->SetActive(!collapsed);
	dropDownCollapsed->SetVisible(collapsed);
	dropDownCollapsed->SetActive(collapsed);
}

