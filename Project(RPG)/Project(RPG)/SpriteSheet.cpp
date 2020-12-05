#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(SDL_Surface* nTexture, float nCellSize, int nCellCount) : mTexture(nTexture), mCellCount(nCellCount), mCellSize(nCellSize)
{
	anims["default"] = new Animation(0, 0);
}

SDL_Surface* SpriteSheet::GetTexture()
{
	return mTexture;
}

float SpriteSheet::GetCellSize()
{
	return mCellSize;
}
Animation* SpriteSheet::GetAnim(std::string name)
{
	return anims[name];
}
void SpriteSheet::AddAnim(std::string name, Animation* anim)
{
	anims[name] = anim;
}