#include "UiObject.h"



UiObject::UiObject(std::string sprSheet): RenderObject(sprSheet)
{

}

void UiObject::SetCallBack(void (*nCallBack)())
{
	mCallBack = nCallBack;
}
void UiObject::Call()
{
	mCallBack();
}
void UiObject::Clear()
{
	mCallBack = nullptr;
}

void UiObject::Select(SceneManager* sceneMgr, GameManager* gameMgr)
{
	std::cout << "UI Object pressed";
}
