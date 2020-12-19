#pragma once
#include "Scene.h"
#include "CombatScene.h"
class CombatScene :
    public Scene
{
public:
    CombatScene(ObjectManager* objmg);
    //void Update(double dTime, Act act,std::pair<int, int> mouse) override;
};

