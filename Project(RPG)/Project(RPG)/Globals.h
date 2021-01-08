#pragma once
#include <random>
#include <iostream>
#include <memory>
#include <functional>

typedef void (*fnc)(void); // function pointer type

enum Layer
{
	UI = 3, Game = 2, Map = 1, Background = 0,
};

const int layerNum = 4;

enum class Act { Blank, Jump, Why, Click, RClick, MouseUpdate };

enum Scenes
{
	MainMenu = 0,
	//Overworld = 1,
	Combat = 1,
	Shopi = 2,
	Party = 3
};