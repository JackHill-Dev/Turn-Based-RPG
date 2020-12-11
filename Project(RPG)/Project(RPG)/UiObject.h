#pragma once
#include "SpriteSheet.h"
#include "RenderObject.h"
class UiObject : public RenderObject
{
private:
	void (*mCallBack)();
public:
	UiObject() {}
	UiObject(std::string);
	void SetCallBack(void (*nCallBack)());
	void Call();
	void Clear();
	virtual void Select() override;
};

