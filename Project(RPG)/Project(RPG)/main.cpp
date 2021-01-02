#include <SDL.h>
#include <SDL_image.h>
#undef main
#include "GameManager.h"


void Out()
{
	std::cout << "AHH";
}
int main()
{

	GameManager manager;
	manager.Init();

	manager.Run();
	return 0;
}

