#include "Animation.h"
void Animation::Advance()
{
	current++;
	if (current > end)
	{
		current = start;

	}
}
Animation::Animation(std::string name, int st, int en, int curr)
{
	this->name = name; 
	start = st;
	end = en;
	current = curr;
}

int Animation::GetCurrentFrame()
{
	return current;
}

std::string Animation::GetName()
{
	return name;
}