#pragma once
#include "RenderObject.h"
class Unit :
    public RenderObject
{
private:
    double time = 0;
    float speed = 1;
public:
    bool Update(double dTime, Act act) override;
};

