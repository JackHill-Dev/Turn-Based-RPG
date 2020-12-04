#pragma once
#include <SDL.h>
#include "SceneManager.h"
#include "AudioManager.h"
#include "ImportManager.h"
#include "Database.h"
#include "InputManager.h"
#include "Globals.h"
#include "Actions.h"
#include "MainMenuClass.h"
class GameManager
{
private:
	bool bRunning;
	SDL_Window* mWnd;
	SDL_Renderer* mRnd;
	SceneManager* mScManager;
	AudioManager* mAudioMgr;
	ImportManager* mImportMgr;
	InputManager* mInputMgr;
	Database* mDb;
	GameManager* sInstance;
public:
	bool Init();
	bool Running();
	void Run();
	Act Poll(SDL_Keycode kCode);
	void Quit();
	void Select(int x, int y);
	InputManager* GetInputMgr();
private:
	bool CreateWindow();
	void SetupManagers();


};

