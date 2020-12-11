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

class SceneManager;
class GameManager;

class Scene
{
private:
	
	std::string name;
	std::vector<std::vector<RenderObject*>> mLayers;
	SDL_Surface* mSurface;
protected:
	ObjectManager* mgr;
public:
	Scene();

	virtual void Update(double dTime, Act act);
	void Draw(SDL_Surface* surf);
	void Select(int x, int y, SceneManager* sceneMgr, GameManager* gameMgr);
	void Clear();
	RenderObject* AddObject(std::string obj, int x, int y, Layer layerNum);
};

