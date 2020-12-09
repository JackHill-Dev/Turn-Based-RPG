#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Animation.h"
#include "Globals.h"
#include <map>
class SpriteSheet
{
private:
	SDL_Surface* mTexture;
	const float mCellSize;
	const int mCellCount;
	std::map<std::string,Animation*> anims;
public:
	bool SetTexture(SDL_Surface* texture);
	const std::string mFilePath;
	SpriteSheet(std::string path, float nCellSize, int nCellCount);
	SDL_Surface* GetTexture();
	float GetCellSize();
	Animation* GetAnim(std::string name);
	void AddAnim(std::string name, Animation anim);
};