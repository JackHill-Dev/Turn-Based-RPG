#include "SceneManager.h"

bool SceneManager::Init()
{
	return true;
}

void SceneManager::Update(double dTime)
{
	mCurrentScene->Update(dTime);
}

void SceneManager::Draw(SDL_Surface* surf)
{
	mCurrentScene->Draw(surf);
}