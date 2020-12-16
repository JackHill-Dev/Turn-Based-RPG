#include "Animation.h"
void Animation::Advance()
{
	current++;
	if (current > frames.size())
		current = 0;
}
Animation::Animation(std::string name, std::vector<std::pair<int,int>> anims)
{
	this->frames = anims;
	this->name = name; 
	current = 0;
}

std::pair<int,int> Animation::GetCurrentFrame()
{
	return frames[current];
}

std::string Animation::GetName()
{
	return name;
}