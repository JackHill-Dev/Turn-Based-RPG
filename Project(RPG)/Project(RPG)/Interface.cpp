#include "Interface.h"



Interface::Interface(bool* brunning, std::map<std::string, RenderObject*>* objP, int* currentScene, std::vector<Character*>* currentEnemies, Player* player) : objects(objP), currentScene(currentScene), running(brunning), currentEnemies(currentEnemies), pPlayer(player)
{

	//this is the constructor where we pass in pointers to the required objects of which we need to alter/retrieve data from
}

RenderObject* Interface::RequestObject(std::string name)
{

	return (*objects)[name]->Clone(); // Returns a clone of the object, a "deep" pointer copy
}

void Interface::PlayMusic(Mix_Music* pMusic, int loops) // overload for testing until the database and import manager classes are created
{
	Mix_VolumeMusic(10); // this is the volume at which the music is playing, 10 I believe is quite high, the volume range goes from 0-128 -JP
	Mix_PlayMusic(pMusic, loops);	//Will add and overrite current music with pointer to file, and determine how many times it will repeat
}
void Interface::PlaySFX(Mix_Chunk* pSfx, int loops, int channel)
{
	Mix_PlayChannel(channel, pSfx, loops); //This is where we can play sound effects, the different channels allow multiple sound effects to play at once
}


void Interface::StopMusic(Mix_Music& mus) // This stops the music playing regardless of loops remaining
{
	if (Mix_PlayingMusic() != 0)
	{
		Mix_PauseMusic();
	}
}

void Interface::LoadScene(Scenes scene)
{
	prevScene = *currentScene; 
	*currentScene = scene;
}

void Interface::LoadPreviousScene()
{
	*currentScene = prevScene; 
}
