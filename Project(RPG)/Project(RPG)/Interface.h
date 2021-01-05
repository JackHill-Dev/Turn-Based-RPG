#pragma once
#include "Globals.h"
#include "RenderObject.h"
#include <SDL_mixer.h>
#include "Character.h"
class Interface
{
private:
	bool* running;
	int* currentScene;
	std::map<std::string, RenderObject*>* objects;
public:
	RenderObject* RequestObject(std::string name);
	Interface(bool* brunning,std::map<std::string, RenderObject*>* objP, int* currentScene);
	void Quit() { *running = false;};
	void PlayMusic(Mix_Music* pMusic, int loops);
	void PlaySFX(Mix_Chunk* pSfx, int loops, int channel);
	void StopMusic(Mix_Music& mus);
	void LoadScene(int index) { *currentScene = index; };
};

