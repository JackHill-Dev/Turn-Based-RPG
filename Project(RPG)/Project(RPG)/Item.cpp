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

