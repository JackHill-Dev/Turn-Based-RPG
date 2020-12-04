#pragma once
#include <map>
#include <SDL.h>
#include "Globals.h"
#include "Actions.h"
class InputManager
{
private:
	
	std::map<SDL_Keycode, Act> keycodestoActs;
public:
	Act Call(SDL_Keycode key);
	bool CreateKeyBind(SDL_Keycode key, Act func);
	bool ClearKeyBind(SDL_Keycode key);
};