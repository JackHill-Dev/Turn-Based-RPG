#include "SettingsButton.h"
#include "GameManager.h"
SettingsButton::SettingsButton(std::string sprSheet) : Button(sprSheet)
{

}

void SettingsButton::Select(Managers* mgrs)
{
	if (IsActive())
	{

		if (mgrs->GameMgr->GetMainMenu() != nullptr)
		{
			mgrs->GameMgr->GetMainMenu()->ViewSettings();
		}
		else
		{
			std::cout << "Main menu is null" << std::endl;
		}
	}
}





