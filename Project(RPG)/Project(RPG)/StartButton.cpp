#include "StartButton.h"
#include "SceneManager.h"
StartButton::StartButton(std::string sprSheet) : Button(sprSheet)
{
}
void StartButton::Select(SceneManager* sceneMgr, GameManager* gameMgr)
{
	sceneMgr->SetScene(1);
}

