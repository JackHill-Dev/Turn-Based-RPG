#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <SDL.h>
#include "RenderObject.h"
#include "Globals.h"
#include "GameObjects.h"
#include "ObjectManager.h"
#include "AudioManager.h"

class Scene
{
private:
	
	std::string name;
	std::vector<std::vector<RenderObject*>> mLayers;
protected:
	ObjectManager* mgr;
	

public:
	Scene();
	virtual void Update(double dTime, Act act);
	void Draw(SDL_Surface* surf);
	void Select(int x, int y);
	void AddObject(std::string obj, int x, int y, Layer layerNum);
};

