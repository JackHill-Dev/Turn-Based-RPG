#include "GameManager.h"


bool GameManager::Init()
{
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
		screenSurface = SDL_GetWindowSurface(wnd);
		scManager.Draw(screenSurface);
		SDL_UpdateWindowSurface(wnd);
		SDL_FreeSurface(screenSurface);
	}
	SDL_DestroyWindow(wnd);
	SDL_Quit();
}

bool GameManager::CreateWindow()
{
	SDL_CreateWindowAndRenderer(500, 500, 0, &wnd, &rnd);
	SDL_ShowWindow(wnd);
	return true;
}
