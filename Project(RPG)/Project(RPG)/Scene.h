#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include "RenderObject.h"
#include <SDL.h>
#include "Globals.h"

class Scene
{
private:
	std::string name;
	std::vector<std::vector<RenderObject*>> mLayers;

public:
	Scene();
	virtual void Update(double dTime, Act act);
	void Draw(SDL_Surface* surf);
	void Select(int x, int y);
	void AddObject(RenderObject* obj, Layer layerNum);
};

