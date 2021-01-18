#include "MainMenuScene.h"

MainMenuScene::MainMenuScene(Interface* rng) : Scene(rng)
{
	// Get all button objects
	start  = AddObject("StartBtnObj", 60, 90, UI);
	quit = AddObject("quitBtnObj", 60, 400, UI);
	auto t = AddObject("cardObj1", 500, 500, UI);
	// AddObject(pQuitButton->GetName(),5, 400, UI)
	t->scale = 2;
	// Get Background object
	AddObject("mainMenuBGObj", 1280 / 2, 720 / 2, Background);
	// Get all SFX objects
	// Get Music object
	// Play music on loop (set loops to -1)

}

void MainMenuScene::Update(double dTime, Act act, std::pair<int, int> mouse)
{
	//Its better to do button checks here, as this way you can iterate through specific layer, but current functionality in buttons is fine - T
	if (act == Act::Click)
	{
		if (start->InBounds(mouse.first, mouse.second))
			mgr->LoadScene(Scenes::Overworld);
		else
			if (quit->InBounds(mouse.first, mouse.second))
				mgr->Quit();
	}
}

