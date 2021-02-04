#pragma once
#include "Scene.h"
#include "Card.h"
#include <deque>
class CombatScene :
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

    struct Unit
    {
		std::deque<tile*> currentPath;
		RenderObject* object;
		RenderObject* profile;
        Character* character;
        bool busy = false;
		tile* occupiedTile;
		Unit(Character* character, tile* tile, RenderObject* object, RenderObject* profile) : object(object), character(character), occupiedTile(tile), profile(profile)
		{
			object->SetPos(occupiedTile->pos);
			occupiedTile->availiable = false;
		}
		bool SetTarget(std::deque<tile*> path)
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
						currentPath.pop_front();
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
	void Load(std::vector<Character*> enemy);
    CombatScene(Interface* objmg);
    void Update(double dTime, Act act,std::pair<int, int> mouse) override;
private:
	void PlayFightAnimation();
	void RunAi();
	void Cast(Unit* caster, Unit* target, const std::pair<Card*, RenderObject*>* card);
	void RemoveUnit(Unit* unit);
    std::vector<Character> chars{};
    std::vector<Card*> playerHand{};
	std::vector<Mix_Music*> mCombatPlaylist;

	Mix_Chunk* mVictorySFX;
	Mix_Music* mDefeatNoLoop;
	Mix_Music* mVictoryMusic;
	Mix_Music* mCombatMusic2;
	Mix_Music* mCombatMusic3;

	std::deque<tile*> CalculatePath(tile* start, tile* end);
	void RemoveCard(std::pair<Card*, RenderObject*>* cd);
	double GetDistance(tile* start, tile* end) { return std::abs(std::sqrt(std::pow(end->pos.first - start->pos.first, 2) + std::pow(end->pos.second - start->pos.second, 2)))/32; }
};

