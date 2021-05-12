#pragma once
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
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

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

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

	std::vector<Scene*> scenes;
	Scene* currentScene;

	Interface mInterface{&bRunning, &objects, &mCScene, &mPlayer};

	SDL_Texture* LoadTexture(std::string path); //Moved it here for now
	void LoadScene();
	bool SetUp();
	bool Create_Window();
	
public:

	GameManager() {}
	~GameManager();
	
	bool Init();
	void Run(bool isHost, SOCKET usedSocket); // if true, the user is a host
	void Quit();	

};


