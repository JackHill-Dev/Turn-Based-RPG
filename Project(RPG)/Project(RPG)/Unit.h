#pragma once
#include "RenderObject.h"
#include <math.h>
class Unit :
    public RenderObject
{
private:
    bool moving = false;
    std::pair<double, double> target;
    void Move(double dTime);
public:
    bool Update(double dTime, Act act, std::pair<int, int> mouse) override;
    void SetTarget(std::pair<double, double> target);
    void SetPosition(std::pair<float, float> pos);

    Unit(std::string sprSheet);
};

