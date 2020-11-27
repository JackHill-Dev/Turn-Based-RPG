#pragma once
#include "Database.h"
#include <filesystem>

namespace fs = std::filesystem;

class ImportManager
{

private:

	Database* pDB;

	std::string mSpriteDir;
	std::string mMusicDir = "D://OneDrive - Sheffield Hallam University//University Level 6//GamesProject//Project 2//GameMusic//Music";
	std::string mSfxDir = "D://OneDrive - Sheffield Hallam University//University Level 6//GamesProject//Project 2//GameMusic//SFX";
	std::string mAnimationDir;

	void LoadTextures();
	void LoadMusic();
	void LoadSfx();
	void LoadAnimations();

public:

	void Load();

};
