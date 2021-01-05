#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include "Globals.h"
#include "Scene.h"
#include "Actions.h"
#include "MainMenuClass.h"
#include "OverworldMapScene.h"
#include "Character.h"
#include "Interface.h"

class GameManager
{
private:
	
	bool bRunning= true;
	int mCScene = 0;
	SDL_Window* mWnd;
	SDL_Renderer* mRnd;
	SDL_Surface* mSurface;
	std::map<std::string, RenderObject*> objects; // This is where the RenderObject types are stored 
	std::map<std::string, SpriteSheet*> sheets; // This is where the spritesheets are stored
	Interface mInterface{&bRunning, &objects,&mCScene };
	SDL_Texture* LoadTexture(std::string path); //Moved it here for now
	
public:
	bool Init();

	void Run();
	void Quit();
	void SetScene(int index);
	
	
private:
	
	
	bool SetUp();
	bool CreateWindow();
	std::vector<Scene*> scenes;
	Scene* currentScene;
};


