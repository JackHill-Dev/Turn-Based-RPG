#include "Card.h"

Card::Card(int damage, std::string name, int range, std::string objectName, std::string effect, double effectLength) : name(name), cardValues(range, damage, 10, 0, 0), effect(effect), objectName(objectName), effectLength(effectLength)
{

}
void Card::Cast(Character* caster, Character* target)
{
	target->ModHealth(cardValues.damage);
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