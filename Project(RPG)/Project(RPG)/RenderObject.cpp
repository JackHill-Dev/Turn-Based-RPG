#include "RenderObject.h"

bool RenderObject::Update(double dTime)
{
	return true;
}

bool RenderObject::Init()
{
	mVisible = true;
	return true;
}

std::pair<int, int> RenderObject::GetPos()
{
	return mPos;
}

void RenderObject::SetAnim(std::string id)
{

}

void RenderObject::SetPos(std::pair<int, int> nPos)
{
	mPos = nPos;
}

void RenderObject::SetTexture(SpriteSheet* nSheet)
{
	mSheet = nSheet;
}

SpriteSheet* RenderObject::GetSheet()
{
	return mSheet;
}

bool RenderObject::IsVisible()
{
	return mVisible;
}