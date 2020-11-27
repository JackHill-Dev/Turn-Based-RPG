#pragma once
#include <utility>
#include <string>
#include "SpriteSheet.h"
class RenderObject
{

private:
	std::pair<int, int> mPos;
	std::string mName;
	bool mVisible;
	SpriteSheet* mSheet;
public:
	bool Update(double dTime);
	bool Init();
	std::pair<int, int> GetPos();
	void SetAnim(std::string id);
	void SetPos(std::pair<int, int> nPos);
	void SetTexture(SpriteSheet* nSheet);
	SpriteSheet* GetSheet();
	bool IsVisible();
};

