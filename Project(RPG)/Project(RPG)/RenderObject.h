#pragma once
#include <utility>
#include <string>
#include "SpriteSheet.h"
#include "Actions.h"
#include "Animation.h"
class RenderObject
{

private:
	Animation* mCurrentAnim;
	std::pair<int, int> mPos;
	std::string mName;
	bool mVisible;
	SpriteSheet* mSheet;
	
public:
	std::string path;
	RenderObject() {}
	RenderObject(std::string sprSheet);

	bool Update(double dTime, Act act);
	bool Init();
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

