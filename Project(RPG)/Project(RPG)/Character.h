#pragma once
#include "Globals.h"
#include "RenderObject.h"
class Character
{
public:
	int GetHealth();
	Character(std::string objectName);
	~Character();
	RenderObject* getObj();
	void Update(double dTime);
	void Assign(RenderObject* object);
	std::string GetObjName() { return objectName; };
	void SetTarget(std::pair<double, double> target);
	bool ModHealth(int mod);
	bool moving = false;
protected:
	std::pair<int, int> health = { 15,15 }; // max, current
	std::pair<int, int> mana = { 10,10 };
	std::pair<int, int> agility = { 10,10 };
	std::pair<int, int> stamina = { 10,10 };
	std::pair<int, int> movement = { 5,5 };
	void Move(double dTime);
	std::string objectName;
	RenderObject* object;
	
	std::pair<double, double> target;
};

