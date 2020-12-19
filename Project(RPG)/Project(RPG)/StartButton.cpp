#include "StartButton.h"
#include "ManagerStruct.h"
#include "SceneManager.h"
StartButton::StartButton(std::string sprSheet) : Button(sprSheet)
{
}
void StartButton::Select()
{
	mgrs->SceneMgr->NextScene(1);
}

bool StartButton::Update(double dTime, Act act, std::pair<int, int> mouse)
{
	if(act == Act::Click && InBounds(mouse.first, mouse.second))
		mgrs->SceneMgr->NextScene(1);

	return true;
}