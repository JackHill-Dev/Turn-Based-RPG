#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(SDL_Surface* nTexture, float nCellSize, int nCellCount) : mTexture(nTexture), mCellCount(nCellCount), mCellSize(nCellSize)
{
}

SDL_Surface* SpriteSheet::GetTexture()
{
	return mTexture;
}

float SpriteSheet::GetCellSize()
{
	return mCellSize;
}
