#pragma once
#include <utility>
#include <string>
#include "SpriteSheet.h"
#include "Actions.h"
#include "Animation.h"
#include "ManagerStruct.h"

class SceneManager;
class GameManager;

class RenderObject
{

private:
	Animation* mCurrentAnim;
	std::pair<int, int> mPos;
	std::string mName;
	bool mVisible;
	SpriteSheet* mSheet;
protected:
	Managers* mgrs;
	
public:
	std::string path;
	RenderObject();
	RenderObject(std::string sprSheet);

	virtual bool Update(double dTime, Act act, std::pair<int, int> mouse);
	bool Init(Managers* mgrs);
	std::pair<int, int> GetPos();
	void SetAnim(std::string id);
	void SetPos(std::pair<int, int> nPos);
	void SetTexture(SpriteSheet* nSheet);
	SpriteSheet* GetSheet();
	bool IsVisible();
	bool InBounds(int x, int y);
	virtual void Select();
	Animation* GetAnim();
};

