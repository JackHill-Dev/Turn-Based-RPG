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
	Player player;
	Inventory inv;
	Sword longSword("Long sword", 50);
	Sword sword("short sword", 30);

	inv.AddItem(&longSword);
	player.SetInventory(inv);

	player.GetInventory()->AddItem(&sword);
	player.GetInventory()->RemoveItem(&longSword);

	player.SetGold(100);
	player.SellItem(&sword);

	GameManager manager;
	manager.Init();

	manager.Run();
	return 0;
}

