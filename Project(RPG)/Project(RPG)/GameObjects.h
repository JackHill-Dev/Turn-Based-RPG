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
		{"maleObj", new RenderObject("male")},
		{"femaleObj",new RenderObject("female")},
		{"playerPortraitObj",new RenderObject("playerPortrait")},
		{"merchantPortraitObj",new RenderObject("merchantPortrait")},
		{"WizardObj",new RenderObject("wizard")},
		{"RogueObj",new RenderObject("rogue")},
		{"ClericObj",new RenderObject("cleric")},
		{"WarriorObj",new RenderObject("warrior")},
		{"itemFrameObj",new RenderObject("itemFrame")},
		{"characterFrameObj",new RenderObject("characterFrame")},
		{"ShopBGObj",new RenderObject("shopBg")},
		{"swordObj",new RenderObject("sword")},
		{"potionObj",new RenderObject("potion")},
		{"armourObj",new RenderObject("armour")},
		{"overworldObj", new RenderObject("overworld")},
		{"battleNodeObj", new RenderObject("battleNode")},
		{"bossNodeObj", new RenderObject("bossNode")},
		{"shopNodeObj", new RenderObject("shopNode")},
		{"startNodeObj", new RenderObject("startNode")},
		{"StartBtnObj", new RenderObject("startBtn")},
		{"quitBtnObj", new RenderObject("quitBtn")},
		{"mainMenuBGObj",new RenderObject("mainMenuBG")},
		{"CloseBtnObj", new RenderObject("closeBtn")},
		{"cardObj", new RenderObject("card")},
		{"tileObj", new RenderObject("tile")},
		{"forestBGObj",new RenderObject("forestBG")},
		{"portrait", new RenderObject("malePortrait")},
		{"barBgObj", new RenderObject("barBg")},
		{"barFillObj", new RenderObject("barFill")},	
		{"armyViewerButtonObj", new RenderObject("armyViewerButton")},
		{"inventoryButtonObj", new RenderObject("inventoryButton")},
		{"menuButtonObj", new RenderObject("menuButton")},
		{"exitButtonObj", new RenderObject("exitButton")},
		{"settingsBtnObj", new RenderObject("settingsBtn")},
		{"settingsOverlayObj", new RenderObject("settingsOverlay")},
		{"resCollapsedObj", new RenderObject("resCollapsed")},
		{"resUnCollapsedObj", new RenderObject("resUnCollapsed")},
		{"OptionsBackgroundObj", new RenderObject("OptionsBackground")},
		{"ApplyBtnObj", new RenderObject("ApplyBtn")},
		{"checkBoxObj", new RenderObject("checkBox")},
		{"forestFightSceneBg", new RenderObject("fightSceneForest")},
		{"warSprObj",new RenderObject("warSpr")},
		{"rogSprObj",new RenderObject("rogSpr")},
		{"mageSprObj",new RenderObject("magSpr")},
		{"scrollBgObj", new RenderObject("scrollBg")},
		{"backBtnObj", new RenderObject("backBtn")},
		{"yesTxtBtnObj", new RenderObject("yesTxtBtn")},
		{"backTxtBtnObj", new RenderObject("backTxtBtn")},
	}
};

// Define sheets with an identifier, a sheet(Path, texture sizes(x,y), cell sizes(x,y) and cell count)
const std::map<std::string, SpriteSheet*> definedSheets
{
	{	{"fightSceneForest", new SpriteSheet("Assets/ForestFight.png",700, 400, 700, 400, 12)},
		{"male", new SpriteSheet("Assets/Sprites/Male 01-1.png",96, 128, 32, 32, 12)},
		{"female", new SpriteSheet("Assets/Sprites/Female 01.1.png", 96, 128, 32, 32, 12)},
		{"startBtn", new SpriteSheet("Assets/Sprites/Buttons/StartBtn-02.png",128, 64, 128, 64, 12)},
		{"quitBtn", new SpriteSheet("Assets/Sprites/Buttons/QuitBtn.png",128, 64, 128, 64, 12)},
		{"closeBtn", new SpriteSheet("Assets/Sprites/Buttons/CloseBtn2.png",32, 32, 32, 32, 1)},
		{"mainMenuBG", new SpriteSheet("Assets/Backgrounds/MainMenuBG_720.png",1280, 720, 1280, 720, 1)},
		{"overworld", new SpriteSheet("Assets/Backgrounds/Blank_Map_1280x720.png", 1280, 720, 1280, 720, 1)},
		{"battleNode", new SpriteSheet("Assets/Sprites/BattleNode.png", 32, 32, 32, 32, 1)},
		{"bossNode", new SpriteSheet("Assets/Sprites/BossNode.png", 32, 32, 32, 32, 1)},
		{"shopNode", new SpriteSheet("Assets/Sprites/ShopNode.png", 32,32, 32, 32, 1)},
		{"startNode", new SpriteSheet("Assets/Sprites/StartNode.png", 32, 32, 32, 32, 1)},
		{"playerPortrait", new SpriteSheet("Assets/Sprites/Portraits/PlayerPortrait.png",210, 330, 210, 330, 1)},
		{"merchantPortrait", new SpriteSheet("Assets/Sprites/Portraits/MerchantPortrait.png",210, 330, 210, 330, 1)},
		{"wizard", new SpriteSheet("Assets/Sprites/Portraits/Wizard.png",177, 243, 177, 243, 1)},
		{"rogue", new SpriteSheet("Assets/Sprites/Portraits/Rogue.png",177, 243, 177, 243, 1)},
		{"cleric", new SpriteSheet("Assets/Sprites/Portraits/Cleric.png",177, 243, 177, 243, 1)},
		{"warrior", new SpriteSheet("Assets/Sprites/Portraits/Warrior.png",177, 243, 177, 243, 1)},
		{"shopBg", new SpriteSheet("Assets/Backgrounds/ShopBg.png",1280, 720, 1280, 720, 1)},
		{"itemFrame", new SpriteSheet("Assets/Backgrounds/ItemFrame.png",85, 105, 85, 105, 1)},
		{"characterFrame", new SpriteSheet("Assets/Backgrounds/CharacterFrame.png",228, 624, 228, 624, 1)},
		{"sword", new SpriteSheet("Assets/Sprites/sword-art.png",160, 256, 32, 32, 40)},
		{"armour", new SpriteSheet("Assets/Sprites/armour.png",76, 72, 76, 72, 1)},
		{"potion", new SpriteSheet("Assets/Sprites/potion.png",48, 48, 48, 48, 1)},
		{"card", new SpriteSheet("Assets/Sprites/Cards/CardTemplate.png",230, 322, 230, 322, 1)},
		{"tile", new SpriteSheet("Assets/Backgrounds/grass-tile.png", 32, 32, 32, 32, 1)},
		{"forestBG", new SpriteSheet("Assets/Backgrounds/forestbackground.png",1280, 720, 1280, 720, 1)},
		{"malePortrait", new SpriteSheet("Assets/Portrait.png",	357, 364, 357, 364, 1)},
		{"barBg", new SpriteSheet("Assets/Sprites/Bar_Bg.png",	176, 32, 176, 32, 1)},
		{"barFill", new SpriteSheet("Assets/Sprites/Bar_fill.png",	176, 32, 176, 32, 1)},
		{"armyViewerButton", new SpriteSheet("Assets/Sprites/Buttons/Army_viewer_btn1.png", 200, 34, 200, 34, 1)},
		{"inventoryButton", new SpriteSheet("Assets/Sprites/Buttons/inventoryBtn1.png", 200, 34, 200, 34, 1)},
		{"menuButton", new SpriteSheet("Assets/Sprites/Buttons/MenuBtn1.png", 200, 34, 200, 34, 1)},
		{"exitButton", new SpriteSheet("Assets/Sprites/Buttons/exitButton.png", 200, 55, 200, 55, 1)},
		{"settingsBtn", new SpriteSheet("Assets/Sprites/Buttons/SettingsBtn.png",	128, 64, 128, 64, 1)},
		{"settingsOverlay", new SpriteSheet("Assets/Sprites/SettingsOverlay.png",	640, 480, 640, 480, 1)},
		{"resCollapsed", new SpriteSheet("Assets/Sprites/Buttons/dropDown-01.png",	240, 32, 240, 32, 1)},
		{"resUnCollapsed", new SpriteSheet("Assets/Sprites/Buttons/dropDown-02.png",	240, 96, 240, 96, 1)},
		{"OptionsBackground", new SpriteSheet("Assets/Sprites/OptionsBackground.png",	240, 32, 240, 32, 1)},
		{"ApplyBtn", new SpriteSheet("Assets/Sprites/Buttons/ApplyBtn.png",	128, 64, 128, 64, 1)},
		{"checkBox", new SpriteSheet("Assets/Sprites/Buttons/CheckBox.png",	128, 64, 64, 64, 2)},
		{"warSpr", new SpriteSheet("Assets/Sprites/WarriorSprite.png", 96, 128, 32, 32, 12)},
		{"rogSpr", new SpriteSheet("Assets/Sprites/ArcherSprite.png", 96, 128, 32, 32, 12)},
		{"magSpr", new SpriteSheet("Assets/Sprites/MageSprite.png", 96, 128, 32, 32, 12)},
		{"scrollBg", new SpriteSheet("Assets/Backgrounds/ResizedScroll.png", 1280, 720, 1280, 720, 1)},
		{"backBtn", new SpriteSheet("Assets/Sprites/Buttons/BackButtonNoBg.png", 81, 97, 81, 97, 1)},
		{"yesTxtBtn", new SpriteSheet("Assets/Sprites/Buttons/Yes.png", 54, 36, 54, 36, 1)},
		{"backTxtBtn", new SpriteSheet("Assets/Sprites/Buttons/Back.png", 71, 36, 71, 36, 1)},
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

		{"warSpr", 
			{
				Animation("LookUp", {std::make_pair(0,0)}),
				Animation("LookLeft", {std::make_pair(0,1)}),
				Animation("LookRight", {std::make_pair(0,2)}),
				Animation("LookDown", {std::make_pair(0,3)}),

				Animation("WalkUp", {std::make_pair(0,0), std::make_pair(1,0),std::make_pair(2,0)}),
				Animation("WalkLeft", {std::make_pair(0,1), std::make_pair(1,1), std::make_pair(2,1)}),
				Animation("WalkRight", {std::make_pair(0,2), std::make_pair(1,2), std::make_pair(2,2)}),
				Animation("WalkDown", {std::make_pair(0,3), std::make_pair(1,3), std::make_pair(2,3)}),
			}
		},

		{"rogSpr",
				{
					Animation("LookUp", {std::make_pair(0,0)}),
					Animation("LookLeft", {std::make_pair(0,1)}),
					Animation("LookRight", {std::make_pair(0,2)}),
					Animation("LookDown", {std::make_pair(0,3)}),

					Animation("WalkUp", {std::make_pair(0,0), std::make_pair(1,0),std::make_pair(2,0)}),
					Animation("WalkLeft", {std::make_pair(0,1), std::make_pair(1,1), std::make_pair(2,1)}),
					Animation("WalkRight", {std::make_pair(0,2), std::make_pair(1,2), std::make_pair(2,2)}),
					Animation("WalkDown", {std::make_pair(0,3), std::make_pair(1,3), std::make_pair(2,3)}),
				}
		},

		{"magSpr",
				{
					Animation("LookUp", {std::make_pair(0,0)}),
					Animation("LookLeft", {std::make_pair(0,1)}),
					Animation("LookRight", {std::make_pair(0,2)}),
					Animation("LookDown", {std::make_pair(0,3)}),

					Animation("WalkUp", {std::make_pair(0,0), std::make_pair(1,0),std::make_pair(2,0)}),
					Animation("WalkLeft", {std::make_pair(0,1), std::make_pair(1,1), std::make_pair(2,1)}),
					Animation("WalkRight", {std::make_pair(0,2), std::make_pair(1,2), std::make_pair(2,2)}),
					Animation("WalkDown", {std::make_pair(0,3), std::make_pair(1,3), std::make_pair(2,3)}),
				}
		},

		{"startBtn", {Animation("Hover", {std::make_pair(1,0)})}},
		{"checkBox", {Animation("Checked", {std::make_pair(1,0)})}},

		{"tile",
			{
				Animation("Grass", {std::make_pair(0,0)})
			}
		}
	}

	


};



		
	