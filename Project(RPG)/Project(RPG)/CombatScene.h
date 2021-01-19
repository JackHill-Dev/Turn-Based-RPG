#pragma once
#include "Scene.h"
#include "Card.h"

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
		bool SetTarget(tile* tile)
		{
			if (tile->availiable)
			{
				
				occupiedTile->availiable = true;
				busy = true;
				occupiedTile = tile;
				occupiedTile->availiable = false;
				return true;

			}
			return false;
		}
		void Move(double dTime)
		{
			std::pair<double, double> target = occupiedTile->pos;
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
					object->SetAnim("LookUp");
					busy = false;
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
    };
	void Load(std::vector<Character*> enemy);
    CombatScene(Interface* objmg);
    void Update(double dTime, Act act,std::pair<int, int> mouse) override;
private:
	void RunAi();
	void Cast(std::pair<Card*, RenderObject*>* card);
	void RemoveUnit(Unit unit);
    std::vector<Character> chars{};
    std::vector<Card*> playerHand{};
	std::vector<tile*> CalculatePath(tile* start, tile* end);
	void RemoveCard(std::pair<Card*, RenderObject*>* cd);
};

