#pragma once
#include <random>
#include <iostream>
#include <memory>
#include <functional>
#include <chrono>
#include <time.h>

const int layerNum = 5;

enum Layer
{
	Background = 0,
	Map = 1,
	Game = 2,
	UI = 3,
	Effects = 4
};

enum Act
{ 
	Blank = 0,
	Click = 1,
	RClick = 2,
	MouseUp = 3,
	MouseUpdate = 4,
};

enum Scenes
{
	MainMenu = 0,
	NoughtsAndCrosses = 1,
	NoSceneYet = 2, 
};

