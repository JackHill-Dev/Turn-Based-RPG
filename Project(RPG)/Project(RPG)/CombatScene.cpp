#include "CombatScene.h"


RenderObject* character;

CombatScene::CombatScene(ObjectManager* objmg) : Scene(objmg)
{
	character = AddObject("maleObj", 60, 60, Game);
}

void CombatScene::Update(double dTime, Act act)
{
	
}

