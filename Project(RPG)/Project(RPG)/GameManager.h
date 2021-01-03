#pragma once
#include <SDL.h>

#include "Globals.h"
#include "Scene.h"
#include "Actions.h"
#include "MainMenuClass.h"
#include "Character.h"


class GameManager
{
private:
	
	bool bRunning= true;
	SDL_Window* mWnd;
	SDL_Renderer* mRnd;
	SDL_Surface* mSurface;
	AudioManager* mAudioMgr;
	std::map<std::string, RenderObject*> objects; // This is where the RenderObject types are stored 
	std::map<std::string, SpriteSheet*> sheets; // This is where the spritesheets are stored
	SDL_Texture* LoadTexture(std::string path); //Moved it here for now
	
public:
	bool Init();

	void Run();
	void Quit();
	void SetScene(int index);
	void LoadCombatScene(std::vector<Character*> player, std::vector<Character*> enemy);
	RenderObject* RequestObject(std::string name);
private:
	
	
	bool SetUp();
	bool CreateWindow();
	std::vector<Scene*> scenes;
	Scene* currentScene;
};


