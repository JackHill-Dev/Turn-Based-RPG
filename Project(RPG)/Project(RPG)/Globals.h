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

enum class Act 
{ 
	Blank,
	Click,
	RClick,
	MouseUp,
	MouseUpdate
};

enum Scenes
{
	MainMenu = 0,
	NoughtsAndCrosses = 1,
	NoSceneYet = 2, 
};

