#pragma once
#include "Scene.h"
#include "Card.h"
#include <deque>
#include "ProgressBar.h"
class BossScene :
	public Scene
{
public:
	struct tile
	{
		RenderObject* square = NULL;
		std::pair<float, float> pos;
		bool availiable = true;
		tile* up;
		tile* down;
		tile* right;
		tile* left;
		std::vector<tile*> adjacentTiles;

	};

	struct UIStats
	{
		UIText* health;
		UIText* movement;
		UIText* strength;
		UIText* intelligence;
		UIText* agility;

		UIStats(std::pair<float, float> position, UIText* health, UIText* movement, UIText* strength, UIText* intelligence, UIText* agility) : health(health), movement(movement), strength(strength), intelligence(intelligence), agility(agility)
		{

			float scale = 25;


			health->pos = std::make_pair(position.first - 50, position.second);
			health->SetTextScale(scale, scale);
			health->textColor = SDL_Color{ 255, 0, 0 };
			movement->pos = std::make_pair(position.first - 20, position.second);
			movement->SetTextScale(scale, scale);
			movement->textColor = SDL_Color{ 0, 0, 0 };
			strength->pos = std::make_pair(position.first + 10, position.second);
			strength->SetTextScale(scale, scale);
			strength->textColor = SDL_Color{ 255, 255, 0 };
			intelligence->pos = std::make_pair(position.first + 40, position.second);
			intelligence->SetTextScale(scale, scale);
			intelligence->textColor = SDL_Color{ 0, 0, 255 };
			agility->pos = std::make_pair(position.first + 70, position.second);
			agility->SetTextScale(scale, scale);
			agility->textColor = SDL_Color{ 0, 255, 0 };
		}
		void SetVisibility(bool visible)
		{
			health->isVisible = visible;
			movement->isVisible = visible;
			strength->isVisible = visible;
			intelligence->isVisible = visible;
			agility->isVisible = visible;
		}
		void UpdateStats(Character* character)
		{
			auto s = character->GetStats();



			health->text = std::to_string(s.health.first) + "/" + std::to_string(s.health.second);
			movement->text = std::to_string(s.movement.first) + "/" + std::to_string(s.movement.second);
			strength->text = std::to_string(s.strength.first) + "/" + std::to_string(s.strength.second);
			intelligence->text = std::to_string(s.intelligence.first) + "/" + std::to_string(s.intelligence.second);
			agility->text = std::to_string(s.agility.first) + "/" + std::to_string(s.agility.second);
			//movement->text = s.movement.first + "/" + s.movement.second;
			//strength->text = s.strength.first + "/" + s.strength.second;
			//intelligence->text = s.intelligence.first + "/" + s.intelligence.second;
			//agility->text = s.agility.first + "/" + s.agility.second;
		}

	};

	struct Unit
	{
		UIStats visualStats;
		std::vector<tile*> currentPath;
		RenderObject* object;
		RenderObject* profile;
		Character* character;
		bool busy = false;
		tile* occupiedTile;
		void Update()
		{
			visualStats.UpdateStats(character);
		}
		Unit(Character* character, tile* tile, RenderObject* object, RenderObject* profile, UIStats visualStats) : object(object), character(character), occupiedTile(tile), profile(profile), visualStats(visualStats)
		{
			object->SetPos(occupiedTile->pos);
			occupiedTile->availiable = false;
			visualStats.UpdateStats(character);
		}
		bool SetTarget(std::vector<tile*> path)
		{
			occupiedTile->availiable = true;
			occupiedTile = path.back();
			occupiedTile->availiable = false;
			currentPath = path;
			busy = true;
			return false;
		}
		void Move(double dTime)
		{


			if (currentPath.size() > 0)
			{



				std::pair<double, double> target = currentPath.front()->pos;
				double xPos = object->GetPos().first;
				double yPos = object->GetPos().second;
				double yDistance = target.second - object->GetPos().second;
				double xDistance = target.first - object->GetPos().first;

				if (yDistance != 0)
				{
					if (std::abs(yDistance) < 1.f)
						yPos = target.second;

					if (yDistance > 0)
					{
						yPos += dTime * 0.1f;
						object->SetAnim("WalkUp");
					}
					else if (yDistance < 0)
					{
						yPos -= dTime * 0.1f;
						object->SetAnim("WalkDown");
					}
				}
				else
				{
					if (std::abs(xDistance) < 1.f)
					{
						xPos = target.first;
						//object->SetAnim("LookUp");
						//currentPath.pop_front();
						currentPath.erase(currentPath.begin());
					}
					else
					{
						if (xDistance > 0)
						{
							xPos += dTime * 0.1f;
							object->SetAnim("WalkRight");

						}
						else if (xDistance < 0)
						{
							xPos -= dTime * 0.1f;
							object->SetAnim("WalkLeft");

						}
					}
				}
				object->SetPos(std::make_pair(xPos, yPos));

			}
			else
			{
				busy = false;
				object->SetAnim("LookUp");
			}
		}

	};
	void Load();
	BossScene(Interface* objmg);
	void Update(double dTime, Act act, std::pair<int, int> mouse) override;
private:
	void PlayFightAnimation();
	void RunAi();
	void Cast(Unit* caster, Unit* target, const std::pair<Card*, RenderObject*>* card);
	void RemoveUnit(Unit* unit);
	std::vector<Character> chars{};
	std::vector<Card*> playerHand{};

	std::vector<tile*> CalculatePath(tile* start, tile* end);
	void RemoveCard(std::pair<Card*, RenderObject*>* cd);;
	double GetDistance(tile* start, tile* end) { return std::abs(std::sqrt(std::pow(end->pos.first - start->pos.first, 2) + std::pow(end->pos.second - start->pos.second, 2))) / 32; }
	const int gridTileLength = 10;

	double fightScene = 0;
	RenderObject* endTurn;
	RenderObject* pExit;
	bool playerTurn = false; // Is it the players turn
	std::deque<RenderObject*> hovered;
	typedef BossScene::tile tile;
	typedef BossScene::Unit Unit;
	Unit* character = nullptr;
	Unit* target;
	std::pair<Card*, RenderObject*>* selectedCard = nullptr;
	std::deque <Unit> team{};
	std::deque <Unit> enemy{};
	std::vector<std::pair<Card*, RenderObject*>> playerhand;
	std::vector<std::pair<Card*, RenderObject*>> enemyHand;
	Mix_Music* combat_music;
	Mix_Chunk* slash_sfx;
	RenderObject* fightSceneTeamCharacter;
	RenderObject* fightSceneEnemyCharacter;
	RenderObject* fightSceneBg;
	std::pair<Card*, RenderObject*> hoveredCard;
	ProgressBar healthbar;

	std::vector<Card*> deck;

	std::pair<double, double> centre = { 640,360 };
	enum Selection { Team, Enemy, Ground, UICard, Any };
	Selection current = Any;

	tile mapp[10][10];
};

