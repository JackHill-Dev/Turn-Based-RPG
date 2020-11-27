#include "Database.h"

Mix_Music* Database::GetMusic(std::string filePath) const
{
    return Mix_LoadMUS(filePath.c_str());
}

Mix_Chunk* Database::GetSfx(std::string filePath) const
{
    return Mix_LoadWAV(filePath.c_str());
}

void Database::pushToMap(Mix_Music* music, std::string musName)
{
    mMusic.emplace(std::make_pair(music, musName));
}

void Database::pushToMap(Mix_Chunk* sfx, std::string sfxName)
{
    mSfx.emplace(std::make_pair(sfx, sfxName));
}

SpriteSheet* Database::GetSpriteSheet(std::string sheet) const
{
    return nullptr;
}
