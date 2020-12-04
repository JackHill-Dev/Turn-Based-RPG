#pragma once
#include "SpriteSheet.h"
#include "RenderObject.h"
class UiObject : public RenderObject
{
private:
	void (*mCallBack)();
public:
	void SetCallBack(void (*nCallBack)());
	void Call();
	void Clear();
};

