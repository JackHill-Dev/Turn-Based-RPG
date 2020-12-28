#include "CombatScene.h"


RenderObject* obj;
Unit* character;
CombatScene::CombatScene(ObjectManager* objmg) : Scene(objmg)
{
	

	character = static_cast<Unit*>((AddObject("maleUnit", 80, 60, Game)));
	character->SetAnim("LookDown");
	character->SetPosition(std::make_pair (100, 100));
	obj = (AddObject("maleObj", 60, 60, Game));
	obj->SetAnim("LookDown");

	(AddObject("maleObj", 120, 60, Game));
	(AddObject("maleObj", 300, 60, Game));
	(AddObject("maleObj", 300, 399, Game));
	(AddObject("maleObj", 60, 60, Game));



} 


void CombatScene::Update(double dTime, Act act, std::pair<int, int> mouse)
{	
	if (act == Act::Click)
	{

		
		float xDiff = mouse.first - character->GetPos().first;
		if (xDiff < 0)
			xDiff *= -1;

		float yDiff = mouse.second - character->GetPos().second;
		if (yDiff < 0)
			yDiff *= -1;

		if (xDiff > yDiff)
		{

			if (mouse.first < character->GetPos().first)
			{
				character->SetAnim("LookLeft");
			}
			else
			{
				character->SetAnim("LookRight");
			}
		}
		else
		{
			if (mouse.second > character->GetPos().second)
			{
				character->SetAnim("LookUp");
			}
			else
			{
				character->SetAnim("LookDown");
			}
		}


		character->SetTarget(mouse);
	}

	
	//else
		//character->SetAnim("LookDown");
}



