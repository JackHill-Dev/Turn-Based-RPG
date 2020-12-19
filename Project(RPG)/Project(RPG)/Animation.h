#pragma once
#include "Globals.h"
class Animation
{
private:
	int current;
	std::string name;
	std::vector<std::pair<int, int>> frames;
	float speed = 0.5f;
	double time = 0;
public:
	void Advance(double dTime);
	Animation();
	Animation(std::string name, std::vector<std::pair<int, int>>);
	std::pair<int, int> GetCurrentFrame();
	std::string GetName();
};