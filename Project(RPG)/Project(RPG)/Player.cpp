#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::AssignNought()
{
	isNought = true;
}

void Player::AssignCross()
{
	isCrosses = true;
}

void Player::PlayerWon()
{
	++winTally;
}

void Player::PlayerLoss()
{
	++loseTally;
}

void Player::ResetTally()
{
	winTally = 0;
	loseTally = 0;
}
