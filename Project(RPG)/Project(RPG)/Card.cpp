#include "Card.h"

Card::Card(TargetType targetType, int damage, std::string name, int range, std::string objectName) : targetType(targetType), damage(damage), name(name), range(range), objectName(objectName)
{

}


void Card::Cast(Character* caster, Character* target)
{
	target->ModHealth(damage);
}

RenderObject* Card::getObj()
{
	return obj;
}

void Card::Assign(RenderObject* object)
{
	this->obj = object;
	object->SetAnim("default");
}