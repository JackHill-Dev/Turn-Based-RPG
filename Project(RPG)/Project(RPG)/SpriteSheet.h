#pragma once
#include <SDL.h>
#include <SDL_image.h>
class SpriteSheet
{
private:
	SDL_Surface* mTexture;
	const float mCellSize;
	const int mCellCount;
public:
	SDL_Surface* GetTexture();
};

