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
};

enum class Act 
{ 
	Blank, 
	Jump, 
	Click,
	RClick,
	MouseUpdate
};

enum Scenes
{
	MainMenu = 0,
	Overworld = 1,
	Combat = 2,
	Shopi = 3,
	Party = 4,
	NoSceneYet = 5,
};



