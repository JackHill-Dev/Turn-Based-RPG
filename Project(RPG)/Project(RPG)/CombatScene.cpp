#include "CombatScene.h"
Character charac{"maleObj", "WizardObj"};

RenderObject* reload;
RenderObject* hovered = nullptr;

typedef CombatScene::tile tile;

std::pair<Character*, tile* >* character;
std::pair<Character*, tile* >* target;
Card* selectedCard = nullptr;
std::vector < std::pair<Character*, tile*>> team{};
std::vector < std::pair<Character*, tile*>> enemy{};

struct map
{
	tile tiles[15][15];
};

map mapp;

std::vector<Card*> deck;

std::pair<int, int> lastMousePos = { 0,0 };

std::pair<double, double> centre = { 640,360};
enum Selection{Team,Enemy,Ground, UICard, Any};
Selection current = Team;
CombatScene::CombatScene(Interface* objmg) : Scene(objmg)
{

	AddObject("forestBGObj", 640, 360, Background);
	//reload = AddObject("quitBtnObj", 1100, 500, UI);
	for (int i = 0; i < 15; i++)
	{
		for (int x = 0; x < 15; x++)
		{
			mapp.tiles[i][x].square = (AddObject("tileObj", i*32 - 7.5*32 + centre.first, x*32 - 7.5 *32 + centre.second - 32, Background));
			mapp.tiles[i][x].pos = std::make_pair(i * 32 - 7.5 * 32 + centre.first, x * 32 - 7.5 * 32 + centre.second - 32);
			mapp.tiles[i][x].square->SetAnim("Grass");
		}
	}


	

} 


CombatScene* CombatScene::Load(std::vector<Character*> player, std::vector<Character*> anemy)
{
	int v = 0;
	for (auto i : player)
	{

		mapp.tiles[0][v].availiable = false;
		i->SetTarget(mapp.tiles[0][v].pos);
		
		i->Assign(AddObject(i->GetObjName(), mapp.tiles[0][v].pos.first, mapp.tiles[0][v].pos.second, Game));
		team.push_back(std::make_pair(i, &mapp.tiles[0][v]));
		v++;

	}
	v = 0;
	for (auto i : anemy)
	{
		mapp.tiles[14][v].availiable = false;
		i->SetTarget(mapp.tiles[14][v].pos);

		i->Assign(AddObject(i->GetObjName(), mapp.tiles[14][v].pos.first, mapp.tiles[14][v].pos.second, Game));
		enemy.push_back(std::make_pair(i, &mapp.tiles[14][v]));
		v++;

	}
	LoadHand();

	return this;
}
bool InRange(tile* first, tile* second, int range)
{
	if (first->pos.first == second->pos.first || first->pos.first == second->pos.first - 32 || first->pos.first == second->pos.first + 32)
		if (first->pos.second == second->pos.second || first->pos.second == second->pos.second - 32 || first->pos.second == second->pos.second + 32)
			return true;
	return false;
}

void CombatScene::Update(double dTime, Act act, std::pair<int, int> mouse)
{	
	bool busy = false;

	for (auto i : team)
		if (i.first->getObj() != nullptr)
		{
			{
				i.first->Update(dTime);
				if (i.first->moving)
					busy = true;
			}
		}

	
	if (act == Act::Click && !busy)
	{
		

		if (current == Selection::Any)
		{
			if (selectedCard == nullptr)
			{
				int index = 0;
				while (selectedCard == nullptr && index < playerHand.size())
				{
					if (playerHand[index]->getObj()->InBounds(mouse.first, mouse.second))
					{
						selectedCard = playerHand[index];
						selectedCard->getObj()->tint = SDL_Color{ 255,255,0 };
						current = Selection::Team;
					}
					index++;
				}
			}
				if (selectedCard == nullptr && character == nullptr)
				{
					int index = 0;

					while (character == nullptr && index < team.size())
					{
						if (team[index].first->getObj()->InBounds(mouse.first, mouse.second))
						{
							character = &team[index];
							team[index].first->getObj()->tint = SDL_Color{ 255,255,0 };
							current = Selection::Ground;
						}
						index++;
					}
				}
			
		}
		
			else if (current == Selection::Ground)
			{

			

				if (character != nullptr)
					for (int i = 0; i < 15; ++i)
						for (int p = 0; p < 15; ++p)
							if (mapp.tiles[i][p].availiable &&mapp.tiles[i][p].square->InBounds(mouse.first, mouse.second))
							{

								character->second->availiable = true;
								character->second = &mapp.tiles[i][p];
								character->second->availiable = false;
								character->first->SetTarget(character->second->pos);
								

							}
				if (character != nullptr)
					character->first->getObj()->Untint();
				character = nullptr;
					
				current = Selection::Any;
				
				
			}
			else if (current == Selection::Team)
			{
				if (character == nullptr)
				{
					int index = 0;

					while (character == nullptr && index < team.size())
					{
						if (team[index].first->getObj()->InBounds(mouse.first, mouse.second))
						{
							character = &team[index];
							team[index].first->getObj()->tint = SDL_Color{ 255,255,0 };
							current = Selection::Enemy;
						}
						index++;
					}
					if (character == nullptr)
					{
						if (selectedCard != nullptr)
						{
							current = Selection::Any;
							selectedCard->getObj()->Untint();
							selectedCard = nullptr;
							
						}

					}
				}
			}
			else if (current == Selection::Enemy)
			{
				target = nullptr;
				int index = 0;
				while (index < enemy.size() && target == nullptr)
				{

					if (enemy[index].first->getObj()->InBounds(mouse.first, mouse.second))
					{
						target = &enemy[index];
					}

					index++;
				}


				selectedCard->getObj()->Untint();
				character->first->getObj()->Untint();
				
				if (target != nullptr)
				{
					Cast(selectedCard, character, target);
					
					selectedCard = nullptr;
				}
				character->first->getObj()->Untint();
				character = nullptr;

				if (selectedCard != nullptr)
				{
					selectedCard->getObj()->Untint();
					selectedCard = nullptr;
				}
				
				
				
				current = Selection::Any;

			}





	}
	else if (act == Act::MouseUpdate)
	{
	if (hovered != nullptr)
	{
		if ((character == nullptr || hovered != character->first->getObj()) && (selectedCard == nullptr || hovered != selectedCard->getObj()))
			hovered->Untint();
		hovered = nullptr;
	}
		if (current == Selection::Any)
		{
			int index = 0;
			while (hovered == nullptr && index < playerHand.size())
			{
				if (playerHand[index]->getObj()->InBounds(mouse.first, mouse.second))
				{
					hovered = playerHand[index]->getObj();
					hovered->tint = SDL_Color{ 0,255,0 };
					
				}
				++index;
			}
			
			if (hovered == nullptr)
			{
				index = 0;
				while (hovered == nullptr && index < team.size())
				{
					if (team[index].first->getObj()->InBounds(mouse.first, mouse.second))
					{
						hovered = team[index].first->getObj();
						hovered->tint = SDL_Color{ 0,255,0 };
					}
					index++;
				}
			}


		}
		else if (current == Selection::Team)
		{
			


			int index = 0;
			while (hovered == nullptr && index < team.size())
			{
				if (team[index].first->getObj()->InBounds(mouse.first, mouse.second))
				{
					hovered = team[index].first->getObj();
					hovered->tint = SDL_Color{ 0,255,0 };
				}
				index++;
			}
		
		}
		else if (current == Selection::Ground)
		{
			
			for (int i = 0; i < 15; i++)
				for (int t = 0; t < 15; t++)
					if (mapp.tiles[i][t].square->InBounds(mouse.first, mouse.second))
					{
						hovered = mapp.tiles[i][t].square;
						if (mapp.tiles[i][t].availiable)
							hovered->tint = SDL_Color{ 0,255,0 };
						else
							hovered->tint = SDL_Color{ 255,0,0 };
					}
		}
		else if (current == Selection::Enemy)
		{



			int index = 0;
			while (hovered == nullptr && index < team.size())
			{
				if (enemy[index].first->getObj()->InBounds(mouse.first, mouse.second))
				{



					hovered = enemy[index].first->getObj();

					if (selectedCard != nullptr && InRange(character->second, enemy[index].second, 1))
					{

						hovered->tint = SDL_Color{ 0,255,0 };

					}
					else
						hovered->tint = SDL_Color{ 255,0,0 };
				}
				index++;
			}

		}
	}

}










void CombatScene::Cast(Card* card, std::pair<Character*, tile*>* caster, std::pair<Character*, tile*>* target)
{
	if (card != nullptr && caster != nullptr && target != nullptr && InRange(caster->second, target->second, 1))
	{
		
		card->Cast(caster->first, target->first);

		if (target->first->GetHealth() <= 0)
		{
			mLayers[Game].erase(std::find(mLayers[Game].begin(), mLayers[Game].end(), target->first->getObj()));
			enemy.erase(std::find(enemy.begin(), enemy.end(), *target));
			target->second->availiable = true;
			delete target->first->getObj();
			delete target;
			
			
		}

		target = nullptr;
		selectedCard = nullptr;







		mLayers[UI].erase(std::find(mLayers[UI].begin(), mLayers[UI].end(), card->getObj()));

		delete (card->getObj());

		playerHand.erase(std::find(playerHand.begin(), playerHand.end(), card));

	}
	//card->getObj() = nullptr;
}


void CombatScene::LoadHand()
{

	 
	for (auto i : playerHand)
		delete i->getObj();
	playerHand.clear();

	for(int i = 0; i < 5; i++)
		playerHand.push_back(new Card(5, "slash", 1, "cardObj"));

	if(playerHand.size() > 0)
	for (int i = 0; i < playerHand.size(); ++i)
	{

		
			
		playerHand[i]->Assign(AddObject(playerHand[i]->GetObjName(), centre.first + (float)100  * i - 210, 650, UI));
		playerHand[i]->getObj()->scale = 0.4f;
		
	}

	current = Selection::Any;
}


