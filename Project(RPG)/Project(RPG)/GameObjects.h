#pragma once
#include "Globals.h"
#include "RenderObject.h"
#include <map>
#include "SpriteSheet.h"
#include "Animation.h"
#include "Button.h"
#include "StartButton.h"
#include "QuitButton.h"
#include "Unit.h"

const std::map<std::string,RenderObject*> definedObjects
{
	{
		{"maleObj",new RenderObject("male")}, // a defined object
		{"maleUnit", new Unit("male")},
		{"mainMenuBGObj",new RenderObject("mainMenuBG")}, 
		{"playerPortraitObj",new RenderObject("playerPortrait")},
		{"merchantPortraitObj",new RenderObject("merchantPortrait")},
		{"swordObj",new RenderObject("sword")},
		{"armourObj",new RenderObject("armour")},
		{"StartBtnObj",new StartButton("startBtn")},
		{"QuitBtnObj",new QuitButton("quitBtn")}
	}
};

const std::map<std::string, SpriteSheet*> definedSheets
{
	{
		{"male", new SpriteSheet("Assets/Sprites/Male/Male 01-1.png",96, 128, 32, 32, 12)}, // a defined sheet
		{"startBtn", new SpriteSheet("Assets/Sprites/Buttons/StartBtn-Sheet.png",128, 64, 128, 64, 12)},
		{"quitBtn", new SpriteSheet("Assets/Sprites/Buttons/QuitBtn.png",128, 64, 128, 64, 12)},
		{"mainMenuBG", new SpriteSheet("Assets/Backgrounds/MainMenuBG_720.png",1280, 720, 1280, 720, 1)},
		{"playerPortrait", new SpriteSheet("Assets/Sprites/Portraits/PlayerPortrait.png",210, 330, 210, 330, 1)},
		{"merchantPortrait", new SpriteSheet("Assets/Sprites/Portraits/MerchantPortrait.png",210, 330, 210, 330, 1)},
		{"sword", new SpriteSheet("Assets/Sprites/sword-art.png",160, 256, 32, 32, 40)},
		{"armour", new SpriteSheet("Assets/Sprites/armour.png",76, 72, 76, 72, 1)}
	}
};

const std::map<std::string, std::vector<Animation>> definedAnimations
{
	{
		{"male", {// a defined vector of animations, make sure the name matches the sheet
		Animation("LookUp", {std::make_pair(0,0)}), 
		Animation("LookLeft", {std::make_pair(0,1)}),
		Animation("LookRight", {std::make_pair(0,2)}),
		Animation("LookDown", {std::make_pair(0,3)}),

		Animation("WalkUp", {std::make_pair(0,0), std::make_pair(1,0),std::make_pair(2,0)}),
		Animation("WalkLeft", {std::make_pair(0,1), std::make_pair(1,1), std::make_pair(2,1)}),
		Animation("WalkRight", {std::make_pair(0,2), std::make_pair(1,2), std::make_pair(2,2)}),
		Animation("WalkDown", {std::make_pair(0,3), std::make_pair(1,3), std::make_pair(2,3)}),


		}} ,

		{"startBtn", {Animation("Hover", {std::make_pair(1,0)})}}
	}
};