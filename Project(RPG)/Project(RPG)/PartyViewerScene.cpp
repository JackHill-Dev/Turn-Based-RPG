#include "PartyViewerScene.h"

PartyViewerScene::PartyViewerScene(Interface* mgr) : Scene(mgr)
{
	// Add background to scene
	AddObject("mainMenuBGObj", 640, 360, Background);
	// Add close button to scene
	mCloseBtn = AddObject("CloseBtnObj", 1200, 50, UI);
	mInventoryBtn = AddObject("inventoryButtonObj", 640, 700, UI);
	button_SFX = Mix_LoadWAV("Assets/SFX/GenericClick.wav");
	mMenuMusic = Mix_LoadMUS("Assets/Music/MenuMusic.mp3");
	Init();

}

void PartyViewerScene::Update(double dTime, Act act, std::pair<int, int> mousePos)
{
	// Check if close button has been pressed 
	if (act == Act::Click && mCloseBtn->InBounds(mousePos.first, mousePos.second))
	{
		mgr->PlaySFX(button_SFX, 0, 1);
		mgr->LoadScene(Overworld); 	// Go to previous scene that opened the party viewer
	}
		
	if (act == Act::Click && mInventoryBtn->InBounds(mousePos.first, mousePos.second))
	{
		mgr->PlaySFX(button_SFX, 0, 1);
		mgr->LoadScene(Scenes::InventoryScreen); // Inventory screen
	}
	
	mSceneText.clear();

	GetCharacterStatistics();
}


void PartyViewerScene::Init()
{
	mParty = mgr->GetPlayer()->GetParty();
	GetCharacterPortraits();

	GetCharacterStatistics();
}

void PartyViewerScene::Load()
{
	
	mParty = mgr->GetPlayer()->GetParty();
	GetCharacterPortraits();

	if (mgr->GetPreviousScene() != Scenes::InventoryScreen)
	{
		mgr->FadeInMusic(mMenuMusic, -1, mgr->fadeTime);
	}
}

void PartyViewerScene::GetCharacterPortraits()
{
	int offsetX = 250; // Allows for equal seperation of portraits and frames
	
	// Get all party memebers from player
	for (Character* c : mParty)
	{
		AddObject(c->GetPortraitName(), offsetX, 180, UI); // Get all of their portrait render objects and add them to the scene
		offsetX += 250;							
	}
	offsetX = 250;
	// Add character frame object for each party memeber
	for (int i = 0; i < mParty.size(); ++i)
	{
		AddObject("characterFrameObj", offsetX, 350, Background);
		offsetX += 250;
	}
}

void PartyViewerScene::GetCharacterStatistics()
{
	int offsetX = 200;
	int offsetY = 330;
	for (Character* c  : mParty) 
	{
		CharacterCard cc;
		cc.health = DrawStat("Health", c->GetStats().health.second, SDL_Color{255,0,0}, std::make_pair(offsetX, offsetY));
		offsetY += 50;

		cc.mana = DrawStat("Mana", c->GetStats().mana.second, SDL_Color{ 0,0,200 }, std::make_pair(offsetX, offsetY));

		offsetY += 50;
		cc.agility = DrawStat("Agility", c->GetStats().agility.second, SDL_Color{ 0,200,0 }, std::make_pair(offsetX, offsetY));

		offsetY += 50;
		cc.stamina = DrawStat("Stamina", c->GetStats().stamina.second, SDL_Color{ 50, 143, 23 }, std::make_pair(offsetX, offsetY));

		offsetY += 50;
		cc.movement = DrawStat("Movement", c->GetStats().movement.second, SDL_Color{ 50,50,150 }, std::make_pair(offsetX, offsetY));

		mSceneText.push_back(cc.health);
		mSceneText.push_back(cc.mana);
		mSceneText.push_back(cc.agility);
		mSceneText.push_back(cc.stamina);
		mSceneText.push_back(cc.movement);


		offsetX += 250;
		offsetY = 330;
	}
}

UIText PartyViewerScene::DrawStat(std::string statName, int stat, SDL_Color textColor, std::pair<int, int> pos)
{
	std::string statTxt = statName + ": " + std::to_string(stat);
	return UIText{statTxt, pos,std::make_pair(70,50), textColor};
}

