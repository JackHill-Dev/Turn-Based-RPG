#pragma once
#include "Globals.h"
#include "RenderObject.h"
#include <map>
#include "SpriteSheet.h"
#include "Animation.h"



// Define objects with an identifier and a render object that refers to a specific spritesheet.
const std::map<std::string,RenderObject*> definedObjects
{
	{
		{"maleObj",new RenderObject("male")}, 
		{"maleUnit", new RenderObject("male")},
		/*
		{"startBtnObj", new RenderObject("startBtn")},
		{"quitBtnObj", new RenderObject("quitBtn")},
		{"mainMenuBGObj",new RenderObject("mainMenuBG")}, 
		{"cardObj", new RenderObject("card")},
		{"tileObj", new RenderObject("tile")},
		{"forestBGObj",new RenderObject("forestBG")}
	}
};

// Define sheets with an identifier, a sheet(Path, texture sizes(x,y), cell sizes(x,y) and cell count)
const std::map<std::string, SpriteSheet*> definedSheets
{
	{
		{"overworld", new SpriteSheet("Assets/Backgrounds/Blank_Map_1280x720.png", 1280, 720, 1280, 720, 1)},
		{"battleNode", new SpriteSheet("Assets/Sprites/BattleNode.png", 32, 32, 32, 32, 1)},
		{"bossNode", new SpriteSheet("Assets/Sprites/BossNode.png", 32, 32, 32, 32, 1)},
		{"shopNode", new SpriteSheet("Assets/Sprites/ShopNode.png", 32,32, 32, 32, 1)},
		{"startNode", new SpriteSheet("Assets/Sprites/StartNode.png", 32, 32, 32, 32, 1)},
		{"male", new SpriteSheet("Assets/Sprites/Male 01-1.png",96, 128, 32, 32, 12)}, 	
		{"startBtn", new SpriteSheet("Assets/Sprites/Buttons/StartBtn-02.png",128, 64, 128, 64, 12)},
		{"quitBtn", new SpriteSheet("Assets/Sprites/Buttons/QuitBtn.png",128, 64, 128, 64, 12)},
		{"mainMenuBG", new SpriteSheet("Assets/Backgrounds/MainMenuBG_720.png",1280, 720, 1280, 720, 1)},
		{"card", new SpriteSheet("Assets/Sprites/Cards/CardTemplate.png",230, 322, 230, 322, 1)},
		{"tile", new SpriteSheet("Assets/Backgrounds/grass-tile.png", 32, 32, 32, 32, 1)},
		{"forestBG", new SpriteSheet("Assets/Backgrounds/forestbackground.png",1280, 720, 1280, 720, 1)}
	}
};

const std::map<std::string, std::vector<Animation>> definedAnimations
{
	{
		// a defined vector of animations, make sure the name matches the sheet
		{"male", 
			{
				Animation("LookUp", {std::make_pair(0,0)}), 
				Animation("LookLeft", {std::make_pair(0,1)}),
				Animation("LookRight", {std::make_pair(0,2)}),
				Animation("LookDown", {std::make_pair(0,3)}),

				Animation("WalkUp", {std::make_pair(0,0), std::make_pair(1,0),std::make_pair(2,0)}),
				Animation("WalkLeft", {std::make_pair(0,1), std::make_pair(1,1), std::make_pair(2,1)}),
				Animation("WalkRight", {std::make_pair(0,2), std::make_pair(1,2), std::make_pair(2,2)}),
				Animation("WalkDown", {std::make_pair(0,3), std::make_pair(1,3), std::make_pair(2,3)})
			}
		},
		{"tile",
			{
				Animation("Grass", {std::make_pair(0,0)})
			}
		}
	}
};