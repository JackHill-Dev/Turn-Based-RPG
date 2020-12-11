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
	virtual void Select(SceneManager* sceneMgr, GameManager* gameMgr) override;
};

