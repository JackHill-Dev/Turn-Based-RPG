#include "StartButton.h"
#include "ManagerStruct.h"
#include "SceneManager.h"
StartButton::StartButton(std::string sprSheet) : Button(sprSheet)
{
}
void StartButton::Select(Managers* mgrs)
{
	mgrs->SceneMgr->NextScene(1);
}

