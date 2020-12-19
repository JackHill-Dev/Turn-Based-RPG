#include "UiObject.h"
#include "ManagerStruct.h"



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

void UiObject::Select()
{
	std::cout << "UI Object pressed";
}

bool UiObject::Update(double dTime, Act act, std::pair<int, int> mouse)
{
	
	return true;
		
}