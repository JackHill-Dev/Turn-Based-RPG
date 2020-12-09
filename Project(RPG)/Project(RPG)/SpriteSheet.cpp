#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(std::string path, float nCellSize, int nCellCount) : mFilePath(path), mCellCount(nCellCount), mCellSize(nCellSize)
{
	anims["default"] = new Animation("default", 0, 0, 0);
}

SDL_Surface* SpriteSheet::GetTexture()
{
	return mTexture;
}

bool SpriteSheet::SetTexture(SDL_Surface* texture)
{
	if (mTexture == nullptr)
	{
		mTexture = texture;
		return true;
	}
	return false;

}

float SpriteSheet::GetCellSize()
{
	return mCellSize;
}
Animation* SpriteSheet::GetAnim(std::string name)
{
	return anims[name];
}
void SpriteSheet::AddAnim(std::string name, Animation anim)
{
	anims[name] = &anim;
}