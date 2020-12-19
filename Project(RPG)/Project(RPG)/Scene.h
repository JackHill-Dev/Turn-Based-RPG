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
	SDL_Surface* mSurface = nullptr;
protected:
	ObjectManager* mgr;
	virtual void Update(double dTime, Act act, std::pair<int, int> mousePos);
public:
	Scene(ObjectManager* objmg);

	void SceneUpdate(double dTime, Act act, std::pair<int, int> mousePos);

	
	void Draw(SDL_Renderer* rnd);
	void Select(int x, int y, Managers* mgrs);
	void Clear(SDL_Renderer* rnd);
	RenderObject* AddObject(std::string obj, int x, int y, Layer layerNum);
};

