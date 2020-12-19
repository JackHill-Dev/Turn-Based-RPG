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

void SceneManager::Update(double dTime, Act act, std::pair<int, int> mousePos)
{
	mCurrentScene->SceneUpdate(dTime, act, mousePos);
	
}

void SceneManager::Draw(SDL_Renderer* rnd)
{
	mCurrentScene->Draw(rnd);
}

void SceneManager::AddScene(Scene* scene)
{
	mScenes.push_back(scene);
}

void SceneManager::SetScene(int index)
{
	mCurrentScene->Clear(mRenderer);
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