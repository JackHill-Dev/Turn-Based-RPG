#pragma once
#include "Globals.h"
#include "RenderObject.h"
#include <map>
#include "SpriteSheet.h"
#include "Animation.h"
#include "Button.h"
#include "StartButton.h"
#include "QuitButton.h"

const std::map<std::string,RenderObject*> definedObjects
{
	{
		{"maleObj",new RenderObject("male")}, // a defined object
		{"mainMenuBGObj",new RenderObject("mainMenuBG")}, // a defined object
		{"StartBtnObj",new StartButton("startBtn")},
		{"QuitBtnObj",new QuitButton("quitBtn")}
	}
};

const std::map<std::string, SpriteSheet*> definedSheets
{
	{
		{"male", new SpriteSheet("Assets/Sprites/Male/Male 01-1.png",96, 128, 32, 32, 12)}, // a defined sheet
		{"startBtn", new SpriteSheet("Assets/Sprites/Buttons/StartBtn-02.png",128, 64, 128, 64, 12)},
		{"quitBtn", new SpriteSheet("Assets/Sprites/Buttons/QuitBtn.png",128, 64, 128, 64, 12)},
		{"mainMenuBG", new SpriteSheet("Assets/Backgrounds/MainMenuBG_720.png",1280, 720, 1280, 720, 1)}
	}
};

const std::map<std::string, std::vector<Animation>> definedAnimations
{
	{
		{"male", {Animation("WalkLeft", {std::make_pair(0,0),std::make_pair(1,0),std::make_pair(2,1)})}} // a defined vector of animations, make sure the name matches the sheet
	}
};