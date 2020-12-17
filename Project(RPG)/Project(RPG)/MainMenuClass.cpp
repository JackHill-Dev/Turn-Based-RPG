#include "MainMenuClass.h"
#include "CloseButton.h"
MainMenuClass::MainMenuClass(ObjectManager* rng) : Scene(rng)
{
	SetupObjects();

}

void MainMenuClass::Init(Managers* mgrs)
{
	//Mix_Music* mus = Mix_LoadMUS("Assets/Music/Windless-Slopes.mp3");
	//mgrs->AudioMgr->PlayMusic(mus, -1);
}

void MainMenuClass::Update(double dTime, Act act)
{
	/*if (act == Act::Jump)
		std::cout << "AGHH";*/
}

void MainMenuClass::ViewSettings()
{
	pSettingsOverlay->SetVisible(true);
	pSettingsOverlay->SetActive(true);
	pCloseButton->SetVisible(true);
	pCloseButton->SetActive(true);
	pSettingsButton->SetActive(false);
}

void MainMenuClass::CloseSettings()
{
	pSettingsOverlay->SetVisible(false);
	pSettingsOverlay->SetActive(false);

	pCloseButton->SetActive(false);
	pCloseButton->SetVisible(false);

	pSettingsButton->SetActive(true);

}

void MainMenuClass::SetupObjects()
{
	// Get Background object
	RenderObject* pBack = AddObject("mainMenuBGObj", 0, 0, Background);

	SetupButtons();

	pSettingsOverlay = AddObject("settingsOverlayObj", 300, 100, Background);
	pSettingsOverlay->SetVisible(false);
	pSettingsOverlay->SetActive(false);

	
	pCloseButton->SetActive(false);
	pCloseButton->SetVisible(false);
	

	// Get all SFX objects
	// Get Music object
	// Play music on loop (set loops to -1)
}

void MainMenuClass::SetupButtons()
{
	// Get all button objects
	pStartButton = AddObject("StartBtnObj", 5, 90, UI);
	pSettingsButton = dynamic_cast<SettingsButton*>(  AddObject("SettingsBtnObj", 5, 250, UI));
	pCloseButton = dynamic_cast<CloseButton*>(AddObject("CloseBtnObj", 905, 105, UI));
	pQuitButton = AddObject("QuitBtnObj", 5, 400, UI);
}

