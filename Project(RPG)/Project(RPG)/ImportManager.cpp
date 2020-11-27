#include "ImportManager.h"
#include <iostream>

void ImportManager::LoadTextures()
{
	
}

void ImportManager::LoadMusic()
{
	Mix_Music* music;
	std::string musicName;

	for (const auto& file : fs::directory_iterator(mMusicDir))
	{
		std::cout << "File path: " << file.path() << std::endl;
		music = Mix_LoadMUS(file.path().string().c_str());
		musicName = file.path().filename().string();
		pDB->pushToMap(music, musicName);
	}
}

void ImportManager::LoadSfx()
{
	Mix_Chunk* sfx;
	std::string sfxName;

	for (const auto& file : fs::directory_iterator(mSfxDir))
	{
		std::cout << "File path: " << file.path().c_str() << std::endl;
		sfx = Mix_LoadWAV(file.path().string().c_str());
		sfxName = file.path().filename().string();
		pDB->pushToMap(sfx, sfxName);
	}
}

void ImportManager::LoadAnimations()
{

}

void ImportManager::Load()
{
	LoadMusic();
	LoadSfx();
	// Call the other load methods. Check when they're complete.
	// Stop calling.
}
