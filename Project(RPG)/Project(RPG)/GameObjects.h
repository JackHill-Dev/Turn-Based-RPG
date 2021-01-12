#pragma once
#include <map>
#include "Globals.h"
#include "RenderObject.h"
#include "SpriteSheet.h"
#include "Animation.h"



// Define objects with an identifier and a render object that refers to a specific spritesheet.
const std::map<std::string,RenderObject*> definedObjects
{
	{
		{"maleObj",new RenderObject("male")},
		{"playerPortraitObj",new RenderObject("playerPortrait")},
		{"merchantPortraitObj",new RenderObject("merchantPortrait")},
		{"itemFrameObj",new RenderObject("itemFrame")},
		{"ShopBGObj",new RenderObject("shopBg")},
		{"swordObj",new RenderObject("sword")},
		{"potionObj",new RenderObject("potion")},
		{"armourObj",new RenderObject("armour")},
		{"overworldObj", new RenderObject("overworld")},
		{"battleNodeObj", new RenderObject("battleNode")},
		{"bossNodeObj", new RenderObject("bossNode")},
		{"shopNodeObj", new RenderObject("shopNode")},
		{"startNodeObj", new RenderObject("startNode")},
		{"maleUnit", new RenderObject("male")},
		{"StartBtnObj", new RenderObject("startBtn")},
		{"QuitBtnObj", new RenderObject("quitBtn")},
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
		{"male", new SpriteSheet("Assets/Sprites/Male/Male 01-1.png",96, 128, 32, 32, 12)},
		{"startBtn", new SpriteSheet("Assets/Sprites/Buttons/StartBtn-02.png",128, 64, 128, 64, 12)},
		{"quitBtn", new SpriteSheet("Assets/Sprites/Buttons/QuitBtn.png",128, 64, 128, 64, 12)},
		{"mainMenuBG", new SpriteSheet("Assets/Backgrounds/MainMenuBG_720.png",1280, 720, 1280, 720, 1)},
		{"overworld", new SpriteSheet("Assets/Backgrounds/Blank_Map_1280x720.png", 1280, 720, 1280, 720, 1)},
		{"battleNode", new SpriteSheet("Assets/Sprites/BattleNode.png", 32, 32, 32, 32, 1)},
		{"bossNode", new SpriteSheet("Assets/Sprites/BossNode.png", 32, 32, 32, 32, 1)},
		{"shopNode", new SpriteSheet("Assets/Sprites/ShopNode.png", 32,32, 32, 32, 1)},
		{"startNode", new SpriteSheet("Assets/Sprites/StartNode.png", 32, 32, 32, 32, 1)},
		{"playerPortrait", new SpriteSheet("Assets/Sprites/Portraits/PlayerPortrait.png",210, 330, 210, 330, 1)},
		{"merchantPortrait", new SpriteSheet("Assets/Sprites/Portraits/MerchantPortrait.png",210, 330, 210, 330, 1)},
		{"shopBg", new SpriteSheet("Assets/Backgrounds/ShopBg.png",1280, 720, 1280, 720, 1)},
		{"itemFrame", new SpriteSheet("Assets/Backgrounds/ItemFrame.png",85, 105, 85, 105, 1)},
		{"sword", new SpriteSheet("Assets/Sprites/sword-art.png",160, 256, 32, 32, 40)},
		{"armour", new SpriteSheet("Assets/Sprites/armour.png",76, 72, 76, 72, 1)},
		{"potion", new SpriteSheet("Assets/Sprites/potion.png",48, 48, 48, 48, 1)},
		{"card", new SpriteSheet("Assets/Sprites/Card/CardTemplate.png",230, 322, 230, 322, 1)},
		{"tile", new SpriteSheet("Assets/Backgrounds/grass-tile.png", 32, 32, 32, 32, 1)},
		{"forestBG", new SpriteSheet("Assets/Backgrounds/forestbackground.png",1280, 720, 1280, 720, 1)}
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

		{"startBtn", {Animation("Hover", {std::make_pair(1,0)})}},

		{"tile",
			{
				Animation("Grass", {std::make_pair(0,0)})
			}
		}
	}

	


};



		
	