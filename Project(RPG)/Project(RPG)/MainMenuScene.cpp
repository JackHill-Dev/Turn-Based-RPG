#include "MainMenuScene.h"

MainMenuScene::MainMenuScene(ObjectManager* rng) : Scene(rng)
{
	// Get all button objects
	pMenuButton = AddObject("StartBtnObj", 5, 90, UI);
	pQuitButton = AddObject("QuitBtnObj", 5, 400, UI);

	// AddObject(pQuitButton->GetName(),5, 400, UI)

	// Get Background object
	AddObject("mainMenuBGObj", 0, 0, Background);
	// Get all SFX objects
	// Get Music object
	// Play music on loop (set loops to -1)

}

void MainMenuScene::Update(double dTime, Act act, std::pair<int, int> mouse)
{
	//Its better to do button checks here, as this way you can iterate through specific layer, but current functionality in buttons is fine - T
}

