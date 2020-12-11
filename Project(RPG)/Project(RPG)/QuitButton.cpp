#include "QuitButton.h"
#include "GameManager.h"
QuitButton::QuitButton(std::string sprSheet) : Button(sprSheet)
{
}

void QuitButton::Select(SceneManager* sceneMgr, GameManager* gameMgr)
{
	gameMgr->Quit();
}


