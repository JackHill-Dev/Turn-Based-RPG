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
    mMusic.emplace(std::make_pair(musName, music));
}

void Database::pushToMap(Mix_Chunk* sfx, std::string sfxName)
{
    mSfx.emplace(std::make_pair(sfxName, sfx));
}

void Database::pushToMap(SpriteSheet* sprite, std::string sprName)
{
    mSpriteSheets.emplace(std::make_pair(sprName,sprite));
}

// Not sure if required anymore. - EH
SpriteSheet* Database::GetSpriteSheet(std::string sheet) const
{
    return nullptr;
}
