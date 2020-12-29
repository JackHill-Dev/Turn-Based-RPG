#include "Item.h"


Item::Item(std::string name, int cost) : mName(name), mCost(cost)
{
	
}

Item::~Item()
{
}

std::string Item::GetName() const
{
	return mName;
}

std::string Item::GetObjName() const
{
	return mObjName;
}

int Item::GetCost() const
{
	return mCost;
}

RenderObject* Item::GetRenderObject()
{
	return &mRenderObject;
}

void Item::SetObjName(std::string name)
{
	mObjName = name;
}

void Item::SetRenderObject(RenderObject obj)
{
	mRenderObject = obj;
}

void Item::OnHover()
{
	std::cout << "Hovering over " << GetName() << std::endl;
	//SDL_SetTextureColorMod(mRenderObject.GetSheet()->GetTexture(), 250, 0, 0); // tint the item red when hovered over
}

void Item::OnLeave()
{
	//SDL_SetTextureColorMod(mRenderObject.GetSheet()->GetTexture(), 255, 255, 255);
}
