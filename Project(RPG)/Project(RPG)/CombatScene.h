#pragma once
#include "Scene.h"
class CombatScene :
    public Scene
{
public:
    CombatScene(ObjectManager* objmg);
    void Update(double dTime, Act act) override;
};

