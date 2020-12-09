#include "ObjectManager.h"


ObjectManager* ObjectManager::sInstance = nullptr;

ObjectManager& ObjectManager::Instance()
{
	if (sInstance == nullptr)
	{
		sInstance = new ObjectManager();
		sInstance->SetUp();
	}

	return *sInstance;
}

ObjectManager::~ObjectManager()
{
	delete sInstance;
	sInstance = nullptr;
}

SDL_Surface* ObjectManager::LoadTexture(std::string path)
{

	SDL_Surface* img = IMG_Load((path.c_str()));
	std::cout << IMG_GetError();
	return img;
}

RenderObject* ObjectManager::RequestObject(std::string name)
{
	RenderObject* obj(objects[name]);
	return obj;
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
			sheets[i.first]->AddAnim(anim.GetName(), anim);
		}
	}
	//Create Object types
	for (auto i : definedObjects)
	{
		objects[i.first] = i.second;
		objects[i.first]->SetTexture(sheets[(objects[i.first]->path)]);
	}
	return true;
}

ObjectManager::ObjectManager()
{
	
}