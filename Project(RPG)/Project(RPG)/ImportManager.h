#pragma once

#include <filesystem>
#include <iostream>
#include <SDL_image.h>
#include "Database.h"

// Allows us to make use of c++17 library which handles processing filesystems. 
// Namely iterating through directories and performing operations on files contained within.
namespace fs = std::filesystem;

class ImportManager
{

private:

	Database* pDB;

	std::string mSpriteDir = "Assets/Sprites/Male/";
	std::string mMusicDir = "Assets/";
	std::string mSfxDir = "Assets/";
	std::string mAnimationDir;
	
	void LoadTextures();
	void LoadMusic();
	void LoadSfx();
	void LoadAnimations();

public:
	ImportManager(Database* db);
	void Load();
	SDL_Surface* LoadTexture(std::string path);
};
