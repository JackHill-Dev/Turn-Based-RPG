#include "RenderObject.h"
RenderObject::RenderObject(std::string sprSheet)
{
	path = sprSheet;
	mCurrentAnim = nullptr;
	mVisible = true;
}

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
	mCurrentAnim = mSheet->GetAnim(id);
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
	//std::cout << "Render object clicked";
}

bool RenderObject::InBounds(int x, int y)
{
	//return false if cant be selected
	std::pair<float, float> bound = GetSheet()->GetCellSize();
	//float bound = GetSheet()->GetCellSize().first;
	if (x >= mPos.first - bound.first / 2 && x <= mPos.first + bound.first  / 2)
		return (y >= mPos.second  - bound.second  && y <= mPos.second + bound.second );
	else
		return false;
}

Animation* RenderObject::GetAnim()
{
	return mCurrentAnim;	
}