#include "PartyViewerScene.h"

PartyViewerScene::PartyViewerScene(Interface* mgr) : Scene(mgr)
{
	// Add background to scene
	AddObject("mainMenuBGObj", 640, 360, Background);
	// Add close button to scene
	mCloseBtn = AddObject("CloseBtnObj", 1200, 50, UI);




	Init();

	
	
}

void PartyViewerScene::Update(double dTime, Act act, std::pair<int, int> mousePos)
{
	// Check if close button has been pressed 
	if (act == Act::Click && mCloseBtn->InBounds(mousePos.first, mousePos.second))
		mgr->LoadPreviousScene(); 	// Go to previous scene that opened the party viewer

}

void PartyViewerScene::Init()
{
	GetCharacterPortraits();
	GetCharacterStatistics();
}

void PartyViewerScene::GetCharacterPortraits()
{
	// Get all party memebers from player
		// Get all of their portrait render objects and add them to the scene
	// std::vector<Character*> party = mgr->GetPlayer()->GetParty()
	Character wizard("maleObj", "WizardObj");
	Character cleric("maleObj", "ClericObj");
	Character rogue("maleObj", "RogueObj");
	Character warrior("maleObj", "WarriorObj");

	mChars.push_back(wizard);
	mChars.push_back(cleric);
	mChars.push_back(warrior);
	mChars.push_back(rogue);

	int offsetX = 250; // Allows for equal seperation of portraits and frames
	
	for (Character c : mChars)
	{
		RenderObject& obj = *AddObject(c.GetPortraitName(), offsetX, 180, Game);
		offsetX += 250;
	}
	offsetX = 250;
	// Add character frame object for each party memeber
	for (int i = 0; i < mChars.size(); ++i)
	{
		AddObject("characterFrameObj", offsetX, 350, Background);
		offsetX += 250;
	}
}

void PartyViewerScene::GetCharacterStatistics()
{
	

	int offsetX = 160;
	int offsetY = 330;
	for (Character c  : mChars) // Change to looping through the player's party members
	{
		CharacterCard cc;
		cc.health = DrawStat("Health", c.GetStats().health.second, SDL_Color{255,0,0}, std::make_pair(offsetX, offsetY));
		offsetY += 50;

		cc.mana = DrawStat("Mana", c.GetStats().mana.second, SDL_Color{ 0,0,200 }, std::make_pair(offsetX, offsetY));

		offsetY += 50;
		cc.agility = DrawStat("Agility", c.GetStats().agility.second, SDL_Color{ 0,200,0 }, std::make_pair(offsetX, offsetY));

		offsetY += 50;
		cc.stamina = DrawStat("Stamina", c.GetStats().stamina.second, SDL_Color{ 50, 143, 23 }, std::make_pair(offsetX, offsetY));

		offsetY += 50;
		cc.movement = DrawStat("Movement", c.GetStats().movement.second, SDL_Color{ 50,50,150 }, std::make_pair(offsetX, offsetY));

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
	return UIText{statTxt, pos, textColor};
}
