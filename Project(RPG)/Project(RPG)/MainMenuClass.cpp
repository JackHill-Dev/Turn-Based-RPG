#include "MainMenuClass.h"

MainMenuClass::MainMenuClass()
{
	// Get all button objects
	pMenuButton = AddObject("StartBtnObj", 5, 90, UI);
	AddObject("QuitBtnObj", 5, 400, UI);
	// Get Background object
	AddObject("mainMenuBGObj", 0, 0, Background);
	// Get all SFX objects
	// Get Music object
	// Play music on loop (set loops to -1)

}

void MainMenuClass::Init(Managers* mgrs)
{
	Mix_Music* mus = Mix_LoadMUS("Assets/Music/Windless-Slopes.mp3");
	mgrs->AudioMgr->PlayMusic(mus, -1);
}

void MainMenuClass::Update(double dTime, Act act)
{
	/*if (act == Act::Jump)
		std::cout << "AGHH";*/
}

