#include "SettingsScene.h"
#include <fstream>


void SettingsScene::Update(double dTime, Act act, std::pair<int, int> mousePos)
{

}

void SettingsScene::Setup()
{
}

void SettingsScene::SetupResOptions()
{
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

