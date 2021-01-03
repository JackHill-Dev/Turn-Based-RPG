#pragma once
#include <SDL.h>
#include "SceneManager.h"
#include "AudioManager.h"
#include "ImportManager.h"
#include "Database.h"
#include "InputManager.h"
#include "Globals.h"
#include "Actions.h"
#include "MainMenuScene.h"
#include "ObjectManager.h"
#include "ManagerStruct.h"

class GameManager
{
private:
	bool bRunning;
	SDL_Window* mWnd;
	SDL_Renderer* mRnd;
	SceneManager* mScManager;
	SDL_Surface* mSurface;
	AudioManager* mAudioMgr;
	ImportManager* mImportMgr;
	InputManager* mInputMgr;
	ObjectManager* mObjMgr;
	Database* mDb;
	//GameManager* sInstance;

	Managers mMgrs;
	TTF_Font* font;
public:
	bool Init();
	bool Running();
	void Run();
	Act Poll(SDL_Keycode kCode);
	void Quit();
	InputManager* GetInputMgr();
private:
	bool CreateWindow();
	void SetupManagers();
	void SetupManagersStruct();
	void InitManagers();

};


