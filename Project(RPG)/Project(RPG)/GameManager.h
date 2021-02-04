#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include "Globals.h"
#include "Scene.h"
#include "Actions.h"
#include "MainMenuScene.h"
#include "OverworldMapScene.h"
#include "ShopScene.h";
#include "PartyViewerScene.h"
#include "SettingsScene.h"
#include "Character.h"
#include "Interface.h"

#include "Player.h"
#include "CombatScene.h"
#include "Consumable.h"
#include "Armour.h"
#include "InventoryScene.h"
#include "ClassPickerScene.h"
class GameManager
{
private:

	ClassPickerScene* mClassPickerInstance;
	std::pair<CombatScene*, std::vector<Character*>> combatInstance;
	PartyViewerScene* partyViewerInstance;
	InventoryScene* mInventorySceneInstance;
	SettingsScene* mSettingsSceneInstance;
	ShopScene* mShopSceneInstance;
	MainMenuScene* mMainMenuSceneInstance;


	bool bRunning= true;
	int mCScene = 0;
	SDL_Window* mWnd;
	SDL_Renderer* mRnd;
	SDL_Surface* mSurface;

	Player mPlayer;
	std::map<std::string, RenderObject*> objects; // This is where the RenderObject types are stored 
	std::map<std::string, SpriteSheet*> sheets; // This is where the spritesheets are stored
	std::map<std::string, Card*> cards;
	//Interface mInterface{&bRunning, &objects, &mPlayer,&mCScene };


	Interface mInterface{&bRunning, &objects,&mCScene, &combatInstance.second, &mPlayer, &mSettings};


	SDL_Texture* LoadTexture(std::string path); //Moved it here for now
	void CreateCard(DefinedCard* card);
	void LoadScene();
	
public:
	GameManager() {}
	bool Init();

	void Run();
	void Quit();	
	
private:
	void LoadSettings();
	void SetupPlayer();
	bool SetUp();
	bool CreateWindow();
	std::vector<Scene*> scenes;
	Scene* currentScene;
	Settings mSettings;

	// temp
	Consumable mPotion;
	Armour mArmour;
	Character mWizard;
	Character mWarrior;
};


