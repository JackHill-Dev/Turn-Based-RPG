#include "QuitButton.h"
#include "ManagerStruct.h"
#include "GameManager.h"
QuitButton::QuitButton(std::string sprSheet) : Button(sprSheet)
{
}

bool QuitButton::Update(double dTime, Act act, std::pair<int, int> mouse)
{
	if (this ==  nullptr)
	{
		return false;
	}

	if (act == Act::Click && InBounds(mouse.first, mouse.second))
	{
		mgrs->GameMgr->Quit();
	}

	return true;
}

