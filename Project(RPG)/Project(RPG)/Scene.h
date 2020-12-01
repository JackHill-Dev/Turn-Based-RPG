#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include "RenderObject.h"
#include <SDL.h>
class Scene
{
private:
	std::string name;
	std::vector<std::vector<RenderObject>> mLayers;
public:
	virtual void Update(double dTime);
	void Draw(SDL_Surface* surf);
};

