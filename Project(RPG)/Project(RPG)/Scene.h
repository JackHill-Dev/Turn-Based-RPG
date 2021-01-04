#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <SDL.h>
#include "RenderObject.h"
#include "Globals.h"
#include "GameObjects.h"
#include "AudioManager.h"
class GameManager;

class Scene
{
private:
	
	std::string name;
	
	SDL_Surface* mSurface = nullptr;
protected:
	std::vector<std::vector<RenderObject*>> mLayers;

	virtual void Update(double dTime, Act act, std::pair<int, int> mousePos);
	
	GameManager* mgr;
public:
	Scene(GameManager* objmg);

	void SceneUpdate(double dTime, Act act, std::pair<int, int> mousePos);

	
	void Draw(SDL_Renderer* rnd);
	
	void Clear(SDL_Renderer* rnd);
	RenderObject* AddObject(std::string obj, int x, int y, Layer layerNum);
};

