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
	ApplyBtn = AddObject("ApplyBtnObj", 640, 550, UI);

	mFsCheckBox.obj = AddObject("checkBoxObj", 750, 200, UI);
	mFsCheckBox.obj->SetScale(std::make_pair(0.5, 0.5));
	mFsCheckBox.bIsChecked = false;


	SetupResOptions();

	settingsOverlay->SetVisible(false);
	SettingsCloseBtn->SetVisible(false);
	SettingsCloseBtn->SetActive(false);
	dropDownCollapsed->SetVisible(false);
	ApplyBtn->SetVisible(false);
	ApplyBtn->SetActive(false);
	mFsCheckBox.obj->SetActive(false);
	mFsCheckBox.obj->SetVisible(false);

}

void MainMenuScene::SetupResOptions()
{
	resOptions.push_back({ nullptr, UIText{"1920 X 1080", std::make_pair(0,0), SDL_Color{0,0,0}}, 1920, 1080 });
	resOptions.push_back({ nullptr, UIText{"1270 X 720", std::make_pair(0,0), SDL_Color{0,0,0}}, 1270, 720 });
	resOptions.push_back({ nullptr, UIText{"800 X 600", std::make_pair(0,0), SDL_Color{0,0,0}}, 800, 600 });
	int offsetY = 332;
	for (int i = 0; i < resOptions.size(); ++i)
	{
		resOptions[i].obj = AddObject("OptionsBackgroundObj", 640, offsetY, UI);
		resOptions[i].obj->SetVisible(false);
		resOptions[i].obj->SetActive(false);
		resOptions[i].ResOption.isVisible = false;
		resOptions[i].ResOption.pos = std::make_pair(640, offsetY + 5); //resOptions[i].obj->GetPos();
		mSceneText.push_back(resOptions[i].ResOption);
		offsetY += 32;
	}
	currentRes.pos = std::make_pair(640, 305);
	currentRes.text = mgr->GetSettings().w + " X " + mgr->GetSettings().h;
	currentRes.isVisible = false;
	mSceneText.push_back(currentRes);
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

	if (ApplyBtn->InBounds(mouse.first, mouse.second) && ApplyBtn->IsActive())
	{
		ApplySettings();
	}

	if (mFsCheckBox.obj->InBounds(mouse.first, mouse.second))
	{
		if (!mFsCheckBox.bIsChecked)
		{
			mFsCheckBox.obj->SetAnim("Checked");
			mgr->GetSettings().bIsFullScreen = true;
			mFsCheckBox.bIsChecked = true;
		}
		else
		{
			mFsCheckBox.obj->SetAnim("default");
			mgr->GetSettings().bIsFullScreen = false;
			mFsCheckBox.bIsChecked = false;
		}
			
	}

	for (int i = 0; i < resOptions.size(); ++i)
	{
		if (resOptions[i].obj->InBounds(mouse.first, mouse.second) && resOptions[i].obj->IsActive())
		{
				mSceneText[3].text = resOptions[i].ResOption.text; //  This changes the text of the collapsed dropdown
				mgr->GetSettings().w = resOptions[i].w;
				mgr->GetSettings().h = resOptions[i].h;
				//mgr->SetWindowSize(resOptions[i].w, resOptions[i].h);

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
	ApplyBtn->SetVisible(actvis);
	mFsCheckBox.obj->SetVisible(actvis);

	mFsCheckBox.obj->SetActive(actvis);
	ApplyBtn->SetActive(actvis);
	SettingsCloseBtn->SetActive(actvis);
	dropDownCollapsed->SetActive(actvis);

	mSceneText[3].isVisible = actvis;

	
}

void MainMenuScene::ApplySettings()
{
	std::ofstream file("Settings.Json");
	nlohmann::json j;
	j["Audio"]["master-volume"] = mgr->GetSettings().mMasterVolume;
	j["Display"]["Width"] = mgr->GetSettings().w;
	j["Display"]["Height"] = mgr->GetSettings().h;
	j["Display"]["fullscreen"] = mgr->GetSettings().bIsFullScreen;

	file << j.dump(1);

	mgr->SetWindowSize(); 

}

void MainMenuScene::Collapse(bool collapsed)
{
	for (int i = 0; i < resOptions.size(); ++i)
	{
		resOptions[i].obj->SetVisible(!collapsed);
		resOptions[i].obj->SetActive(collapsed);
		mSceneText[i].isVisible = !collapsed;
	}

}

