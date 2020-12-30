#include "CombatScene.h"

RenderObject* selected;
RenderObject* obj;
Unit* character;
Layer current = Layer::Game;
std::pair<int, int> lastMousePos = { 0,0 };
CombatScene::CombatScene(ObjectManager* objmg) : Scene(objmg)
{
	

	character = static_cast<Unit*>((AddObject("maleUnit", 80, 60, Game)));
	character->SetAnim("LookDown");
	character->SetPosition(std::make_pair (100, 100));

	(AddObject("maleUnit", 120, 60, Game));
	(AddObject("maleUnit", 300, 60, Game));



} 


void CombatScene::Update(double dTime, Act act, std::pair<int, int> mouse)
{	



	if (act == Act::MouseUpdate)
	{
		int i = 0;
		if (selected != nullptr)
		{
			if(selected != character)
			selected->tint = SDL_Color{ 255,255,255 };
			selected = nullptr;
		}

		while (selected == nullptr && i < mLayers[current].size())
		{


			if (mLayers[current][i]!= character && mLayers[current][i]->InBounds(mouse.first, mouse.second))
			{

				selected = mLayers[current][i];
				selected->tint = SDL_Color{ 0,255,0 };
			}
			i++;
		}
	}
	else

	{


		switch (act)
		{
		case Act::Click:
			if (selected != nullptr)
			{

				if (character != nullptr)
					character->tint = SDL_Color{ 255,255,255 };
				character = static_cast<Unit*>(selected);
				character->tint = SDL_Color{ 255,100,255 };



			}
			else
			{
				if (character != nullptr)
					character->tint = SDL_Color{ 255,255,255 };
				character = nullptr;

			}
			break;
		case Act::RClick:
			if (character != nullptr)
				character->SetTarget(mouse);
			break;
	
		default:
			break;
		}



	}



	


	
	//else
		//character->SetAnim("LookDown");
}



