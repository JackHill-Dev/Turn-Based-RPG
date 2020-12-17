#include "Globals.h"
#include <SDL.h>
#include <SDL_image.h>
#undef main
#include "GameManager.h"
#include <cassert>
#include "ini.h"
void Out()
{
	std::cout << "AHH";
}

bool to_bool(const std::string& s)
{
	if (s == "true")
	{
		return true;
	}
	else if (s == "false")
	{
		return false;
	}
	else
	{
		return false;
		assert("String passed was not true or false");
	}

}

int main()
{
	mINI::INIFile file("settings.ini");
	mINI::INIStructure ini;
	file.read(ini);

	int i = 0;
	bool fullScreen = true;

	i = stoi(  ini["Audio"]["volume"]);
	fullScreen = to_bool(ini["Display"]["fullscreen"]);

	ini["Audio"]["volume"] = "100";

	file.write(ini);

	GameManager manager;
	manager.Init();

	manager.Run();
	return 0;
}

