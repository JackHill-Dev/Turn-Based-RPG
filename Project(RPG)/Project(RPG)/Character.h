#pragma once
#include "Globals.h"
#include "RenderObject.h"
class Character
{
public:
	int GetHealth();
	Character(std::string objectName);
	~Character();

	std::string GetObjName() { return objectName; };
	
	bool ModHealth(int mod);
	bool moving = false;
	std::pair<int, int> health =   { 15,15 }; // max, current
	std::pair<int, int> mana =	   { 10,10 };
	std::pair<int, int> agility =  { 10,10 };
	std::pair<int, int> stamina =  { 10,10 };
	std::pair<int, int> movement = {  5,5  };
protected:
	
	
	std::string objectName;
	RenderObject* object;
	
	std::pair<double, double> target;
};

