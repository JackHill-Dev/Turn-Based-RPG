#pragma once
#include <vector>
#include <string>
#include <SDL.h>
#include "Scene.h"

class GameManager;

class SceneManager
{
private:
	std::vector<Scene*> mScenes;
	Scene* mCurrentScene;
public:
	bool Init();
	void Update(double dTime, Act act);
	void Draw(SDL_Surface* surf);
	void AddScene(Scene* scene);
	void SetScene(int index);
	void NextScene(int index);
	void Select(int x, int y, SceneManager* sceneMgr, GameManager* gameMgr);
};

