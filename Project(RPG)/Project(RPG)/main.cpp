#include <SDL.h>
#include <SDL_image.h>
#undef main
#include "GameManager.h"

#include "Player.h"
#include "Inventory.h"
#include "Sword.h"

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

