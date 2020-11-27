#include "ImportManager.h"


// How are we grabbing sprite metadata from sprite files? Will they all be same dimensions? - EH
// Do I need to use IMG_INIT here to support the given file types and load the files? Tom could advise perhaps? - EH
/// <summary>
/// Load textures from all files in a given directory.Iterate through and store every file within a given directory into a map.
/// Need to convert to string then c_str as file.path() contains a string that requires extraction 
/// -EH	
/// </summary>
void ImportManager::LoadTextures()
{
	SDL_Surface* sprite;
	std::string sprName;

	for (const auto& file : fs::directory_iterator(mSpriteDir))
	{
		std::cout << "File path: " << file.path() << std::endl;
		sprite = IMG_Load(file.path().string().c_str());
		sprName = file.path().filename().string();
		pDB->pushToMap(new SpriteSheet(sprite, 16, 16), sprName);
	}
}

/// <summary>
/// Load music. We are using the .mp3 format. Iterate through and store every file within a given directory into a map.
/// Need to convert to string then c_str as file.path() contains a string that requires extraction 
/// -EH	
/// </summary>
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

/// <summary>
///	Load sound effects. Must be in .WAV format. Iterate through and store every file within a given directory into a map.
/// Need to convert to string then c_str as file.path() contains a string that requires extraction 
/// -EH	
/// </summary>
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

/// <summary>
/// Should be the same as the rest. Shall be implemented when the animation class has been made. - EH
/// </summary>
void ImportManager::LoadAnimations()
{

}

// Call the other load methods. Check when they're complete.
// Stop calling.
// #TODO Should Load be called before the while loop in GameManager::Run?
/// <summary>
///	Public method that calls all private load methods. Prevents client access to files within the project. 	
/// </summary>
void ImportManager::Load()
{
	LoadMusic();
	LoadSfx();
	LoadTextures();
	//LoadAnimations();
}
