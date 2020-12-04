#include "UiObject.h"
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