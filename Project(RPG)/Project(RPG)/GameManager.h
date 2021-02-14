#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <fstream>;
#include <istream>
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
#include "ClassPickerScene.h"
#include "Consumable.h"
#include "Armour.h"
#include "InventoryScene.h"
#include "json.hpp"
#include "OverworldMapScene.h"
#include "WinLoseStateScene.h"


class GameManager
{

private:

	std::pair<CombatScene*, std::vector<Character*>> combatInstance;
	PartyViewerScene* partyViewerInstance;
	InventoryScene* mInventorySceneInstance;
	ShopScene* mShopSceneInstance;
	MainMenuScene* mMainMenuSceneInstance;
	OverworldMapScene* mOverworldInstance;
	SettingsScene* mSettingsSceneInstance;
	ClassPickerScene* mClassPickerInstance;
	WinLoseStateScene* mWinLoseStateSceneInstance;

	bool bRunning= true;
	Scenes mCScene = Scenes::MainMenu;
	SDL_Window* mWnd;
	SDL_Renderer* mRnd;
	SDL_Surface* mSurface;

	Player mPlayer;
	std::map<std::string, RenderObject*> objects; // This is where the RenderObject types are stored 
	std::map<std::string, SpriteSheet*> sheets; // This is where the spritesheets are stored
	std::map<std::string, Card*> cards;

	Interface mInterface{&bRunning, &objects, &mCScene, &combatInstance.second, &mPlayer, &mSettings};

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


