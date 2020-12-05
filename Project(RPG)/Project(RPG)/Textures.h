#pragma once
#include "Globals.h"
#include "Animation.h"
struct TextureDefinition
{
	TextureDefinition(std::string name, int size, int x, int y, std::vector<Animation> anims)
	{
		
		fileName = name;
		cellsize = size;
		cellcountx = x;
		cellcounty = y;

		mAnims = anims;
	}
	std::string fileName;
	int cellsize;
	int cellcountx;
	int cellcounty;
	std::vector<Animation> mAnims;
};

const std::vector<TextureDefinition> Textures{
};