#pragma once
#include "RenderObject.h"
class Item :
    public RenderObject
{
public:
    virtual void SetCost(const int& amount) = 0;

private:
    int mCost;
};

