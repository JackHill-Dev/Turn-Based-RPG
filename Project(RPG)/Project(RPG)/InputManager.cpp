#include "InputManager.h"
Act InputManager::Call(SDL_Keycode key)
{
	//SDL_Keycode scanToKey = SDL_SCANCODE_TO_KEYCODE(key);
	if (keycodestoActs.find(key) != keycodestoActs.end())
		return keycodestoActs[key];
	return Act::Blank;
}

bool InputManager::CreateKeyBind(SDL_Keycode key, Act func)
{
	SDL_Keycode scanToKey = SDL_SCANCODE_TO_KEYCODE(key);
	keycodestoActs[key] = func;
	return true;
}

bool InputManager::ClearKeyBind(SDL_Keycode key)
{
	keycodestoActs.erase(key);
	return true;
}

