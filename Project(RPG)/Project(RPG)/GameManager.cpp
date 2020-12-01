#include "GameManager.h"


bool GameManager::Init()
{
	mDb = new Database();
	SetupManagers();
	CreateWindow();
	Run();
	return true;
}

bool GameManager::Running()
{
	return true;
}

void GameManager::Run()
{
	SDL_Surface* screenSurface;
	while (Running())
	{
		screenSurface = SDL_GetWindowSurface(mWnd);
		mScManager->Draw(screenSurface);
		SDL_UpdateWindowSurface(mWnd);
		SDL_FreeSurface(screenSurface);
	}

	SDL_DestroyWindow(mWnd);
	SDL_Quit();
}

bool GameManager::CreateWindow()
{
	SDL_CreateWindowAndRenderer(500, 500, 0, &mWnd, &mRnd);
	SDL_ShowWindow(mWnd);
	return true;
}

void GameManager::SetupManagers()
{
	mAudioMgr = AudioManager::Instance();
	mImportMgr = new ImportManager(mDb);
	mScManager = new SceneManager();
}
