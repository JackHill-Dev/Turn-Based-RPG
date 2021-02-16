#include "CombatScene.h"
#include <deque>

CombatScene::CombatScene(Interface* objmg) : Scene(objmg)
{
	
} 

void CombatScene::Update(double dTime, Act act, std::pair<int, int> mouse)
{
   
	if (fightScene <= 0)
	{
	
		for (auto e : mLayers[Effects])
		{
			delete(e);
		}
		mLayers[Effects].clear();


		// Win Condition - EH
		if (enemy.size() <= 0)
		{		
			for(auto i : team)
				RemoveUnit(&i);

			for (auto i : enemy)
				RemoveUnit(&i);

			mgr->LoadScene(Scenes::WinLoseStateScreen);
		}
			


		for (auto i : team)
		{
			if (i.character->GetHealth() <= 0)
			{
				i.character->Die();
				RemoveUnit(&i);

				// Lose Condition - EH
				if (team.size() <= 0)
				{
					for (auto i : enemy)
						RemoveUnit(&i);

					for (auto i : team)
						RemoveUnit(&i);
					mgr->LoadScene(Scenes::WinLoseStateScreen);
				}
			}
		}
				
		for (auto i : enemy)
		{
			if (i.character->GetHealth() <= 0)
			{
				mgr->GetPlayer()->AddToXpPool(i.character->GetStats().experience.first);
				RemoveUnit(&i);
			}
		}

		
		

		bool scenebusy = false;
		if (playerTurn)
		{
			for (auto& i : team)
				if (i.busy)
				{
					i.Move(dTime);
					scenebusy = true;
				}
			if (!scenebusy)
			{
				if (act == Act::Click)
				{
					if (!hovered.empty())
					{
						for (auto& i : hovered)
						{
							if (character != nullptr && character->object != nullptr && character->object == i)
							{

							}
							else
								if (selectedCard != nullptr && selectedCard->second != nullptr && selectedCard->second == i)
								{

								}
								else
									i->Untint();
						}
					}
					hovered.clear();
					
					if (endTurn->InBounds(mouse.first, mouse.second))
					{
						endTurn->Untint();

						for (int i = 0; i < playerhand.size(); ++i)
						{
							mLayers[UI].erase(std::find(mLayers[UI].begin(), mLayers[UI].end(), playerhand[i].second));

						}
						playerhand.clear();
						playerTurn = false;

						for (auto& i : team)
						{
							i.object->Untint();
						}

						for (auto& i : enemy)
						{
							i.character->GetStats().movement.first = i.character->GetStats().movement.second;
							i.character->GetStats().strength.first = i.character->GetStats().strength.second;

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
									i.second->tint = SDL_Color{ 255,255,0 };
									hovered.push_back(i.second);
									
									//hovered->tint = SDL_Color{ 255,255,0 };
									current = Selection::Team;
								}

							if (!found)
								for (auto& i : team)
									if (i.object->InBounds(mouse.first, mouse.second) || i.profile->InBounds(mouse.first, mouse.second))
									{
										character = &i;
										character->object->tint = SDL_Color{ 255,255,0 };
										if (selectedCard != nullptr)
											current = Selection::Enemy;
										current = Selection::Ground;
									}
						}
						else
						{
							switch (current)
							{
							case(Selection::Ground):

								for (int i = 0; i < gridTileLength; i++)
									for (int x = 0; x < gridTileLength; x++)
										if (mapp[i][x].square->InBounds(mouse.first, mouse.second) && &mapp[i][x] != character->occupiedTile)
										{
											auto path = CalculatePath(character->occupiedTile, &mapp[i][x]);
											int distance = path.size();
											if (distance <= character->character->GetStats().movement.first)
											{
												character->SetTarget(path);
												
												character->character->GetStats().movement.first -= distance;
											}
										}
								character->object->Untint();
								character = nullptr;
								current = Selection::Any;

								break;
							case(Selection::Team):
								for (auto& i : team)
									if (i.object->InBounds(mouse.first, mouse.second) || i.profile->InBounds(mouse.first, mouse.second))
									{
										if (i.character->GetStats().strength.first > 5)
										{
											character = &i;
											character->object->tint = SDL_Color{ 255,255,0 };
											current = Selection::Enemy;
										}
										
									}
								if (character == nullptr)
								{
									selectedCard->second->Untint();
									selectedCard = nullptr;
									current = Selection::Any;
								}
								break;
							case(Selection::Enemy):
								for (auto& i : enemy)
									if (i.object->InBounds(mouse.first, mouse.second) || i.profile->InBounds(mouse.first, mouse.second))
									{
										target = &i;
										
									}
								if (target == nullptr)
								{
									character->object->Untint();
									character = nullptr;
									selectedCard->second->Untint();
									selectedCard = nullptr;
									current = Selection::Any;
								}
								else
								{
									Cast(character, target,selectedCard);
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

						if (endTurn->InBounds(mouse.first, mouse.second))
						{
							endTurn->Tint({ 0,255,0 });
						}
						else
						{
							endTurn->Untint();
						}

						if (hoveredCard.first != nullptr)
						{
							hoveredCard.second->scale = std::make_pair(0.42f, 0.42f);
							hoveredCard.second->SetPos({ hoveredCard.second->GetPos().first, 650 });





							hoveredCard.first = nullptr;
							hoveredCard.second = nullptr;



							for (int i = 0; i < playerhand.size(); ++i)
							{
								float x = 100 * (i - ((float)playerhand.size() / 2 - 0.5f));

								float xpos = centre.first + x;
								playerhand[i].second->SetPos(std::make_pair(xpos, 650));
							}
						
						}
						if (!hovered.empty())
						{
							for (auto &i : hovered)
							{
								if (character != nullptr && character->object != nullptr && character->object == i)
								{

								}
								else
									if (selectedCard != nullptr && selectedCard->second != nullptr && selectedCard->second == i)
									{

									}
									else
										if (hoveredCard.first != nullptr && hoveredCard.second != nullptr && selectedCard->second == i)
										{

										}
										else
											i->Untint();
							}
						}
						hovered.clear();
						if (current == Selection::Any)
						{

							bool found = false;

							for (auto& i : playerhand)
								if (i.second->InBounds(mouse.first, mouse.second))
								{
									if (hoveredCard.first != nullptr)
									{
										hoveredCard.second->scale = std::make_pair(0.42f, 0.42f);
										hoveredCard.second->SetPos({ hoveredCard.second->GetPos().first, 650 });
										hoveredCard.first = nullptr;
										hoveredCard.second = nullptr;
										
									}
									found = true;
									//i.second->tint = SDL_Color{ 0,255,0 };
									hovered.push_back(i.second);
									hoveredCard = i;
									

									int offset = -60;

									for (int c = 0; c < playerhand.size(); ++c)
									{
										float x = 100 * (c - ((float)playerhand.size() / 2 - 0.5f) );

										float xpos = centre.first + x;
										if (playerhand[c] == i)
										{
											offset = 60;
											i.second->scale = { 1,1 };
											i.second->SetPos(std::make_pair(xpos, 550));
										}
										else
											playerhand[c].second->SetPos(std::make_pair(xpos + offset, 650));
										
									}

									
								}

							if (!found)
								for (auto& i : team)
									if (i.object->InBounds(mouse.first, mouse.second) || i.profile->InBounds(mouse.first, mouse.second))
									{
										found = true;
										i.object->tint = SDL_Color{ 0,255,0 };
										hovered.push_back(i.object);
									}
						}
						else
							switch (current)
							{
							case(Selection::Team):

								for (auto& i : team)
									if (i.object->InBounds(mouse.first, mouse.second) || i.profile->InBounds(mouse.first, mouse.second))
									{
										
										if (i.character->GetStats().strength.first > 5)
										{

											i.object->tint = SDL_Color{ 0, 255, 0 };
										}
										else
											i.object->tint = SDL_Color{ 255, 0, 0 };


										hovered.push_back(i.object);
										
									}

								break;
							case(Selection::Enemy):

								for (auto& i : enemy)
									if (i.object->InBounds(mouse.first, mouse.second))
									{
										i.object->tint = SDL_Color{ 0, 255, 0 };
										hovered.push_back(i.object);
										
									}

								break;
							case(Selection::Ground):
								bool found = false;
								for (int i = 0; i < gridTileLength; i++)
									for (int t = 0; t < gridTileLength; t++)
										if (!found && mapp[i][t].square->InBounds(mouse.first, mouse.second) )
										{
											auto path = CalculatePath(character->occupiedTile, &mapp[i][t]);
											int distance = path.size();
											

											found = true;
											


											for (int x = 0; x < path.size(); x++)
											{
												if(path[x] != character->occupiedTile && path[x]->availiable && x < character->character->GetStats().movement.first)
													path[x]->square->tint = SDL_Color{ 0,255,0 };
												else
													path[x]->square->tint = SDL_Color{ 255,0,0 };
												








												hovered.push_back(path[x]->square);
											}
										}

								break;
							}


					}
			}
		}
		else
		{
			for (auto& i : enemy)
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
	else
		fightScene -= (dTime/1000);
	

}

void CombatScene::Load(std::vector<Character*> enemyTeam, int seed)
{
	playerTurn = false;
	mgr->PlayMusic(combat_music, -1);
	int v = 0;
	enemyHand.clear();
	playerhand.clear();
	enemy.clear(); team.clear();
	for (auto &layer : mLayers)
	{
		for (auto obj : layer)
			delete obj;
		layer.clear();
	}

	srand(seed);




	combat_music = Mix_LoadMUS("Assets/Combat_Music.wav");
	slash_sfx = Mix_LoadWAV("Assets/SFX/slash.wav");
	endTurn = AddObject("EndTurnButtonObj", centre.first, 30, UI);
	endTurn->scale = std::make_pair(1, 1);
	AddObject("forestBGObj", 640, 360, Background);





	for (double i = 0; i < gridTileLength; i++)
	{
		for (double x = 0; x < gridTileLength; x++)
		{

			mapp[(int)i][(int)x].square = (AddObject("tileObj", (i - 4.5) * 32 + centre.first, x * 32 - 5 * 32 + centre.second - 32, Background));
			mapp[(int)i][(int)x].pos = std::make_pair((i - 4.5) * 32 + centre.first, x * 32 - 5 * 32 + centre.second - 32);
			mapp[(int)i][(int)x].square->SetAnim("Grass");


			if (std::rand() % 10 == 4)
			{
				auto tree = AddObject("TreeObj", mapp[(int)i][(int)x].pos.first, mapp[(int)i][(int)x].pos.second, Game);
				mapp[(int)i][(int)x].availiable = false;
				tree->SetScale(std::make_pair(0.25f, 0.25f));
			}
		}
	}
	for (int i = 0; i < gridTileLength; i++)
	{
		for (int x = 0; x < gridTileLength; x++)
		{

			if (x > 0)
			{
				mapp[i][x].down = (&mapp[i][x - 1]);
				mapp[i][x].adjacentTiles.push_back(mapp[i][x].down);
			}
			if (x < gridTileLength - 1)
			{
				mapp[i][x].up = (&mapp[i][x + 1]);
				mapp[i][x].adjacentTiles.push_back(mapp[i][x].up);
			}
			if (i > 0)
			{
				mapp[i][x].left = (&mapp[i - 1][x]);
				mapp[i][x].adjacentTiles.push_back(mapp[i][x].left);
			}
			if (i < gridTileLength - 1)
			{
				mapp[i][x].right = (&mapp[i + 1][x]);
				mapp[i][x].adjacentTiles.push_back(mapp[i][x].right);
			}

		}
	}




	
	for (auto i : mgr->GetPlayer()->GetParty())
	{
		i->GetStats().strength.first = i->GetStats().strength.second;
		Unit unit = Unit(i, &mapp[v][9], AddObject(i->GetObjName(), 0, 0, Game), AddObject("portrait", 250, 125+150*v, UI));


		unit.healthBar.SetObjects(AddObject("barBgObj", 250, 125 + 70 + 150 * v, UI), AddObject("barFillObj", 250, 125 + 70 + 150 * v, UI));
		unit.healthBar.Scale(std::make_pair(0.6, 0.6));
		unit.healthBar.OnChange((unit.character->GetStats().health.second - unit.character->GetStats().health.first)/ unit.character->GetStats().health.second * 100);


		//unit.object->scale = std::make_pair(0.5f, 0.5f);
		unit.profile->scale = std::make_pair(0.3f, 0.3f);
		team.push_back(unit);
		v++;
	}
	v = 0;

	for(auto i : enemyTeam)
	{
		Unit unit = Unit(i, &mapp[9-v][0], AddObject(i->GetObjName(), 0, 0, Game),AddObject("portrait", 1000, 125+150*v, UI));

		// Arbitrary experience to grant to player from defeating said unit in combat. - EH
		i->GetStats().experience.first = 100;

		unit.healthBar.SetObjects(AddObject("barBgObj", 1000, 125 + 70 + 150 * v, UI), AddObject("barFillObj", 1000, 125 + 70 + 150 * v, UI));
		unit.healthBar.Scale(std::make_pair(0.6, 0.6));
		unit.profile->scale = std::make_pair(0.3f, 0.3f);
		enemy.push_back(unit);
		v++;
	}

	//for (int i = 0; i < 5; i++)
	//{
	//	playerhand.push_back(std::make_pair(new Card(5, "Slash", 1, "cardObj"), AddObject("cardObj0", centre.first - 200 + 100 * i - 15, 650, UI)));
	//	playerhand.back().second->scale = std::make_pair( 0.4f, 0.4f);
	//}
	for (int i = 0; i < 5; i++)
	{
		enemyHand.push_back(std::make_pair(new Card(5, "Slash", 1, "cardObj", "swordSlashEffectObj", 0.5, 5,0,0), nullptr));
		
	}
	
}
void CombatScene::PlayFightAnimation()
{
	fightSceneTeamCharacter->SetVisible(true);
	fightSceneEnemyCharacter->SetVisible(true);
	fightSceneBg->SetVisible(true);
	fightScene = 0.5f;
	

}
void CombatScene::Cast(Unit* caster, Unit* target, const std::pair<Card*,  RenderObject*>* card)
{
	auto d = card->first->GetEffect();
	auto stats = &caster->character->GetStats();
	auto dist = GetDistance(caster->occupiedTile, target->occupiedTile);
	target->object->Untint();
	caster->object->Untint();
	if (dist <= card->first->Values().range && 
		stats->strength.first >= card->first->Values().stamCost)
	{
		mgr->PlaySFX(slash_sfx,0, 1);
		card->first->Cast(caster->character, target->character);
		caster->character->GetStats().strength.first -= card->first->Values().stamCost;
		caster->character->GetStats().intelligence.first -= card->first->Values().intCost;
		caster->character->GetStats().agility.first -= card->first->Values().agilCost;

		AddObject(card->first->GetEffect().first, centre.first, centre.second, Effects);
		//PlayFightAnimation();
		fightScene = card->first->GetEffect().second;



		if (playerTurn)
		{

			mLayers[UI].erase(std::find(mLayers[UI].begin(), mLayers[UI].end(), card->second));
			playerhand.erase(std::find_if(playerhand.begin(), playerhand.end(), [card](std::pair<Card*, RenderObject*> cd)

				{
					//for (int i = 0; i < playerhand.size(); i++)
					//{
					//	//reorder cards
					//	//playerhand[i].second->SetPos({ center.fi100 * i- playerhand.size()/2 * 100,650 });
					//}
					return(card->first == cd.first);
				})
			);



			for (int i = 0; i < playerhand.size(); ++i)
			{
				float x = 100 * (i - ((float)playerhand.size() / 2 - 0.5f));

				float xpos = centre.first + x;
				playerhand[i].second->SetPos(std::make_pair(xpos, 650));
			}
		}
		else
		{
			enemyHand.erase(std::find_if(enemyHand.begin(), enemyHand.end(), [card](std::pair<Card*, RenderObject*> cd)
				{

					return(card->first == cd.first);
				})
			);
		}

		
	}
}

void CombatScene::RemoveUnit(Unit* unit)
{
		auto p = std::find(mLayers[Game].begin(), mLayers[Game].end(), unit->object);
		mLayers[Game].erase(p);
		mLayers[UI].erase(std::find(mLayers[UI].begin(), mLayers[UI].end(), unit->profile));
		delete unit->object;
		delete unit->profile;
		unit->occupiedTile->availiable = true;
		auto i = std::find_if(team.begin(), team.end(), [unit](Unit u) {
			return (u.character == unit->character);
			});
		if (i != team.end())
		{
			team.erase(i);
		}
		else
		{
			i = std::find_if(enemy.begin(), enemy.end(), [unit](Unit u) {
				return (u.character == unit->character);
				});
			if (i == enemy.end())
				std::cout << "Error, enemy not found error 01";
			enemy.erase(i);
		}
	
	//delete unit.character;
}
void CombatScene::RunAi()
{

	bool validAction = false;
	for (auto &i : enemy)
	{
		auto stats = &i.character->GetStats();
		if (!validAction)
		{
			std::deque<std::pair<Card*,RenderObject*>> validCards;

			for (auto &c : enemyHand)
			{
				if (stats->strength.first >= c.first->Values().stamCost && stats->intelligence.first >= c.first->Values().intCost && stats->agility.first >= c.first->Values().agilCost)
					validCards.push_back(c);
			}

			if (!validCards.empty())
			{
				for (auto e : team)
				{
					if(!validAction)
					for (auto c : validCards)
					{
						if (GetDistance(i.occupiedTile, e.occupiedTile) <= c.first->Values().range && !validAction)
						{
							validAction = true;
							Cast(&i, &e, &c);
						}
					}

					if (!validAction)
					{
						for (auto c : validCards)
						{
							for (auto e : team)
							{
								auto path = CalculatePath(i.occupiedTile, e.occupiedTile);
								if (path.size() <= stats->movement.first && GetDistance(path.back(),e.occupiedTile) <= c.first->Values().range)
								{
									i.SetTarget(path);
									validAction = true;
									stats->movement.first -= path.size();
								}
							}
						}
					}
				}
			}

			if (!validAction)
			{
				int dist = 0;
				Unit* target = nullptr;
				if (!validCards.empty())
				{
					for (auto& e : team)
					{
						int distToTarget = GetDistance(i.occupiedTile, e.occupiedTile);
						if (target == nullptr || distToTarget < dist)
						{
							dist = distToTarget;
							target = &e;
						}
					}

					if (target != nullptr)
					{
						auto path = CalculatePath(i.occupiedTile, target->occupiedTile);
						while (path.size() > stats->movement.first)
						{
							path.pop_back();
						}
						if (!path.empty())
						{
							stats->movement.first -= path.size();
							i.SetTarget(path);
							validAction = true;
						}
					}
				}
			}
		}

		
			
	}


	if (!validAction)
	{
		
		for (int i = 0; i < playerhand.size(); ++i)
		{
			mLayers[UI].erase(std::find(mLayers[UI].begin(), mLayers[UI].end(), playerhand[i].second));
			
		}
		playerhand.clear();
		

		while (playerhand.size() < 5)
		{

			auto cd = mgr->GetPlayer()->deck[std::rand() % mgr->GetPlayer()->deck.size()];

			auto found = std::find_if(playerhand.begin(), playerhand.end(), [cd](std::pair<Card*, RenderObject*> obj) {
				return obj.first == cd;
				});

			if (found == playerhand.end())
			{

				float x = 100 * (playerhand.size() - 2.0);

				float xpos = centre.first + x;
				playerhand.push_back(std::make_pair(cd, AddObject(cd->GetObjName(), xpos, 650, UI)));
				playerhand.back().second->scale = std::make_pair(0.42f, 0.42f);
			}
		}

		for (auto i : team)
		{
			i.character->GetStats().strength.first = i.character->GetStats().strength.second;
			i.character->GetStats().movement.first = i.character->GetStats().movement.second;
		}
		playerTurn = true;
	
	}
		
}

std::vector<CombatScene::tile*> CombatScene::CalculatePath(tile* start, tile* end)
{
	struct pathNode
	{
		pathNode(tile* node) : node(node)
		{

		}
		tile* node;
		int hcost = 1000;
		int gcost = 1000;
		int fcost = 1000;
		pathNode* prev = nullptr;
	};

	std::vector<pathNode*> map;







	for(int i = 0; i < gridTileLength; i++)
		for (int t = 0; t < gridTileLength; t++)
			map.push_back(new pathNode(&mapp[i][t]));



	std::vector<pathNode*> open;
	std::vector<pathNode*> closed;

	pathNode* current = *std::find_if(map.begin(), map.end(), [start](pathNode* node)
		{
			return node->node == start;
		});
	current->fcost = 0;
	current->hcost = 0;
	current->gcost = 0;
	open.push_back(current);
	while (!open.empty() && !(current->node== end))
	{
		open.erase(std::find(open.begin(), open.end(), current));
		closed.push_back(current);

		for (auto &i : current->node->adjacentTiles)
		{
			auto it = std::find_if(closed.begin(), closed.end(), [i](pathNode* nod) {return i == nod->node; });
			if (it == closed.end() && (i->availiable || i == end))
			{
				it = std::find_if(open.begin(), open.end(), [i](pathNode* nod) {return i == nod->node; });
				if (it == open.end())
				{
					auto p = std::find_if(map.begin(), map.end(), [i](pathNode* nod) {return i == nod->node; });
					if (p == map.end())
						std::cerr << "tile not found";
					open.push_back(*p);
					it = open.end() - 1;
				}
				auto node = open[it - open.begin()];
				node->prev = current;
				node->gcost = 10 + current->gcost;
				node->hcost = GetDistance(node->node, end);
				node->fcost = node->gcost + node->hcost;
			}
		}
		int currentValue = INT_MAX;
		for (auto& i : open)
		{
			if (i->fcost < currentValue)
			{
				current = i;
				currentValue = current->fcost;
			}
		}
	}

	std::vector<tile*> path;
	path.push_back(current->node);
	while (current->prev != nullptr)
	{
		path.push_back(current->prev->node);
		current = current->prev;
	}
	std::reverse(path.begin(), path.end());
	if (!end->availiable)
		path.erase(path.end() - 1);
	
	return path;
}







