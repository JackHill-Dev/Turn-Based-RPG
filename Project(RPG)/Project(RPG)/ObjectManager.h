#pragma once
#include "Globals.h"
#include "Database.h"
#include "RenderObject.h"
#include "GameObjects.h"
#include "ImportManager.h"
class ObjectManager
{
private:
	
	SDL_Renderer* mRnd;
	Database db;
	std::map<std::string, RenderObject*> objects; // This is where the RenderObject types are stored 
	std::map<std::string, SpriteSheet*> sheets; // This is where the spritesheets are stored
	SDL_Texture* LoadTexture(std::string path); //Moved it here for now
	Managers* mgrs;
	
public:

	RenderObject* RequestObject(std::string name); //Scenes will call this to add a renderobject to it
	bool SetUp();
	Managers* GetManagers() { return mgrs; }
	ObjectManager(SDL_Renderer* rnd, Managers* mgr);
private:
	
	~ObjectManager();
	
};

