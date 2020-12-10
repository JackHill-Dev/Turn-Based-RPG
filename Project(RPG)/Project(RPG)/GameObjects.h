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
		{"StartBtnObj",new RenderObject("startBtn")}
	}
};

const std::map<std::string, SpriteSheet*> definedSheets
{
	{
		{"male", new SpriteSheet("Assets/Sprites/Male/Male 01-1.png", 32, 12)}, // a defined sheet
		{"startBtn", new SpriteSheet("Assets/Sprites/StartBtn.png", 128, 12)} // a defined sheet
	}
};

const std::map<std::string, std::vector<Animation>> definedAnimations
{
	{
		//{"Sheet1", {Animation("Jump", 0, 1, 0)}} // a defined vector of animations, make sure the name matches the sheet
	}
};