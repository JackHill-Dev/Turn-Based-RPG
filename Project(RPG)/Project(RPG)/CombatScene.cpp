#include "CombatScene.h"
Character charac{"maleObj"};

Character* character;
Character* target;
Card* selectedCard = nullptr;



std::vector<Card*> deck;

std::pair<int, int> lastMousePos = { 0,0 };

enum Selection{Team,Enemy,Ground, UICard, Any};
Selection current = Team;
CombatScene::CombatScene(GameManager* objmg) : Scene(objmg)
{
	

	

	charac.Assign(AddObject(charac.GetObjName(), 400, 400, Game));
	chars.push_back(charac);

} 


CombatScene* CombatScene::Load(std::vector<Character*> player, std::vector<Character*> enemy)
{
	this->team = player;
	this->enemy = enemy;
	int v = 0;
	LoadHand();
	for (auto i : team)
	{
		
		i->Assign(AddObject(i->GetObjName(), 0, v * 50, Game));
		v++;
	}
	v = 0;
	for (auto i : this->enemy)
	{
	
		i->Assign(AddObject(i->GetObjName(), 300, v * 50, Game));
		v++;
	}
	return this;
}

void CombatScene::Update(double dTime, Act act, std::pair<int, int> mouse)
{	
	for (auto i : chars)
		if (i.getObj() != nullptr)
	{
		{
			i.Update(dTime);
		}
	}

	if (act == Act::Click)
	{
		if (current == Selection::Ground)
		{
			if (std::find(team.begin(), team.end(), character) != team.end())
				character->SetTarget(mouse);
			current = Selection::Any;
		}

		else 
			if (current == Selection::Enemy)
			{
				if (character != nullptr)
				{
					for (auto i : enemy)
						if (i->getObj()->InBounds(mouse.first, mouse.second))
						{
							target = i;

						}

					if (target != nullptr)
					{
						Cast(selectedCard,character, target);
						current = Selection::Any;
					}
				}
				else
					current = Selection::Team;
			}
		
		else
			if (current == Selection::Team || current == Selection::Any)
			{
				for (auto i : team)
					if (i->getObj()->InBounds(mouse.first, mouse.second))
					{
						character = i;
						
					}

				if (character != nullptr)
				{

					if (selectedCard != nullptr)
					{
						current = Selection::Enemy;
					}
					else
					{
						current = Selection::Ground;
					}
				}
			}
		else
			if (current == Selection::UICard || current == Selection::Any)
			{
				//selected = 
				for(auto i: playerHand)
					if (i->getObj() != nullptr && i->getObj()->InBounds(mouse.first, mouse.second))
					{
						selectedCard = i;
					}
				if (selectedCard != nullptr)
					current = Selection::Team;
			}
		
			
	}

	else if (act == Act::MouseUpdate)
	{

	}
}


void CombatScene::Cast(Card* card, Character* caster, Character* target)
{
	card->Cast(caster, target);
	character = nullptr;
	target = nullptr;
	delete (card->getObj());
	//card->getObj() = nullptr;
}


void CombatScene::LoadHand()
{

	 
	for (auto i : playerHand)
		delete i->getObj();
	playerHand.clear();

	Card* card = nullptr;

	if(deck.size() > 0)
	for (int i = 0; i < 5; ++i)
	{

		card = deck[0];
			
		card->Assign(AddObject(card->GetObjName(), 50, 50, UI));

		playerHand.push_back(card);
	}

	
}


