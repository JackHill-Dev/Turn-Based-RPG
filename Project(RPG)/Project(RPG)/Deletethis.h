//#pragma once
//if (act == Act::Click)
//{
//	if (current == Selection::Any)
//	{
//		for (auto i : playerHand)
//			if (i->getObj() != nullptr && i->getObj()->InBounds(mouse.first, mouse.second))
//			{
//				selectedCard = i;
//			}
//		if (selectedCard != nullptr)
//		{
//			current = Selection::Team;
//			selectedCard->getObj()->Tint(SDL_Color{ 255,255,0 });
//		}
//		else
//		{
//
//			character = nullptr;
//			for (auto i : team)
//			{
//				if (i.first->getObj()->InBounds(mouse.first, mouse.second))
//				{
//					character->first = i.first;
//
//				}
//			}
//			if (character != nullptr)
//			{
//				current = Selection::Ground;
//				character->first->getObj()->tint = SDL_Color{ 255,255,0 };
//			}
//
//		}
//
//
//
//
//
//	}
//	else
//	{
//		switch (current)
//		{
//		case Ground:
//			if (std::find_if(team.begin(), team.end(), [](std::pair<Character*, tile*> t) {
//
//				if (character->first == t.first)
//					return true;
//				return false;
//
//
//				}) != team.end())
//				for (int y = 0; y < 15; ++y)
//					for (int x = 0; x < 15; ++x)
//						if (mapp.tiles[x][y].availiable && mapp.tiles[x][y].square->InBounds(mouse.first, mouse.second))
//						{
//							character->second->availiable = true;
//							character->first->SetTarget(mapp.tiles[x][y].pos);
//							mapp.tiles[x][y].availiable = false;
//						}
//
//				character->first->getObj()->Untint();
//				character = nullptr;
//				current = Selection::Any;
//				break;
//
//		case Enemy:
//			if (character != nullptr)
//			{
//				for (auto i : enemy)
//					if (i->getObj()->InBounds(mouse.first, mouse.second))
//					{
//						target = i;
//
//					}
//
//				if (target != nullptr)
//				{
//					Cast(selectedCard, character->first, target);
//					current = Selection::Any;
//				}
//			}
//			else
//				current = Selection::Team;
//			break;
//
//		case Team:
//
//			if (selectedCard != nullptr)
//			{
//				for (auto i : team)
//				{
//					if (i.first->getObj()->InBounds(mouse.first, mouse.second))
//					{
//						character->first = i.first;
//
//					}
//				}
//				if (character != nullptr)
//				{
//					character->first->getObj()->tint = (SDL_Color{ 255,255,0 });
//					current = Selection::Enemy;
//				}
//			}
//
//			break;
//
//		}
//	}
//}
//else
//if (act == Act::MouseUpdate)
//{
//	if (select != nullptr)
//		if (selectedCard == nullptr || selectedCard->getObj() != select)
//			if (character == nullptr || character->first->getObj() != select)
//				select->Untint();
//	select = nullptr;
//	if (current == Selection::Any || current == Selection::UICard)
//		for (int i = 0; i < playerHand.size(); i++)
//		{
//			if (selectedCard != playerHand[i] && playerHand[i]->getObj()->InBounds(mouse.first, mouse.second))
//				select = playerHand[i]->getObj();
//		}
//	if (select == nullptr)
//		for (int i = 0; i < team.size(); i++)
//		{
//			if (character == nullptr || character->first == nullptr || team[i].first != character->first)
//				team[i].first->getObj()->Untint();
//			if ((character == nullptr || character->first == nullptr || team[i].first != character->first) && team[i].first->getObj()->InBounds(mouse.first, mouse.second) && (Selection::Any || current == Selection::Team))
//				select = team[i].first->getObj();
//		}
//	else
//	{
//
//		for (int i = 0; i < team.size(); i++)
//		{
//
//			team[i].first->getObj()->tint = SDL_Color{ 0,0,255 };
//		}
//	}
//
//	if (select != nullptr)
//		select->tint = SDL_Color{ 0,255,0 };
//
//}
