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
		// Character Sprite objects

		{"femaleObj",new RenderObject("female")},
		{"mageObj",new RenderObject("mage")},
		{"mageSprObj",new RenderObject("magSpr")},
		{"maleObj", new RenderObject("male")},
		{"nobleSpriteObj", new RenderObject("nobleSprite")},
		{"rogSprObj",new RenderObject("rogSpr")},
		{"scholarSpriteObj", new RenderObject("scholarSprite")},
		{"villagerSpriteObj", new RenderObject("villagerSprite")},
		{"warSprObj",new RenderObject("warSpr")},
		{"daemonBoss", new RenderObject("daemonSpr")},
		
		// Portrait Objects 

		{"ClericObj",new RenderObject("cleric")},
		{"merchantPortraitObj",new RenderObject("merchantPortrait")},
		{"playerPortraitObj",new RenderObject("playerPortrait")},
		{"portrait", new RenderObject("malePortrait")},
		{"RogueObj",new RenderObject("rogue")},
		{"WarriorObj",new RenderObject("warrior")},
		{"WizardObj",new RenderObject("wizard")},

		// Item Objects

		{"armourObj",new RenderObject("armour")},
		{"potionObj",new RenderObject("potion")},
		{"swordObj",new RenderObject("sword")},

		// Background Objects

		{"characterFrameObj",new RenderObject("characterFrame")},
		{"forestBGObj",new RenderObject("forestBG")},
		{"forestFightSceneBg", new RenderObject("fightSceneForest")},
		{"itemFrameObj",new RenderObject("itemFrame")},
		{"mainMenuBGObj",new RenderObject("mainMenuBG")},
		{"OptionsBackgroundObj", new RenderObject("OptionsBackground")},
		{"overworldObj", new RenderObject("overworld")},
		{"scrollBgObj", new RenderObject("scrollBg")},
		{"ShopBGObj",new RenderObject("shopBg")},
		{"tileObj", new RenderObject("tile")},	
		{"stoneTileObj", new RenderObject("stone-tile")},
		{"TreeObj", new RenderObject("tree")},
		{"settingsBgObj", new RenderObject("settingsBg")},
			
		// Button Objects

		{"ApplyBtnObj", new RenderObject("ApplyBtn")},
		{"armyViewerButtonObj", new RenderObject("armyViewerButton")},
		{"backBtnObj", new RenderObject("backBtn")},
		{"backTxtBtnObj", new RenderObject("backTxtBtn")},
		{"CloseBtnObj", new RenderObject("closeBtn")},
		{"exitButtonObj", new RenderObject("exitButton")},
		{"inventoryButtonObj", new RenderObject("inventoryButton")},
		{"menuButtonObj", new RenderObject("menuButton")},
		{"quitBtnObj", new RenderObject("quitBtn")},
		{"settingsBtnObj", new RenderObject("settingsBtn")},
		{"StartBtnObj", new RenderObject("startBtn")},
		{"yesTxtBtnObj", new RenderObject("yesTxtBtn")},

		// Node Objects

		{"battleNodeObj", new RenderObject("battleNode")},
		{"bossNodeObj", new RenderObject("bossNode")},
		{"shopNodeObj", new RenderObject("shopNode")},
		{"nodeObj", new RenderObject("startNode")},

		// Card Objects

		{"cardObj", new RenderObject("card")},
				
		// More Traditional UI Objects

		{"barBgObj", new RenderObject("barBg")},
		{"barFillObj", new RenderObject("barFill")},	
		{"checkBoxObj", new RenderObject("checkBox")},
		{"resCollapsedObj", new RenderObject("resCollapsed")},

		// Effects Objects 

		{"MagicObj", new RenderObject("Magic")},
		{"swordSlashEffectObj", new RenderObject("swordSlashEffect")},
		{"defaultItemObj", new RenderObject("defaultItem")},
		{"toolTipBgObj", new RenderObject("toolTipBg")}


	}
};

// Define sheets with an identifier, a sheet(Path, texture sizes(x,y), cell sizes(x,y) and cell count)
const std::map<std::string, SpriteSheet*> definedSheets
{
	{
		// Character Spritesheets

		{"female", new SpriteSheet("Assets/Sprites/Female 01-1.png", 96, 128, 32, 32, false)},
		{"mage", new SpriteSheet("Assets/Sprites/Male/Male 12-1.png",96, 128, 32, 32, false)},
		{"magSpr", new SpriteSheet("Assets/Sprites/MageSprite.png", 96, 128, 32, 32, false)},
		{"male", new SpriteSheet("Assets/Sprites/Male/Male 01-1.png",96, 128, 32, 32, false)},	
		{"nobleSprite", new SpriteSheet("Assets/Sprites/Male/Male 06-4.png", 96, 128, 32, 32, false)},
		{"rogSpr", new SpriteSheet("Assets/Sprites/ArcherSprite.png", 96, 128, 32, 32, false)},
		{"scholarSprite", new SpriteSheet("Assets/Sprites/Male/Male 08-1.png", 96, 128, 32, 32, false)},
		{"villagerSprite", new SpriteSheet("Assets/Sprites/Male/Male 10-2.png", 96, 128, 32, 32, false)},		
		{"warSpr", new SpriteSheet("Assets/Sprites/WarriorSprite.png", 96, 128, 32, 32, false)},
		{"daemonSpr", new SpriteSheet("Assets/Sprites/Daemon.png",385, 875, 75, 75, false)},

		// Portrait Spritesheets

		{"cleric", new SpriteSheet("Assets/Sprites/Portraits/Cleric.png",177, 243, 177, 243, false)},
		{"malePortrait", new SpriteSheet("Assets/Portrait.png",	357, 364, 357, 364, false)},
		{"merchantPortrait", new SpriteSheet("Assets/Sprites/Portraits/MerchantPortrait.png",210, 330, 210, 330, false)},
		{"playerPortrait", new SpriteSheet("Assets/Sprites/Portraits/PlayerPortrait.png",210, 330, 210, 330, false)},		
		{"rogue", new SpriteSheet("Assets/Sprites/Portraits/Rogue.png",177, 243, 177, 243, false)},
		{"warrior", new SpriteSheet("Assets/Sprites/Portraits/Warrior.png",177, 243, 177, 243,false)},
		{"wizard", new SpriteSheet("Assets/Sprites/Portraits/Wizard.png",177, 243, 177, 243, false)},

		// Item Spritesheets

		{"armour", new SpriteSheet("Assets/Sprites/armour.png",76, 72, 76, 72, false)},
		{"potion", new SpriteSheet("Assets/Sprites/potion.png",48, 48, 48, 48, false)},
		{"sword", new SpriteSheet("Assets/Sprites/sword-art.png",160, 256, 32, 32, false)},
		

		// Background Spritesheets

		{"characterFrame", new SpriteSheet("Assets/Backgrounds/CharacterFrame.png",228, 624, 228, 624, false)},
		{"fightSceneForest", new SpriteSheet("Assets/ForestFight.png",700, 400, 700, 400, false)},
		{"forestBG", new SpriteSheet("Assets/forestbackground.png",1280, 720, 1280, 720, false)},
		{"itemFrame", new SpriteSheet("Assets/Backgrounds/ItemFrame.png",85, 105, 85, 105, false)},
		{"mainMenuBG", new SpriteSheet("Assets/Backgrounds/MainMenuBG_720.png",1280, 720, 1280, 720, false)},
		{"OptionsBackground", new SpriteSheet("Assets/Sprites/Buttons/OptionsBackground.png",	240, 32, 240, 32, false)},
		{"overworld", new SpriteSheet("Assets/Backgrounds/background.png", 2048, 1536, 2048, 1536, true)},
		{"scrollBg", new SpriteSheet("Assets/Backgrounds/ResizedScroll.png", 1280, 720, 1280, 720, false)},
		{"shopBg", new SpriteSheet("Assets/Backgrounds/ShopBg.png",1280, 720, 1280, 720, false)},		
		{"tile", new SpriteSheet("Assets/grass-tile.png", 32, 32, 32, 32, false)},		
		{"stone-tile", new SpriteSheet("Assets/stone-tile.png", 32, 32, 32, 32, false)},
		{"tree", new SpriteSheet("Assets/Sprites/baum.png", 128,128,128,128,false)},
		
		// Button Spritesheets		
		
		{"ApplyBtn", new SpriteSheet("Assets/Sprites/Buttons/ApplyBtn.png",	128, 64, 128, 64, false)},
		{"armyViewerButton", new SpriteSheet("Assets/Sprites/Buttons/Army_viewer_btn1.png", 200, 34, 200, 34, false)},
		{"backBtn", new SpriteSheet("Assets/Sprites/Buttons/BackButtonNoBg.png", 81, 97, 81, 97, false)},
		{"backTxtBtn", new SpriteSheet("Assets/Sprites/Buttons/Back.png", 71, 36, 71, 36, false)},
		{"closeBtn", new SpriteSheet("Assets/Sprites/Buttons/CloseBtn2.png",32, 32, 32, 32, false)},
		{"exitButton", new SpriteSheet("Assets/Sprites/Buttons/exitButton.png", 200, 55, 200, 55, false)},
		{"inventoryButton", new SpriteSheet("Assets/Sprites/Buttons/inventoryBtn1.png", 200, 34, 200, 34, false)},
		{"menuButton", new SpriteSheet("Assets/Sprites/Buttons/MenuBtn1.png", 200, 34, 200, 34, false)},
		{"quitBtn", new SpriteSheet("Assets/Sprites/Buttons/QuitBtn.png",128, 64, 128, 64, false)},
		{"settingsBtn", new SpriteSheet("Assets/Sprites/Buttons/SettingsBtn.png",	128, 64, 128, 64, false)},
		{"startBtn", new SpriteSheet("Assets/Sprites/Buttons/StartBtn-02.png",128, 64, 128, 64, false)},
		{"yesTxtBtn", new SpriteSheet("Assets/Sprites/Buttons/Yes.png", 54, 36, 54, 36, false)},
		{"defaultItem", new SpriteSheet("Assets/Sprites/helmet.png", 32, 32, 32, 32, false)},
		{"settingsBg", new SpriteSheet("Assets/Backgrounds/Blank_Map_1280x720_Blurred.png", 1280, 720, 1280, 720, false)},
		{"toolTipBg", new SpriteSheet("Assets/Backgrounds/TooltipBackground.png", 48, 48, 48, 48, false)},

		// Node Spritesheets

		{"battleNode", new SpriteSheet("Assets/Sprites/BattleNode.png", 32, 32, 32, 32, false)},
		{"bossNode", new SpriteSheet("Assets/Sprites/BossNode.png", 32, 32, 32, 32, false)},
		{"shopNode", new SpriteSheet("Assets/Sprites/ShopNode.png", 32,32, 32, 32, false)},
		{"startNode", new SpriteSheet("Assets/Sprites/StartNode.png", 32, 32, 32, 32, false)},

		// Card Spritesheets

		{"card", new SpriteSheet("Assets/Sprites/Card/CardTemplateNew.png",230, 322, 230, 322, false)},
		{"SlashCard", new SpriteSheet("Assets/Sprites/SlashCard.png", 600, 951, 600, 951,false)},

		// More Traditional UI Spritesheets

		{"barBg", new SpriteSheet("Assets/Sprites/Bar_Bg.png",	176, 32, 176, 32, false)},
		{"barFill", new SpriteSheet("Assets/Sprites/Bar_fill.png",	176, 32, 176, 32, false)},		
		{"checkBox", new SpriteSheet("Assets/Sprites/Buttons/CheckBox.png",	128, 64, 64, 64, false)},		
		{"resCollapsed", new SpriteSheet("Assets/Sprites/Buttons/dropDown-01.png",	240, 32, 240, 32, false)},
		
		// Effects Spritesheets

		{"Magic", new SpriteSheet("Assets/Sprites/Effects/MagicEffect.png", 9200, 300, 400, 300,true)},
		{"swordSlashEffect", new SpriteSheet("Assets/Sprites/Effects/SwordSlash.png", 3248, 190, 406, 190,true)},
						
	}
};

const std::map<std::string, std::vector<Animation>> definedAnimations
{
	{
		// Unit Animations

		{"mage", {// a defined vector of animations, make sure the name matches the sheet
		Animation("LookUp", {std::make_pair(0,0)}),
		Animation("LookLeft", {std::make_pair(0,1)}),
		Animation("LookRight", {std::make_pair(0,2)}),
		Animation("LookDown", {std::make_pair(0,3)}),

		Animation("WalkUp", {std::make_pair(0,0), std::make_pair(1,0),std::make_pair(2,0)}),
		Animation("WalkLeft", {std::make_pair(0,1), std::make_pair(1,1), std::make_pair(2,1)}),
		Animation("WalkRight", {std::make_pair(0,2), std::make_pair(1,2), std::make_pair(2,2)}),
		Animation("WalkDown", {std::make_pair(0,3), std::make_pair(1,3), std::make_pair(2,3)}),


		}},

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

		{"male", {// a defined vector of animations, make sure the name matches the sheet
		Animation("LookUp", {std::make_pair(0,0)}),
		Animation("LookLeft", {std::make_pair(0,1)}),
		Animation("LookRight", {std::make_pair(0,2)}),
		Animation("LookDown", {std::make_pair(0,3)}),

		Animation("WalkUp", {std::make_pair(0,0), std::make_pair(1,0),std::make_pair(2,0)}),
		Animation("WalkLeft", {std::make_pair(0,1), std::make_pair(1,1), std::make_pair(2,1)}),
		Animation("WalkRight", {std::make_pair(0,2), std::make_pair(1,2), std::make_pair(2,2)}),
		Animation("WalkDown", {std::make_pair(0,3), std::make_pair(1,3), std::make_pair(2,3)}),


		}},

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

	// UI Animations

	{"checkBox", {Animation("Checked", {std::make_pair(1,0)})}},
	{"startBtn", {Animation("Hover", {std::make_pair(1,0)})}},

	// Background Animations

	{"tile",
		{
			Animation("Grass", {std::make_pair(0,0)})
		}
	},

	// Effects Animations

	{"Magic", {Animation("default", {std::make_pair(0,0), std::make_pair(1,0),std::make_pair(2,0),std::make_pair(3,0),std::make_pair(4,0),std::make_pair(5,0),std::make_pair(6,0)})}},
	{"swordSlashEffect", {Animation("default", {std::make_pair(0,0), std::make_pair(1,0),std::make_pair(2,0),std::make_pair(3,0),std::make_pair(4,0),std::make_pair(5,0),std::make_pair(6,0)})}},

	{"daemonSpr", {Animation("default", {std::make_pair(4,0)})}},
		
	}
};

const std::map<std::string, DefinedCard> definedCards
{
	{"magicCard",{25, 5, 0, 5, 0, "Magic", "Magically assail the enemy for 5 damage, costs 5 intelligence", "malePortrait" ,"MagicObj", 1.0}},
	{"slashCard",{1.5, 5, 5, 0, 0, "Slash", "Slash the enemy for 10 damage, costs 10 strength", "SlashCard" ,"swordSlashEffectObj", 0.5}},	
};





		
	