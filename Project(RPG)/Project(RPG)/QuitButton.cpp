#include "QuitButton.h"
#include "ManagerStruct.h"
#include "GameManager.h"
QuitButton::QuitButton(std::string sprSheet) : Button(sprSheet)
{
}

void QuitButton::Select()
{
	mgrs->GameMgr->Quit();
}


