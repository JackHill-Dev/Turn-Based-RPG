#pragma once
#include <SDL.h>
#include "SceneManager.h"
class GameManager
{
private:
	SDL_Window* wnd;
	SDL_Renderer* rnd;
	SceneManager scManager;
public:
	bool Init();
	bool Running();
	void Run();

private:
	bool CreateWindow();

};

