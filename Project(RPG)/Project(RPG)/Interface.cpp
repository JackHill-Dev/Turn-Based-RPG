#include "Interface.h"


Interface::Interface(bool* brunning, std::map<std::string, RenderObject*>* objP, int* currentScene) : objects(objP), currentScene(currentScene), running(brunning)
{


}

RenderObject* Interface::RequestObject(std::string name)
{

	return (*objects)[name]->Clone(); // Returns a clone of the object, a "deep" pointer copy
}

void Interface::PlayMusic(Mix_Music* pMusic, int loops) // overload for testing until the database and import manager classes are created
{
	Mix_VolumeMusic(10);
	Mix_PlayMusic(pMusic, loops);
}
void Interface::PlaySFX(Mix_Chunk* pSfx, int loops, int channel)
{
	Mix_PlayChannel(channel, pSfx, loops);
}


void Interface::StopMusic(Mix_Music& mus)
{
	if (Mix_PlayingMusic() != 0)
	{
		Mix_PauseMusic();
	}
}