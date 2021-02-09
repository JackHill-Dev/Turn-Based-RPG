#include "CombatScene.h"
#include <deque>

double fightScene = 0;
RenderObject* endTurn;
RenderObject* pExit;
bool playerTurn = false; // Is it the players turn
std::deque<RenderObject*> hovered;
typedef CombatScene::tile tile;
typedef CombatScene::Unit Unit;
Unit* character = nullptr;
Unit* target;
std::pair<Card*, RenderObject*>* selectedCard = nullptr;
std::deque <Unit> team{};
std::deque <Unit> enemy{};
std::vector<std::pair<Card*, RenderObject*>> playerhand;
std::vector<std::pair<Card*, RenderObject*>> enemyHand;
Mix_Music* combat_music1;
Mix_Chunk* slash_sfx;
RenderObject* fightSceneTeamCharacter;
RenderObject* fightSceneEnemyCharacter;
RenderObject* fightSceneBg;
std::pair<Card*, RenderObject*> hoveredCard;

struct map
{
	tile tiles[15][15];
};

map mapp;

std::vector<Card*> deck;

std::pair<double, double> centre = { 640,360 };
enum Selection{Team,Enemy,Ground, UICard, Any};
Selection current = Any;

void CloseCombatScene()
{

}

CombatScene::CombatScene(Interface* objmg) : Scene(objmg)
{
	combat_music1 = Mix_LoadMUS("Assets/Combat_Music.wav");
	mCombatMusic2 = Mix_LoadMUS("Assets/Music/BattleIntesification.mp3");
	mCombatMusic3 = Mix_LoadMUS("Assets/Music/Boss.mp3");
	mVictoryMusic = Mix_LoadMUS("Assets/Music/VictoryWindlessSlopes.mp3");
	mDefeatNoLoop = Mix_LoadMUS("Assets/Music/Game-over-silence.mp3");

	mCombatPlaylist.push_back(combat_music1);
	mCombatPlaylist.push_back(mCombatMusic2);
	mCombatPlaylist.push_back(mCombatMusic3);


	slash_sfx = Mix_LoadWAV("Assets/SFX/slash.wav");
	mVictorySFX = Mix_LoadWAV("Assets/SFX/VictorySfx.wav");


	fightSceneBg = AddObject("forestFightSceneBg", centre.first, centre.second, UI);
	fightSceneTeamCharacter = AddObject("maleObj", centre.first - 50, centre.second, UI);
	fightSceneTeamCharacter->SetAnim("WalkRight");
	fightSceneEnemyCharacter = AddObject("maleObj", centre.first + 50, centre.second, UI);
	fightSceneEnemyCharacter->SetAnim("WalkLeft");
	fightSceneTeamCharacter->scale = std::make_pair(3, 3);
	fightSceneEnemyCharacter->scale = std::make_pair(3, 3);
	fightSceneTeamCharacter->SetVisible(false);
	fightSceneEnemyCharacter->SetVisible(false);
	fightSceneBg->SetVisible(false);
	
	endTurn = AddObject("quitBtnObj", centre.first, 20, UI);
	endTurn->scale = std::make_pair(1, 1);
	pExit = AddObject("exitButtonObj", 600, 600, UI);
	AddObject("forestBGObj", 640, 360, Background);
	//reload = AddObject("quitBtnObj", 1100, 500, UI);

	for (double i = 0; i < 15; i++)
	{
		for (double x = 0; x < 15; x++)
		{

			mapp.tiles[(int)i][(int)x].square = (AddObject("tileObj", (i - 7)*32 + centre.first, x*32 - 7.5 *32 + centre.second - 32, Background));
			mapp.tiles[(int)i][(int)x].pos = std::make_pair((i  - 7) * 32 + centre.first, x * 32 - 7.5 * 32 + centre.second - 32);
			mapp.tiles[(int)i][(int)x].square->SetAnim("Grass");


			if (std::rand() % 10 == 4)
			{
				auto tree = AddObject("TreeObj", mapp.tiles[(int)i][(int)x].pos.first, mapp.tiles[(int)i][(int)x].pos.second, Game);
				mapp.tiles[(int)i][(int)x].availiable = false;
				tree->SetScale(std::make_pair(0.25f, 0.25f));
			}
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


void RemoveCard(std::pair<Card*, RenderObject*>* cd)
{

}

void CombatScene::Update(double dTime, Act act, std::pair<int, int> mouse)
{
   
	if (fightScene <= 0)
	{
		fightSceneEnemyCharacter->SetVisible(false);
		fightSceneTeamCharacter->SetVisible(false);
		fightSceneBg->SetVisible(false);


		for (auto e : mLayers[Effects])
		{
			delete(e);
		}
		mLayers[Effects].clear();


		if (enemy.size() <= 0)
		{
		
			for(auto i : team)
				RemoveUnit(&i);
			for (auto i : enemy)
				RemoveUnit(&i);

			//This simulates a victory for now for music testing purposes - EH			
			mgr->PlaySFX(mVictorySFX, 0, 1);
			//mgr->FadeInMusic(mVictoryMusic, -1, mgr->fadeTime);
			mgr->LoadPreviousScene();
		}
			
		for (auto i : team)
			if (i.character->GetHealth() <= 0)
				RemoveUnit(&i);
		for (auto i : enemy)
			if (i.character->GetHealth() <= 0)
				RemoveUnit(&i);
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
						for (int i = 0; i < playerhand.size(); ++i)
						{
							mLayers[UI].erase(std::find(mLayers[UI].begin(), mLayers[UI].end(), playerhand[i].second));

						}
						playerhand.clear();
						playerTurn = false;
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

								for (int i = 0; i < 15; i++)
									for (int x = 0; x < 15; x++)
										if (mapp.tiles[i][x].square->InBounds(mouse.first, mouse.second) && &mapp.tiles[i][x] != character->occupiedTile)
										{
											auto path = CalculatePath(character->occupiedTile, &mapp.tiles[i][x]);
											int distance = path.size();
											if (distance <= character->character->GetStats().movement.first)
											{
												character->SetTarget(path);
												character->object->Untint();
												character->character->GetStats().movement.first -= distance;
											}
										}

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
								for (int i = 0; i < 15; i++)
									for (int t = 0; t < 15; t++)
										if (!found && mapp.tiles[i][t].square->InBounds(mouse.first, mouse.second) )
										{
											auto path = CalculatePath(character->occupiedTile, &mapp.tiles[i][t]);
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

void CombatScene::Load(std::vector<Character*> enemyTeam)
{
	playerTurn = false;
	mgr->FadeInMusic(mCombatMusic2, -1, mgr->fadeTime); // For testing purposes as I don't have the first one. Eventually randomly pick one for variety? -EH
	//mgr->PlayMusic(combat_music1, -1);
	int v = 0;

	// TO-DO: Seems to be a bug here - Doesn't actually contain the range when stepping through and counts double party size for some reason - EH
	for (auto i : mgr->GetPlayer()->GetParty())
	{
		i->GetStats().strength.first = i->GetStats().strength.second;
		Unit unit = Unit(i, &mapp.tiles[v][14], AddObject(i->GetObjName(), 0, 0, Game), AddObject("portrait", 250, 125+150*v, UI));
		//unit.object->scale = std::make_pair(0.5f, 0.5f);
		unit.profile->scale = std::make_pair(0.3f, 0.3f);
		team.push_back(unit);
		v++;
	}
	v = 0;

	for(auto i : enemyTeam)
	{
		Unit unit = Unit(i, &mapp.tiles[14-v][0], AddObject(i->GetObjName(), 0, 0, Game),AddObject("portrait", 1000, 125+150*v, UI));
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
		enemyHand.push_back(std::make_pair(new Card(5, "Slash", 1, "cardObj", "swordSlashEffectObj"), nullptr));
		
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
	if (card->first->GetEffect() == "swordSlashEffectObj")
	{
		std::cout << "AHH";
	}
	if (dist <= card->first->Values().range && 
		stats->strength.first >= card->first->Values().stamCost && stats->intelligence.first >= card->first->Values().intCost && stats->agility.first >= card->first->Values().agilCost)
	{
		mgr->PlaySFX(slash_sfx,0, 1);
		card->first->Cast(caster->character, target->character);
		caster->character->GetStats().strength.first -= card->first->Values().stamCost;
		caster->character->GetStats().intelligence.first -= card->first->Values().intCost;
		caster->character->GetStats().agility.first -= card->first->Values().agilCost;

		AddObject(card->first->GetEffect(), centre.first, centre.second, Effects);
		PlayFightAnimation();

		if (playerTurn)
		{

			mLayers[UI].erase(std::find(mLayers[UI].begin(), mLayers[UI].end(), card->second));
			playerhand.erase(std::find_if(playerhand.begin(), playerhand.end(), [card](std::pair<Card*, RenderObject*> cd)

				{
					for (int i = 0; i < playerhand.size(); i++)
					{
						//reorder cards
						//playerhand[i].second->SetPos({ center.fi100 * i- playerhand.size()/2 * 100,650 });
					}
					return(card->first == cd.first);
				})
			);
		}
		else
		{
			enemyHand.erase(std::find_if(enemyHand.begin(), enemyHand.end(), [card](std::pair<Card*, RenderObject*> cd)
				{

					return(card->first == cd.first);
				})
			);
		}

		if (card->first->GetEffect() == "swordSlashEffectObj")
		{
			std::cout << "AHH";
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

std::deque<tile*> CombatScene::CalculatePath(tile* start, tile* end)
{
	std::deque<tile*> path;
	int bestScore = 10000;
	tile* currentTile = start;
	tile* nextTile = nullptr;
	while (currentTile != end && currentTile!=nullptr)
	{
		

		
		
		for (auto i : currentTile->adjacentTiles)
		{
			
			int xDist = std::abs(end->pos.first - i->pos.first);
			int yDist = std::abs(end->pos.second - i->pos.second);
			int value = xDist + yDist;
			if ((currentTile != i && currentTile != end && i->availiable&& value < bestScore))
			{
				bestScore = value;
				currentTile = i;
			}

		}


		
		
		if (path.empty() || currentTile != path.back())
		{
			//currentTile->availiable = false;
			path.push_back(currentTile);
		}
		else
			currentTile = nullptr;
		
	}
	if(!path.empty() && !end->availiable && path.back() == end)
			path.pop_back();

	return path;
}







