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
	for (auto i : team)
		if (i->getObj() != nullptr)
		{
			{
				i->Update(dTime);
			}
		}

	if (act == Act::Click)
	{
		if (current == Selection::Any)
		{
			for (auto i : playerHand)
				if (i->getObj() != nullptr && i->getObj()->InBounds(mouse.first, mouse.second))
				{
					selectedCard = i;
				}
			if (selectedCard != nullptr)
			{
				current = Selection::Team;
				selectedCard->getObj()->Tint(SDL_Color{ 255,255,0 });
			}
			else
			{

				character = nullptr;
				for (auto i : team)
				{
					if (i->getObj()->InBounds(mouse.first, mouse.second))
					{
						character = i;

					}
				}
				if (character != nullptr)
				{
					current = Selection::Ground;
					character->getObj()->tint = SDL_Color{ 255,255,0 };
				}

			}
		




		}
		else
		{
			switch (current)
			{
			case Ground:
				if (std::find(team.begin(), team.end(), character) != team.end())
					character->SetTarget(mouse);
				character->getObj()->Untint();
				character = nullptr;
				current = Selection::Any;
				break;

			case Enemy:
				if (character != nullptr)
				{
					for (auto i : enemy)
						if (i->getObj()->InBounds(mouse.first, mouse.second))
						{
							target = i;

						}

					if (target != nullptr)
					{
						Cast(selectedCard, character, target);
						current = Selection::Any;
					}
				}
				else
					current = Selection::Team;
				break;

			case Team:

				if(selectedCard != nullptr)
				{
					for (auto i : team)
					{
						if (i->getObj()->InBounds(mouse.first, mouse.second))
						{
							character = i;

						}
					}
					if (character != nullptr)
					{
						character->getObj()->tint = (SDL_Color{ 255,255,0 });
						current = Selection::Enemy;
					}
				}
			
				break;

			}
		}
	}
	else
		if (act == Act::MouseUpdate)
		{

		}
	
}


void CombatScene::Cast(Card* card, Character* caster, Character* target)
{
	if (card != nullptr && caster != nullptr && target != nullptr)
	{
		character->getObj()->Untint();
		card->Cast(caster, target);
		character = nullptr;
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

	Card* card = new Card(5, "slash", 1, "cardObj");
	deck.push_back(card);
	playerHand.push_back(card);
	if(deck.size() > 0)
	for (int i = 0; i < playerHand.size(); ++i)
	{

		
			
		deck[i]->Assign(AddObject(card->GetObjName(), 200 + 150 * i, 200, UI));
		deck[i]->getObj()->scale = 0.5f;
		
	}

	current = Selection::Any;
}


