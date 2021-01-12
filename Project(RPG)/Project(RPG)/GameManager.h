#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include "Globals.h"
#include "Scene.h"
#include "Actions.h"
#include "MainMenuScene.h"
#include "OverworldMapScene.h"
#include "Character.h"
#include "Interface.h"
#include "Player.h"
class GameManager
{
private:
	
	bool bRunning= true;
	int mCScene = 0;
	SDL_Window* mWnd;
	SDL_Renderer* mRnd;
	SDL_Surface* mSurface;
	Player mPlayer;
	std::map<std::string, RenderObject*> objects; // This is where the RenderObject types are stored 
	std::map<std::string, SpriteSheet*> sheets; // This is where the spritesheets are stored
	Interface mInterface{&bRunning, &objects, &mPlayer,&mCScene };
	SDL_Texture* LoadTexture(std::string path); //Moved it here for now
	
public:
	bool Init();

	void Run();
	void Quit();	
	
private:
	
	
	bool SetUp();
	bool CreateWindow();
	std::vector<Scene*> scenes;
	Scene* currentScene;
};


