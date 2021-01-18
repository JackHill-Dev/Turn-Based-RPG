#include "SettingsScene.h"
#include <fstream>


SettingsScene::SettingsScene(Interface* mgr) : Scene(mgr)
{
	Setup();
}

void SettingsScene::Update(double dTime, Act act, std::pair<int, int> mousePos)
{
	if (act == Act::Click)
	{

		if (settingsCloseBtn->InBounds(mousePos.first, mousePos.second) && settingsCloseBtn->IsActive())
		{
			mgr->LoadPreviousScene();
		}

		if (dropdownCollapsed->InBounds(mousePos.first, mousePos.second) && dropdownCollapsed->IsActive())
			Collapse(false);
		else
			Collapse(true);
	

		if (ApplyBtn->InBounds(mousePos.first, mousePos.second) && ApplyBtn->IsActive())
		{
			ApplySettings();
		}

		if (checkBox->InBounds(mousePos.first, mousePos.second))
		{
			if (!mgr->GetSettings().bIsFullScreen)
			{
				checkBox->SetAnim("Checked");
				mgr->GetSettings().bIsFullScreen = true;
			}
			else
			{
				checkBox->SetAnim("default");
				mgr->GetSettings().bIsFullScreen = false;
			}

		}

		for (int i = 0; i < resOptions.size(); ++i)
		{
			if (resOptions[i].obj->InBounds(mousePos.first, mousePos.second) && resOptions[i].obj->IsActive())
			{
				mSceneText[3].text = resOptions[i].ResOption.text; //  This changes the text of the collapsed dropdown
				mgr->GetSettings().w = resOptions[i].w;
				mgr->GetSettings().h = resOptions[i].h;

			}
		}
	}
}

void SettingsScene::Setup()
{
	settingsCloseBtn = AddObject("CloseBtnObj",50, 50, UI);
	dropdownCollapsed = AddObject("resCollapsedObj", 640, 300, UI);
	ApplyBtn = AddObject("ApplyBtnObj", 640, 550, UI);
	checkBox = AddObject("checkBoxObj", 720, 200, UI);

	if (mgr->GetSettings().bIsFullScreen)
		checkBox->SetAnim("Checked");

	SetupResOptions();
}

void SettingsScene::SetupResOptions()
{
	resOptions.push_back({ nullptr, UIText{"1920 X 1080", std::make_pair(0,0),std::make_pair(70,50), SDL_Color{0,0,0}}, 1920, 1080 });
	resOptions.push_back({ nullptr, UIText{"1270 X 720", std::make_pair(0,0), std::make_pair(70,50), SDL_Color{0,0,0}}, 1270, 720 });
	resOptions.push_back({ nullptr, UIText{"800 X 600", std::make_pair(0,0),  std::make_pair(70,50), SDL_Color{0,0,0}}, 800, 600 });
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
	currentRes.text = std::to_string( mgr->GetSettings().w) + " X " + std::to_string( mgr->GetSettings().h);
	mSceneText.push_back(currentRes);

	
}


void SettingsScene::ApplySettings()
{
	std::ofstream file("Settings.Json");
	nlohmann::json j;
	j["Audio"]["master-volume"] = mgr->GetSettings().mMasterVolume;
	j["Display"]["Width"] = mgr->GetSettings().w;
	j["Display"]["Height"] = mgr->GetSettings().h;
	j["Display"]["fullscreen"] = mgr->GetSettings().bIsFullScreen;

	file << j.dump(1);

	mgr->SetWindowSize();

	mgr->SetFullScreen();

}

void SettingsScene::Collapse(bool collapsed)
{
	for (int i = 0; i < resOptions.size(); ++i)
	{
		resOptions[i].obj->SetVisible(!collapsed);
		resOptions[i].obj->SetActive(collapsed);
		mSceneText[i].isVisible = !collapsed;
	}
}

