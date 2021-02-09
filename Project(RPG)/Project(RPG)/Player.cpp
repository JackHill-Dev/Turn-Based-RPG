#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
	for (Character* c : mPartyMembers)
	{
		delete c;
		c = nullptr;
	}
}


void Player::AddToParty(Character* character)
{
	GetParty().push_back(character);
}

void Player::SetupParty(std::vector<Character*> characters)
{
	mPartyMembers = characters;
}



