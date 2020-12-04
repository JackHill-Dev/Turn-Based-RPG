#include "SceneManager.h"

bool SceneManager::Init()
{
	return true;
}

void SceneManager::Update(double dTime, Act act)
{
	mCurrentScene->Update(dTime, act);
}

void SceneManager::Draw(SDL_Surface* surf)
{
	mCurrentScene->Draw(surf);
}

void SceneManager::AddScene(Scene* scene)
{
	mScenes.push_back(scene);
}

void SceneManager::SetScene(int index)
{
	mCurrentScene = mScenes[index];
}

void SceneManager::Select(int x, int y)
{
	mCurrentScene->Select(x, y);
}