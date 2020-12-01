#pragma once

#include <map>
#include <string>
#include <SDL_audio.h>
#include <SDL_mixer.h>

#include "SpriteSheet.h"

class Database
{

private:

	std::map<std::string, Mix_Music*> mMusic;
	std::map<std::string, Mix_Chunk*> mSfx;
	std::map<std::string, SpriteSheet*> mSpriteSheets;
	//std::vector<std::pair<std::string, Animation>> mAnims;


public:

	Mix_Music* GetMusic(std::string filePath) const;
	Mix_Chunk* GetSfx(std::string filePath) const;
	void pushToMap(Mix_Music* mus, std::string musName);
	void pushToMap(Mix_Chunk* sfx, std::string sfxName);
	void pushToMap(SpriteSheet* sprite, std::string sprName);
	SpriteSheet* GetSpriteSheet(std::string sheet) const;
	//Animation* GetAnims(std::string anim) const;

};

