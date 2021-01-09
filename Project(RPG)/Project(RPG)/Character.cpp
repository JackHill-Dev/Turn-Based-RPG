#include "Character.h"

Character::Character(std::string objectName, std::string portrait)
{
	this->objectName = objectName;
	portraitName = portrait;
}

Character::~Character()
{
	//delete object;
	//object = nullptr;
}

RenderObject* Character::getObj()
{
	return object;
}

void Character::Update(double dTime)
{
	if(object != nullptr)
		Move(dTime);
}

void Character::Assign(RenderObject* object)
{
	this->object = object;
	object->SetAnim("default");
}

//void Character::SetPortrait(RenderObject* portrait)
//{
//	portraitObj = portrait;
//	portraitObj->SetAnim("default");
//}

void Character::SetTarget(std::pair<double, double> target)
{
	this->target = target;
}

void Character::Move(double dTime)
{
	double xPos = object->GetPos().first;
	double yPos = object->GetPos().second;
	double yDistance = target.second - object->GetPos().second;
	double xDistance = target.first - object->GetPos().first;
	moving = true;
	
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
			moving = false;
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


int Character::GetHealth()
{
	return health.first;
}

int Character::GetMana()
{
	return mana.first;
}

int Character::GetAgility()
{
	return agility.first;
}

int Character::GetStamina()
{
	return stamina.first;
}

int Character::GetMovement()
{
	return movement.first;
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