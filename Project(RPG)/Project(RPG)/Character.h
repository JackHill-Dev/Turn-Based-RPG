#pragma once
#include "Globals.h"
#include "RenderObject.h"
class Character
{
public:
	int GetHealth();
	int GetMana();
	int GetAgility();
	int GetStamina();
	int GetMovement();
	Character(std::string objectName, std::string portrait);
	~Character();
	RenderObject* getObj();
	//RenderObject* GetPortrait() { return portraitObj; }
	void Update(double dTime);
	void Assign(RenderObject* object);
	std::string GetObjName() { return objectName; };
	std::string GetPortraitName() { return portraitName; };
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
	//RenderObject* portraitObj;
	std::string portraitName;
	std::pair<double, double> target;
};

