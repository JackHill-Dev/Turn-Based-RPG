#pragma once
#include <random>
#include <iostream>
#include <memory>
#include <functional>
#include <string>
#include <cassert>
typedef void (*fnc)(void); // function pointer type

enum Layer
{
	UI = 3, Game = 2, Map = 1, Background = 0,
};

const int layerNum = 4;

