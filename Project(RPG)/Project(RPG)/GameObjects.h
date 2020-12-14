#pragma once
#include "Globals.h"
#include "RenderObject.h"
#include <map>
#include "SpriteSheet.h"
#include "Animation.h"
const std::map<std::string,RenderObject*> definedObjects
{
	{
		{"maleObj",new RenderObject("male")}, // a defined object
		{"overworldObj", new RenderObject("overworld")},
	}
};

const std::map<std::string, SpriteSheet*> definedSheets
{
	{
		{"male", new SpriteSheet("Assets/Sprites/Male/Male 01-1.png", 32, 32, 12)}, // a defined sheet
		{"overworld", new SpriteSheet("Assets/Backgrounds/testOverworld.png", 2048, 1536, 1)},
	}
};

const std::map<std::string, std::vector<Animation>> definedAnimations
{
	{
		//{"Sheet1", {Animation("Jump", 0, 1, 0)}} // a defined vector of animations, make sure the name matches the sheet
	}
};