#include "ObjectManager.h"






ObjectManager::~ObjectManager()
{
	

}

SDL_Texture* ObjectManager::LoadTexture(std::string path)
{
	SDL_Surface* img = IMG_Load((path.c_str()));
	
	std::cout << IMG_GetError();
	return SDL_CreateTextureFromSurface(mRnd, img);
}

RenderObject* ObjectManager::RequestObject(std::string name)
{	
	return objects[name]->Clone();
}

bool ObjectManager::SetUp()
{
	
	//Converts definitions found in GameObjects.h to fully initlised and stored objects

	//Load sheets
	for (auto i : definedSheets)
	{
		sheets[i.first] = i.second;
		sheets[i.first]->SetTexture(LoadTexture(i.second->mFilePath));
	}
	//Add animations to sheets
	for (auto i : definedAnimations)
	{
		for (auto anim : i.second)
		{
			auto a = sheets[i.first];
			sheets[i.first]->AddAnim(anim.GetName(), anim);
		}
	}
	//Create Object types
	for (auto i : definedObjects)
	{
		objects[i.first] = i.second;
		objects[i.first]->SetTexture(sheets[(objects[i.first]->path)]);
		objects[i.first]->Init(mgrs);
	}
	return true;
}

ObjectManager::ObjectManager(SDL_Renderer* rnd, Managers* mgr)
{
	mRnd = rnd;
	mgrs = mgr;
	SetUp();
}