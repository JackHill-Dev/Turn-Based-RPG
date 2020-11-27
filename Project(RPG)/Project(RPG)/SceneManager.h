#pragma once
#include "Scene.h"
#include <vector>
#include <string>
#include <SDL.h>
class SceneManager
{
private:
	std::vector<Scene> mScenes;
	Scene* mCurrentScene;
public:
	bool Init();
	void Update(double dTime);
	void Draw(SDL_Surface* surf);
};

