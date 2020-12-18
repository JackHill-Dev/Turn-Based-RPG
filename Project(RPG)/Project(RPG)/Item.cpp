#include "Item.h"


Item::Item(std::string& name, int cost) : mName(name), mCost(cost)
{

}

std::string Item::GetName() const
{
    return mName;
}

int Item::GetCost() const
{
    return mCost;
}
