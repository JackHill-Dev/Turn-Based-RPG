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
		{"mageObj",new RenderObject("mage")},

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

		{"swordSlashEffectObj", new RenderObject("swordSlashEffect")},
		{"MagicObj", new RenderObject("Magic")},
		{"TreeObj", new RenderObject("tree")}


	}
};

// Define sheets with an identifier, a sheet(Path, texture sizes(x,y), cell sizes(x,y) and cell count)
const std::map<std::string, SpriteSheet*> definedSheets
{
	{	{"fightSceneForest", new SpriteSheet("Assets/ForestFight.png",700, 400, 700, 400, false)},
		{"male", new SpriteSheet("Assets/Sprites/Male/Male 01-1.png",96, 128, 32, 32, false)},
		{"startBtn", new SpriteSheet("Assets/Sprites/Buttons/StartBtn-02.png",128, 64, 128, 64, false)},
		{"quitBtn", new SpriteSheet("Assets/Sprites/Buttons/QuitBtn.png",128, 64, 128, 64, false)},
		{"closeBtn", new SpriteSheet("Assets/Sprites/Buttons/CloseBtn2.png",32, 32, 32, 32, false)},
		{"mainMenuBG", new SpriteSheet("Assets/Backgrounds/MainMenuBG_720.png",1280, 720, 1280, 720, false)},
		{"overworld", new SpriteSheet("Assets/Backgrounds/Blank_Map_1280x720.png", 1280, 720, 1280, 720, false)},
		{"battleNode", new SpriteSheet("Assets/Sprites/BattleNode.png", 32, 32, 32, 32, false)},
		{"bossNode", new SpriteSheet("Assets/Sprites/BossNode.png", 32, 32, 32, 32, false)},
		{"shopNode", new SpriteSheet("Assets/Sprites/ShopNode.png", 32,32, 32, 32, false)},
		{"startNode", new SpriteSheet("Assets/Sprites/StartNode.png", 32, 32, 32, 32, false)},
		{"playerPortrait", new SpriteSheet("Assets/Sprites/Portraits/PlayerPortrait.png",210, 330, 210, 330, false)},
		{"merchantPortrait", new SpriteSheet("Assets/Sprites/Portraits/MerchantPortrait.png",210, 330, 210, 330, false)},
		{"wizard", new SpriteSheet("Assets/Sprites/Portraits/Wizard.png",177, 243, 177, 243, false)},
		{"rogue", new SpriteSheet("Assets/Sprites/Portraits/Rogue.png",177, 243, 177, 243, false)},
		{"cleric", new SpriteSheet("Assets/Sprites/Portraits/Cleric.png",177, 243, 177, 243, false)},
		{"warrior", new SpriteSheet("Assets/Sprites/Portraits/Warrior.png",177, 243, 177, 243,false)},
		{"shopBg", new SpriteSheet("Assets/Backgrounds/ShopBg.png",1280, 720, 1280, 720, false)},
		{"itemFrame", new SpriteSheet("Assets/Backgrounds/ItemFrame.png",85, 105, 85, 105, false)},
		{"characterFrame", new SpriteSheet("Assets/Backgrounds/CharacterFrame.png",228, 624, 228, 624, false)},
		{"sword", new SpriteSheet("Assets/Sprites/sword-art.png",160, 256, 32, 32, false)},
		{"armour", new SpriteSheet("Assets/Sprites/armour.png",76, 72, 76, 72, false)},
		{"potion", new SpriteSheet("Assets/Sprites/potion.png",48, 48, 48, 48, false)},
		{"card", new SpriteSheet("Assets/Sprites/Card/CardTemplateNew.png",230, 322, 230, 322, false)},
		{"tile", new SpriteSheet("Assets/grass-tile.png", 32, 32, 32, 32, false)},
		{"forestBG", new SpriteSheet("Assets/forestbackground.png",1280, 720, 1280, 720, false)},
		{"malePortrait", new SpriteSheet("Assets/Portrait.png",	357, 364, 357, 364, false)},
		{"barBg", new SpriteSheet("Assets/Sprites/Bar_Bg.png",	176, 32, 176, 32, false)},
		{"barFill", new SpriteSheet("Assets/Sprites/Bar_fill.png",	176, 32, 176, 32, false)},
		{"armyViewerButton", new SpriteSheet("Assets/Sprites/Buttons/Army_viewer_btn1.png", 200, 34, 200, 34, false)},
		{"inventoryButton", new SpriteSheet("Assets/Sprites/Buttons/inventoryBtn1.png", 200, 34, 200, 34, false)},
		{"menuButton", new SpriteSheet("Assets/Sprites/Buttons/MenuBtn1.png", 200, 34, 200, 34, false)},
		{"exitButton", new SpriteSheet("Assets/Sprites/Buttons/exitButton.png", 200, 55, 200, 55, false)},
		{"settingsBtn", new SpriteSheet("Assets/Sprites/Buttons/SettingsBtn.png",	128, 64, 128, 64, false)},
		{"settingsOverlay", new SpriteSheet("Assets/Sprites/SettingsOverlay.png",	640, 480, 640, 480, false)},
		{"resCollapsed", new SpriteSheet("Assets/Sprites/Buttons/dropDown-01.png",	240, 32, 240, 32, false)},
		{"resUnCollapsed", new SpriteSheet("Assets/Sprites/Buttons/dropDown-02.png",	240, 96, 240, 96, false)},
		{"OptionsBackground", new SpriteSheet("Assets/Sprites/Buttons/OptionsBackground.png",	240, 32, 240, 32, false)},
		{"ApplyBtn", new SpriteSheet("Assets/Sprites/Buttons/ApplyBtn.png",	128, 64, 128, 64, false)},
		{"checkBox", new SpriteSheet("Assets/Sprites/Buttons/CheckBox.png",	128, 64, 64, 64, false)},
		{"mage", new SpriteSheet("Assets/Sprites/Male/Male 12-1.png",96, 128, 32, 32, false)},
		{"swordSlashEffect", new SpriteSheet("Assets/Sprites/Effects/SwordSlash.png", 3248, 190, 406, 190,true)},
		{"SlashCard", new SpriteSheet("Assets/Sprites/SlashCard.png", 600, 951, 600, 951,false)},
		{"Magic", new SpriteSheet("Assets/Sprites/Effects/MagicEffect.png", 9200, 300, 400, 300,true)},
		{"tree", new SpriteSheet("Assets/Sprites/baum.png", 128,128,128,128,false)},
		{"female", new SpriteSheet("Assets/Sprites/Female 01.1.png", 96, 128, 32, 32, 12)},
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
		},
		{"swordSlashEffect", {Animation("default", {std::make_pair(0,0), std::make_pair(1,0),std::make_pair(2,0),std::make_pair(3,0),std::make_pair(4,0),std::make_pair(5,0),std::make_pair(6,0)})}},
		{"Magic", {Animation("default", {std::make_pair(0,0), std::make_pair(1,0),std::make_pair(2,0),std::make_pair(3,0),std::make_pair(4,0),std::make_pair(5,0),std::make_pair(6,0)})}}
	}

	


};

const std::map<std::string, DefinedCard> definedCards
{
	{"slashCard",{1, 5, 0, 10, 0, "Slash", "Slash the enemy for 5 damage, costs 10 stamina", "SlashCard" ,"swordSlashEffectObj"}},
	{"magicCard",{5, 5, 0, 5, 0, "Magic", "Slash the enemy for 5 damage, costs 10 stamina", "malePortrait" ,"MagicObj"}}
};





		
	