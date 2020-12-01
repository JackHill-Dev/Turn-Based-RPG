#pragma once
#include <SDL.h>
#include "SceneManager.h"
#include "AudioManager.h"
#include "ImportManager.h"
#include "Database.h"
class GameManager
{
private:
	SDL_Window* mWnd;
	SDL_Renderer* mRnd;
	SceneManager* mScManager;
	AudioManager* mAudioMgr;
	ImportManager* mImportMgr;
	Database* mDb;
public:
	bool Init();
	bool Running();
	void Run();

private:
	bool CreateWindow();
	void SetupManagers();

};

