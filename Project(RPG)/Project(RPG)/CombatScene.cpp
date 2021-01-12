#include "CombatScene.h"
Character charac{"maleObj"};


RenderObject* endTurn;
bool playerTurn = false; // Is it the players turn
RenderObject* hovered = nullptr;
typedef CombatScene::tile tile;
typedef CombatScene::Unit Unit;
Unit* character = nullptr;
Unit* target;
std::pair<Card*, RenderObject*>* selectedCard = nullptr;
std::vector <Unit> team{};
std::vector <Unit> enemy{};
std::vector<std::pair<Card*, RenderObject*>> playerhand;
std::vector<std::pair<Card*, RenderObject*>> enemyHand;
struct map
{
	tile tiles[15][15];
};

map mapp;

std::vector<Card*> deck;

std::pair<double, double> centre = { 640,360};
enum Selection{Team,Enemy,Ground, UICard, Any};
Selection current = Any;
CombatScene::CombatScene(Interface* objmg) : Scene(objmg)
{
	
	endTurn = AddObject("quitBtnObj", 500, 500, UI);
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
	for (int i = 0; i < 15; i++)
	{
		for (int x = 0; x < 15; x++)
		{

			if (x > 0)
			{
				mapp.tiles[i][x].down =(&mapp.tiles[i][x - 1]);
				mapp.tiles[i][x].adjacentTiles.push_back(mapp.tiles[i][x].down);
			}
			if (x < 14)
			{
				mapp.tiles[i][x].up =(&mapp.tiles[i][x + 1]);
				mapp.tiles[i][x].adjacentTiles.push_back(mapp.tiles[i][x].up);
			}
			if (i > 0)
			{
				mapp.tiles[i][x].left = (&mapp.tiles[i - 1][x]);
				mapp.tiles[i][x].adjacentTiles.push_back(mapp.tiles[i][x].left);
			}
			if (i < 14)
			{
				mapp.tiles[i][x].right = (&mapp.tiles[i + 1][x]);
				mapp.tiles[i][x].adjacentTiles.push_back(mapp.tiles[i][x].right);
			}

			
			
			
			

			/*mapp.tiles[i][x].adjacentTiles.push_back(&mapp.tiles[i + 1][x+1]);
			mapp.tiles[i][x].adjacentTiles.push_back(&mapp.tiles[i - 1][x - 1]);
			mapp.tiles[i][x].adjacentTiles.push_back(&mapp.tiles[i + 1][x +1 ]);
			mapp.tiles[i][x].adjacentTiles.push_back(&mapp.tiles[i + 1][x -1]);*/

		}
	}

	

} 


void CombatScene::Update(double dTime, Act act, std::pair<int, int> mouse)
{
	
	for (auto& i : team)
		if (i.character->GetHealth() <= 0)
			RemoveUnit(i);
	for (auto& i : enemy)
		if (i.character->GetHealth() <= 0)
			RemoveUnit(i);

	bool scenebusy = false;
	if (playerTurn)
	{
		for (auto &i : team)
			if (i.busy)
			{
				i.Move(dTime);
				scenebusy = true;
			}
		if (!scenebusy)
		{
			if (act == Act::Click)
			{
				if (endTurn->InBounds(mouse.first, mouse.second))
				{
					playerTurn = false;
					for (auto i : enemy)
					{
						i.character->movement.first = i.character->movement.second;
						i.character->stamina.first = i.character->stamina.second;

					}
				}
				else
				if (current == Selection::Any)
				{
					bool found = false;


					for (auto& i : playerhand)
						if (i.second->InBounds(mouse.first, mouse.second))
						{
							selectedCard = &i;
							found = true;
							hovered = i.second;
							hovered->tint = SDL_Color{ 255,255,0 };
							current = Selection::Team;
						}

					if(!found)
					for (auto &i : team)
						if (i.object->InBounds(mouse.first, mouse.second) || i.profile->InBounds(mouse.first, mouse.second))
						{
							character = &i;
							character->object->tint = SDL_Color{ 255,255,0 };
							if(selectedCard != nullptr)
								current = Selection::Enemy;
							current = Selection::Ground;
						}
				}
				else
				{
					switch (current)
					{
					case(Selection::Ground):
						
						for (int i =0; i < 15; i++)
							for(int x = 0; x < 15; x++)
								if (mapp.tiles[i][x].square->InBounds(mouse.first, mouse.second))
								{
									character->SetTarget(&mapp.tiles[i][x]);
									character->object->Untint();
								}

						character = nullptr;
						current = Selection::Any;

						break;
						case(Selection::Team):
							for (auto& i : team)
								if (i.object->InBounds(mouse.first, mouse.second) || i.profile->InBounds(mouse.first, mouse.second))
								{
									character = &i;
									character->object->tint = SDL_Color{ 255,255,0 };
									current = Selection::Enemy;
								}
							break;
						case(Selection::Enemy):
							for (auto& i : enemy)
								if (i.object->InBounds(mouse.first, mouse.second) || i.profile->InBounds(mouse.first, mouse.second))
								{
									target = &i;
									Cast(selectedCard);
									target = nullptr;
									character = nullptr;
									selectedCard = nullptr;
									current = Selection::Any;
								}
							break;
					}

				}
			}
			else
				if (act == Act::MouseUpdate)
				{
					if (hovered != nullptr)
					{
						if (character != nullptr && character->object != nullptr && character->object == hovered)
						{

						}
						else
							if (selectedCard != nullptr && selectedCard->second != nullptr && selectedCard->second == hovered)
							{

							}
							else
							hovered->Untint();
					}
					hovered = nullptr;
					if (current == Selection::Any)
					{
						
						bool found = false;

						for(auto &i: playerhand)
							if (i.second->InBounds(mouse.first, mouse.second))
							{
								found = true;
								hovered = i.second;
								hovered->tint = SDL_Color{ 0,255,0 };
							}

						if(!found)
							for (auto& i : team)
								if (i.object->InBounds(mouse.first, mouse.second) || i.profile->InBounds(mouse.first, mouse.second))
								{
									found = true;
									hovered = i.object;
									hovered->tint = SDL_Color{ 0, 255, 0 };
								}
					}
					else
						switch (current)
						{
						case(Selection::Team):

							for (auto& i : team)
								if (i.object->InBounds(mouse.first, mouse.second) || i.profile->InBounds(mouse.first, mouse.second))
								{
									hovered = i.object;
									hovered->tint = SDL_Color{ 0, 255, 0 };
								}
							
							break;
						case(Selection::Enemy):

							for (auto& i : enemy)
								if (i.object->InBounds(mouse.first, mouse.second))
								{
									hovered = i.object;
									hovered->tint = SDL_Color{ 0, 255, 0 };
								}

							break;
						case(Selection::Ground):
							bool found = false;
							for(int i =0; i < 15; i++)
								for(int t = 0; t < 15; t++)
									if (!found && mapp.tiles[i][t].square->InBounds(mouse.first, mouse.second))
									{
										found = true;
										hovered = mapp.tiles[i][t].square;
										if(mapp.tiles[i][t].availiable)
											hovered->tint = SDL_Color{ 0,255,0 };
										else
											hovered->tint = SDL_Color{ 255,0,0 };
									}
							
							break;
						}


				}
		}
	}
	else
	{
		for(auto& i : enemy)
			if (i.busy)
			{
				i.Move(dTime);
				scenebusy = true;
			}
		if (!scenebusy)
		{
			RunAi();
		}

	}
}

void CombatScene::Load(std::vector<Character*> enemyTeam)
{
	int v = 0;
	for (auto i : *mgr->player)
	{
		Unit unit = Unit(i, &mapp.tiles[0][v], AddObject(i->GetObjName(), 0, 0, Game), AddObject("portrait", 250, 125+150*v, UI));
		unit.profile->scale = 0.3f;
		team.push_back(unit);
		v++;
	}
	v = 0;

	for(auto i : enemyTeam)
	{
		Unit unit = Unit(i, &mapp.tiles[14][v], AddObject(i->GetObjName(), 0, 0, Game),AddObject("portrait", 1000, 125+150*v, UI));
		unit.profile->scale = 0.3f;
		enemy.push_back(unit);
		v++;
	}

	for (int i = 0; i < 5; i++)
	{
		playerhand.push_back(std::make_pair(new Card(5, "Slash", 1, "cardObj"), AddObject("cardObj", centre.first - 200 + 100 * i - 15, 650, UI)));
		playerhand.back().second->scale = 0.4f;
	}
	for (int i = 0; i < 5; i++)
	{
		enemyHand.push_back(std::make_pair(new Card(5, "Slash", 1, "cardObj"), nullptr));
		
	}
}

void CombatScene::Cast(std::pair<Card*, RenderObject*>* card)
{
	target->object->Untint();
	character->object->Untint();
	if (CalculatePath(character->occupiedTile, target->occupiedTile).size() <= 1)
	{
		card->first->Cast(character->character, target->character);
		mLayers[UI].erase(std::find(mLayers[UI].begin(), mLayers[UI].end(), card->second));
		playerhand.erase(std::find_if(playerhand.begin(), playerhand.end(), [card](std::pair<Card*, RenderObject*> cd)

			{

				return(card->first == cd.first);
			})
		);
		if (target->character->GetHealth() <= 0)
			RemoveUnit(*target);
	}
}

void CombatScene::RemoveUnit(Unit unit)
{
	mLayers[Game].erase(std::find(mLayers[Game].begin(), mLayers[Game].end(), unit.object));
	mLayers[UI].erase(std::find(mLayers[UI].begin(), mLayers[UI].end(), unit.profile));
	delete unit.object;
	delete unit.profile;
	unit.occupiedTile->availiable = true;

	Unit p = unit;
	auto i = std::find_if(team.begin(), team.end(), [unit](Unit u) {
		return (u.character == unit.character);
		});
	if (i != team.end())
	{
		team.erase(i);
	}
	else
	{
		enemy.erase(std::find_if(enemy.begin(), enemy.end(), [unit](Unit u) {
			return (u.character == unit.character);
			}));
	}

	//delete unit.character;
}



void CombatScene::RunAi()
{
	int e = 0;
	bool validAction = false;
	for (auto &i : enemy)
	{
		e++;
	
		for (auto& t : team)
		{
			if (validAction == false)
			{ 
				

				for (auto& c : enemyHand)
					{
						auto d = CalculatePath(i.occupiedTile, t.occupiedTile);
						if (d.size() <= 1 && !d.empty() && i.character->stamina.first >= 10)
						{
							c.first->Cast(i.character, t.character);
							i.character->stamina.first -= 10;
							validAction = true;
						}

					}
					if (!validAction && i.character->movement.first > 0)
					{
						auto p = CalculatePath(i.occupiedTile, t.occupiedTile);
						if (p.size() > 1)
						{
							if (p.size() < i.character->movement.first)
							{
								i.SetTarget(p.back());
								i.character->movement.first -= p.size();
							}
							else
							{
								i.SetTarget(p[i.character->movement.first - 1]);
								i.character->movement.first = 0;

							}
							validAction = true;


						}
					
				}
			}
		}

	}
	if (!validAction)
		playerTurn = true;
}

std::vector<tile*> CombatScene::CalculatePath(tile* start, tile* end)
{
	std::vector<tile*> path;

	tile* currentTile = start;

	while (currentTile != end && currentTile!=nullptr)
	{
		int xDist = end->pos.first - currentTile->pos.first;
		int yDist = end->pos.second - currentTile->pos.second;

		if (std::abs(xDist) > 0)
		{
			if (xDist < 0)
			{
				if (currentTile->left != nullptr)
				{
					currentTile = currentTile->left;
				}
			}
			else
			{
				if (currentTile->right != nullptr)
				{
					currentTile = currentTile->right;
				}
			}
		}
		
		
		if (std::abs(yDist) > 0)
		{
			if (yDist < 0)
			{
				if (currentTile->down != nullptr)
				{
					currentTile = currentTile->down;
				}
			}
			else
			{
				if (currentTile->up != nullptr)
				{
					currentTile = currentTile->up;
				}
			}
		}
		

		

	
			if (currentTile != nullptr && (path.empty() || currentTile != path.back()))
			{

				path.push_back(currentTile);
			}
			else
				currentTile = nullptr;
		
	}

	return path;
}