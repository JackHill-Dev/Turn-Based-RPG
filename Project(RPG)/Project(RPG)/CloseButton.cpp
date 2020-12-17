#include "CloseButton.h"
#include "MainMenuClass.h"
#include "GameManager.h"
CloseButton::CloseButton(std::string sprSheet) : Button(sprSheet)
{
}

void CloseButton::Select(Managers* mgrs)
{
	if (mgrs->GameMgr->GetMainMenu() != nullptr)
	{
		mgrs->GameMgr->GetMainMenu()->CloseSettings();
	}
	else
	{
		std::cout << "Menu is null";
	}
}

