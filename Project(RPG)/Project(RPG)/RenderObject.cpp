#include "RenderObject.h"

bool RenderObject::Update(double dTime, Act act)
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

void RenderObject::Select()
{

}

bool RenderObject::InBounds(int x, int y)
{

	//return false if cant be selected
	float bound = GetSheet()->GetCellSize();
	
	if (x >= mPos.first - bound / 2 && x <= mPos.first + bound / 2)
		return (y >= mPos.second - bound / 2 && y <= mPos.second + bound / 2);
	else
		return false;
}