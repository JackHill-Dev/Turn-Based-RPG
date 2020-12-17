#pragma once
#include "Globals.h"
#include "RenderObject.h"
#include <map>
#include "SpriteSheet.h"
#include "Animation.h"
#include "Button.h"
#include "StartButton.h"
#include "QuitButton.h"
#include "SettingsButton.h"
#include "CloseButton.h"
const std::map<std::string,RenderObject*> definedObjects
{
	{
		{"maleObj",new RenderObject("male")}, // a defined object
		{"mainMenuBGObj",new RenderObject("mainMenuBG")}, // a defined object
		{"StartBtnObj",new StartButton("startBtn")},
		{"QuitBtnObj",new QuitButton("quitBtn")},
		{"SettingsBtnObj",new SettingsButton("settingsBtn")},
		{"CloseBtnObj",new CloseButton("closeBtn")},
		{"settingsOverlayObj",new SettingsButton("settingsOverlay")}
	}
};

const std::map<std::string, SpriteSheet*> definedSheets
{
	{
		{"male", new SpriteSheet("Assets/Sprites/Male/Male 01-1.png",96, 128, 32, 32, 12)}, // a defined sheet
		{"startBtn", new SpriteSheet("Assets/Sprites/Buttons/StartBtn-02.png",128, 64, 128, 64, 1)},
		{"quitBtn", new SpriteSheet("Assets/Sprites/Buttons/QuitBtn.png",128, 64, 128, 64, 1)},
		{"settingsBtn", new SpriteSheet("Assets/Sprites/Buttons/SettingsBtn.png",128, 64, 128, 64, 1)},
		{"closeBtn", new SpriteSheet("Assets/Sprites/Buttons/CloseBtn.png",32, 32, 32, 32, 1)},
		{"settingsOverlay", new SpriteSheet("Assets/Sprites/SettingsOverlay.png",640, 480, 640, 480, 1)},
		{"mainMenuBG", new SpriteSheet("Assets/Backgrounds/MainMenuBG_720.png",1280, 720, 1280, 720, 1)}
	}
};

const std::map<std::string, std::vector<Animation>> definedAnimations
{
	{
		{"male", {Animation("WalkLeft", {std::make_pair(0,0),std::make_pair(1,0),std::make_pair(2,0)})}} // a defined vector of animations, make sure the name matches the sheet
	}
};