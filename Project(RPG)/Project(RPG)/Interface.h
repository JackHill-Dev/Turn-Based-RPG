#pragma once
#include "Globals.h"
#include "RenderObject.h"
#include <SDL_mixer.h>
#include "Character.h"
#include "Player.h"
class Interface
{
private:

	bool* running;											// A pointer to the boolean that says whether its running or not, quit sets this to false
	int* currentScene;
	std::vector<Character*>* currentEnemies;				// A pointer to the currentsceneIndex
	int prevScene;
	std::map<std::string, RenderObject*>* objects;			// A pointer to the renderobjects
	
public:
	Player* pPlayer;
	RenderObject* RequestObject(std::string name);			// Requests a renderobject and returns a clone of the instance to the scene
	Interface(bool* brunning,std::map<std::string, RenderObject*>* objP, int* currentScene, std::vector<Character*>* currentEnemies, std::vector<Character*>* player); //This is the constructor, we pass in the pointers to the various variables which sets them
	void Quit() { *running = false;};						// Sets bRunning to false which closes the loop
	void PlayMusic(Mix_Music* pMusic, int loops);			//Jacks audio manager has been merged into this, these functions will play the music and setting the loop count to 0 will loop indefinitely
	void PlaySFX(Mix_Chunk* pSfx, int loops, int channel);  //Similar to PlayMusic, takes a pointer to the music file to play as well as how many loops, 0 playing indefinitely
	void StopMusic(Mix_Music& mus);							//This functions will halt all music, even the indefinite looping ones
	void LoadScene(int index) { *currentScene = index; };	//Loads scene via its indexed location in the vector scenes 0 being the mainMenu, 1 being combat etc
	void LoadCombatScene(std::vector<Character*> enemies) { *currentEnemies = enemies; *currentScene = 1; }
	Player* GetPlayer() { return pPlayer; }
};

