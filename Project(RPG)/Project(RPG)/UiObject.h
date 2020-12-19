#pragma once
#include "SpriteSheet.h"
#include "RenderObject.h"

class SceneManager;
class GameManager;

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
	virtual bool Update(double dTime, Act act, std::pair<int, int> mouse) override;
};

