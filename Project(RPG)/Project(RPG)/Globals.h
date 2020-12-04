#pragma once
#include <random>
#include <iostream>
#include <memory>
#include <functional>

typedef void (*fnc)(void); // function pointer type

enum Layer
{
	UI = 0,
};

static const Uint32 layerNum = 1;