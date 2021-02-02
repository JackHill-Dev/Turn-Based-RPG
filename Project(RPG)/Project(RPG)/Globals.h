#pragma once
#include <random>
#include <iostream>
#include <memory>
#include <functional>

typedef void (*fnc)(void); // function pointer type
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
	ClassPicker = 6,
	InventoryScreen = 7,
	NoSceneYet = 10 
};

struct Settings
{
	bool bIsFullScreen = false;
	int mMasterVolume;
	int w, h;
};



struct DefinedCard
{
public:
	DefinedCard(int range, int damage, int intelligenceCost, int staminaCost, int agilityCost, std::string name, std::string description, std::string picture,std::string animation) : range(range), damage(damage), intelligenceCost(intelligenceCost), staminaCost(staminaCost), agilityCost(agilityCost), name(name), description(description), picture(picture), animation(animation) {};

	int range, damage, intelligenceCost, staminaCost, agilityCost;
	std::string name, description, picture, animation;
};
