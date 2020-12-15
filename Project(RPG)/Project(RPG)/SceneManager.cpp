#include "SceneManager.h"

bool SceneManager::Init(SDL_Renderer* renderer)
{
	if (this == nullptr)
	{
		return false;
	}
	else
	{
		mRenderer = renderer;
	}

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

void SceneManager::NextScene(int index)
{
	mCurrentScene->Clear(mRenderer);
	mCurrentScene = mScenes[index];
}

void SceneManager::Select(int x, int y, Managers* mgrs)
{
	mCurrentScene->Select(x, y, mgrs);
}