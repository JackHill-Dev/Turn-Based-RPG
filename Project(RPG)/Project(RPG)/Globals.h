#pragma once
#include <random>
#include <iostream>
#include <memory>
#include <functional>

typedef void (*fnc)(void); // function pointer type
const int layerNum = 4;

enum Layer
{
	Background = 0,
	Map = 1,
	Game = 2,
	UI = 3,
	Items = 4
};

enum class Act 
{ 
	Blank, 
	Jump, 
	Click,
	RClick,
	MouseUp,
	MouseUpdate
};

enum Scenes
{
	MainMenu = 0,
	Overworld = 1,
	Combat = 2,
	Shops = 3,
	Party = 4,
	SettingsPage = 5,
	NoSceneYet = 10 
};

struct Settings
{
	bool bIsFullScreen = false;
	int mMasterVolume;
	int w, h;
};




