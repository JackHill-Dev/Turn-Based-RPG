#pragma once
#include "Globals.h"
#include "Database.h"
#include "RenderObject.h"
#include "GameObjects.h"
#include "ImportManager.h"
class ObjectManager
{
private:
	static ObjectManager* sInstance;
	
	Database db;
	std::map<std::string, RenderObject*> objects; // This is where the RenderObject types are stored 
	std::map<std::string, SpriteSheet*> sheets; // This is where the spritesheets are stored
	SDL_Surface* LoadTexture(std::string path); //Moved it here for now
	
public:

	RenderObject* RequestObject(std::string name); //Scenes will call this to add a renderobject to it
	bool SetUp();
	static ObjectManager& Instance();
private:
	ObjectManager();
	~ObjectManager();
	
};

