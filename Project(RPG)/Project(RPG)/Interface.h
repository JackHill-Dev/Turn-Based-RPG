#pragma once
#include "Globals.h"
#include "RenderObject.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include "Character.h"
#include "Player.h"
class Interface
{
private:
	bool* running;											// A pointer to the boolean that says whether its running or not, quit sets this to false
	Scenes* currentScene;										// A pointer to the currentsceneIndex
	Scenes prevScene;
	std::vector<Character*>* currentEnemies;				
	std::map<std::string, RenderObject*>* objects;			// A pointer to the renderobjects
	SDL_Window* mWnd = nullptr;
	Settings* pSettings;
public:
	const int fadeTime = 750; // Represents 750 ms (3/4 second) - EH
	Player* pPlayer;
	RenderObject* RequestObject(std::string name);			// Requests a renderobject and returns a clone of the instance to the scene
	Settings& GetSettings() { return *pSettings; }
	Interface(bool* brunning,std::map<std::string, RenderObject*>* objP, Scenes* currentScene, std::vector<Character*>* currentEnemies, Player* player, Settings* settings); //This is the constructor, we pass in the pointers to the various variables which sets them
	void Quit() { *running = false;};						// Sets bRunning to false which closes the loop
	void PlayMusic(Mix_Music* pMusic, int loops);			//Jacks audio manager has been merged into this, these functions will play the music and setting the loop count to -1 will loop indefinitely
	void FadeInMusic(Mix_Music* pMusic, int loops, int ms); // Fades in the music, loops it like play music but has a delay in ms - EH
	void FadeOutMusic(int ms); // ONLY USE TO SWAP MUSIC INSIDE A SCENE. This seems to halt execution until fade complete. Fades ALL music. Music stops playing when fade out is completed. Time in ms as before. - EH
	void PlaySFX(Mix_Chunk* pSfx, int loops, int channel);  //Similar to PlayMusic, takes a pointer to the music file to play as well as how many loops, -1 playing indefinitely
	void SetMasterVolume(int channel, int musVolume, int sfxVolume);
	void StopMusic();							//This functions will halt all music, even the indefinite looping ones
	void LoadScene(Scenes index);	//Loads scene via its indexed location in the vector scenes 0 being the mainMenu, 1 being combat etc
	Scenes GetPreviousScene() { return prevScene; } // This is mainly to enable logic for music transitions - EH
	void LoadCombatScene(std::vector<Character*> enemies) { *currentEnemies = enemies; prevScene = *currentScene; *currentScene = Scenes::Combat; }

	void LoadPreviousScene();
	void StoreWindow(SDL_Window* wnd) { mWnd = wnd; }
	void SetWindowSize();
	void SetFullScreen() { if(pSettings->bIsFullScreen) SDL_SetWindowFullscreen(mWnd, SDL_WINDOW_FULLSCREEN); }
	Player* GetPlayer() { return pPlayer; }
};

