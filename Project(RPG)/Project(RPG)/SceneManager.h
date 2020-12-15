#pragma once
#include <vector>
#include <string>
#include <SDL.h>
#include "Scene.h"
#include "ManagerStruct.h"

class GameManager;

class SceneManager
{
private:
	std::vector<Scene*> mScenes;
	Scene* mCurrentScene;
	SDL_Renderer* mRenderer;
public:
	bool Init(SDL_Renderer* renderer);
	void Update(double dTime, Act act);
	void Draw(SDL_Surface* surf);
	void AddScene(Scene* scene);
	void SetScene(int index);
	void NextScene(int index);
	void Select(int x, int y, Managers* mgrs);
};

