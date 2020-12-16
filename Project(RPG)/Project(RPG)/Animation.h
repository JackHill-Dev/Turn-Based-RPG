#pragma once
#include "Globals.h"
class Animation
{
private:
	int current;
	std::string name;
	std::vector<std::pair<int, int>> frames;
public:
	void Advance();
	Animation(std::string name, std::vector<std::pair<int, int>>);
	std::pair<int, int> GetCurrentFrame();
	std::string GetName();
};