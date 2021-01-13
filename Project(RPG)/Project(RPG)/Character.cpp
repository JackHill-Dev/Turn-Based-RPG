#include "Character.h"

Character::Character(std::string objectName, std::string portraitName)
{
	this->objectName = objectName;
	mPortraitName = portraitName;
}

Character::~Character()
{
	//delete object;
	//object = nullptr;
}	


int Character::GetHealth()
{
	return mStats.health.first;
}

bool Character::ModHealth(int mod)
{
	mStats.health.first -= mod;
	if (mStats.health.first > mStats.health.second)
		mStats.health.first = mStats.health.second;
	else
		if (mStats.health.first <= 0)
			return false;
	return true;
}