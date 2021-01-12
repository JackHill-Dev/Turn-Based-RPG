#include "Character.h"

Character::Character(std::string objectName)
{
	this->objectName = objectName;
}

Character::~Character()
{
	//delete object;
	//object = nullptr;
}	


int Character::GetHealth()
{
	return health.first;
}

bool Character::ModHealth(int mod)
{
	health.first -= mod;
	if (health.first > health.second)
		health.first = health.second;
	else
		if (health.first <= 0)
			return false;
	return true;
}