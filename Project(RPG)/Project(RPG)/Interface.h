#pragma once
#include "Globals.h"
#include "RenderObject.h"
#include <SDL_mixer.h>
#include "Character.h"
class Interface
{
private:
	bool* running;										// A pointer to the boolean that says whether its running or not, quit sets this to false
	int* currentScene;									// A pointer to the currentsceneIndex
	std::map<std::string, RenderObject*>* objects;		// A pointer to the renderobjects
public:
	RenderObject* RequestObject(std::string name);		// Requests a render object and returns a clone of the instance to the scene
	Interface(bool* brunning,std::map<std::string, RenderObject*>* objP, int* currentScene); //This is the constructor, we pass in the pointers to various variables which sets them
	void Quit() { *running = false;};					// Sets bRunning to false which closes the loop
	void PlayMusic(Mix_Music* pMusic, int loops);		// Jacks audio manager has been merged into this, these functions will play the music and setting the loop count to -1 will loop indefinitely
	void PlaySFX(Mix_Chunk* pSfx, int loops, int channel); // Similar to PlayMusic, takes a pointer to the music file to play as well as how many loops, -1 playing indefinitely
	void StopMusic(Mix_Music& mus);						// This function will halt all music, even the infinite looping ones
	void LoadScene(Scenes scene) { *currentScene = scene; }; // Loads scene via it's indexed location in the vector, this now uses an enum Scenes which you can find in Globals.h 
															 // This is mainly semantic so it's easier to track the scene we're loading and still functions like an int index
};

