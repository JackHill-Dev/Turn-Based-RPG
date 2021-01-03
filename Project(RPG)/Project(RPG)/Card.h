#pragma once
#include "Character.h"

class Card
{
	enum TargetType { Self, Enemy };
	int range;
	int damage;
	std::string name;
	TargetType targetType;
	RenderObject* obj;
	std::string objectName;
public:
	Card(int damage, std::string name, int range, std::string objectName);
	void Cast(Character* caster, Character* target);
	RenderObject* getObj();
	void Assign(RenderObject* object);
	std::string GetObjName() { return objectName; };

};

