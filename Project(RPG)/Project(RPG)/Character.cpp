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

void Character::ModHealth(int mod)
{
	health.first += mod;
}