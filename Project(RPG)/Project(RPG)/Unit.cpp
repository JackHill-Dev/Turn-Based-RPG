#include "Unit.h"

bool Unit::Update(double dTime, Act act, std::pair<int, int> mouse)
{
	Move(dTime);
	return true;
}


void Unit::Move(double dTime)
{
	
		double yDistance = target.second - mPos.second;
		double xDistance = target.first - mPos.first;
		if (yDistance != 0)
		{
			if (std::abs(yDistance) < 1.f)
				mPos.second = target.second;


			if (yDistance > 0)
			{
				mPos.second += dTime * 0.1f;
				SetAnim("WalkUp");
			}
			else if (yDistance < 0)
			{
				mPos.second -= dTime * 0.1f;
				SetAnim("WalkDown");
			}
		}
		else
		{
			if (std::abs(xDistance) < 1.f)
			{
				mPos.first = target.first;
				SetAnim("LookUp");
			}
			else
			{


				if (xDistance > 0)
				{
					mPos.first += dTime * 0.1f;
					SetAnim("WalkRight");
					
				}
				else if (xDistance < 0)
				{
					mPos.first -= dTime * 0.1f;
					SetAnim("WalkLeft");

				}
			}
		

		


		


	}
	
}

void Unit::SetTarget(std::pair<double, double> target)
{

	this->target = target;
}


void Unit::SetPosition(std::pair<float, float> pos)
{
	SetPos(pos);
	target = pos;
}

Unit::Unit(std::string sprSheet) : RenderObject(sprSheet)
{
	target = mPos;
}