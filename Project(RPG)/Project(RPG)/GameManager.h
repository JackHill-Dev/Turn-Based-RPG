#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <fstream>;
#include <istream>
#include "Globals.h"
#include "Scene.h"
#include "MainMenuScene.h"
#include "NoughtsAndCrossesScene.h"
#include "Interface.h"
#include "Player.h"
#include "json.hpp"

class GameManager
{

private:

	MainMenuScene* mMainMenuSceneInstance;
	NoughtsAndCrossesScene* mNoughtsAndCrossesSceneInstance;

	bool bRunning= true;
	Scenes mCScene = Scenes::MainMenu;
	SDL_Window* mWnd;
	SDL_Renderer* mRnd;
	SDL_Surface* mSurface;

	Player mPlayer;
	std::map<std::string, RenderObject*> objects; // This is where the RenderObject types are stored 
	std::map<std::string, SpriteSheet*> sheets; // This is where the spritesheets are stored

	std::map<std::string, Item*> mItems;
	std::vector<Scene*> scenes;
	Scene* currentScene;

	Interface mInterface{&bRunning, &objects, &mCScene, &mPlayer};

	SDL_Texture* LoadTexture(std::string path); //Moved it here for now
	void LoadScene();
	bool SetUp();
	bool CreateWindow();
	
public:

	GameManager() {}
	~GameManager();
	
	bool Init();
	void Run();
	void Quit();	

};


