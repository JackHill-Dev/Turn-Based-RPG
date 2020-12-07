#pragma once
#include "Globals.h"
class Animation
{
private:
	int start, end, current;
	std::string name;
public:
	void Advance();
	Animation(std::string name, int st, int en, int curr);
	int GetCurrentFrame();
	std::string GetName();
};

