#pragma once
#include "Globals.h"
#include "RenderObject.h"

struct Statistics
{
	std::pair<int, int> health = { 15,15 }; // max, current
	std::pair<int, int> mana = { 10,10 };
	std::pair<int, int> agility = { 10,10 };
	std::pair<int, int> stamina = { 10,10 };
	std::pair<int, int> movement = { 5,5 };
};

class Character
{
public:

	Statistics GetStats() { return mStats; }
	Character(std::string objectName, std::string portrait);
	~Character();
	RenderObject* getObj();
	void Update(double dTime);
	void Assign(RenderObject* object);
	std::string GetObjName() { return objectName; };
	std::string GetPortraitName() { return portraitName; };
	void SetTarget(std::pair<double, double> target);
	bool ModHealth(int mod);
	bool moving = false;


protected:

	Statistics mStats;
	void Move(double dTime);
	std::string objectName;
	RenderObject* object;
	std::string portraitName;
	std::pair<double, double> target;
};

