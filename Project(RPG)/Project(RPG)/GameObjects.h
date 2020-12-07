#pragma once
#include "Globals.h"
#include "RenderObject.h"
#include <map>
#include "SpriteSheet.h"
#include "Animation.h"
const std::map<std::string,RenderObject*> definedObjects
{
	{
		{"Object1",new RenderObject("Sheet1")} // a defined object
	}
};

const std::map<std::string, SpriteSheet*> definedSheets
{
	{
		{"Sheet1", new SpriteSheet("Male.png", 32, 16)} // a defined sheet
	}
};

const std::map<std::string, std::vector<Animation>> definedAnimations
{
	{
		{"Sheet1", {Animation("Jump", 0, 1, 0)}} // a defined vector of animations, make sure the name matches the sheet
	}
};