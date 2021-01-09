#include "PartyViewerScene.h"

PartyViewerScene::PartyViewerScene(Interface* mgr) : Scene(mgr)
{
	// Add background to scene
	// Add close button to scene
	mCloseBtn = AddObject("CloseBtnObj", 1200, 50, UI);
	// Add character frame object for each party memeber
	// for(Character c  : player.GetCharacters())
	AddObject("characterFrameObj", 250, 350, Background);


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

	int startX = 250; // Allows for equal seperation of portraits and frames
	
	for (Character c : mChars)
	{
		RenderObject& obj = *AddObject(c.GetPortraitName(), startX, 200, Game);
		startX += 250;
		obj.scale = 0.3; // Currently needed as portraits are not uniform size - JP
	}
	startX = 250;
	for (int i = 0; i < mChars.size(); ++i)
	{
		AddObject("characterFrameObj", startX, 350, Background);
		startX += 250;
	}
	//delete obj; // Cleanup temp render object
}

void PartyViewerScene::GetCharacterStatistics()
{
	// Get all party memebers from player
		// for each party memeber
			// get each statistic 
				// convert and store to UIText

	int offsetX = 160;
	int offsetY = 330;
	for (Character c  : mChars)
	{
		CharacterCard cc;
		cc.health.pos = std::make_pair(offsetX, offsetY);
		cc.health.text = "Health: " + std::to_string( c.GetHealth()); // Need to work out how to change this for each seperate stat
		cc.health.textColor = SDL_Color{ 255,0,0 };
		offsetY += 50;
		cc.mana.pos = std::make_pair(offsetX, offsetY);
		cc.mana.text = "Mana: " + std::to_string(c.GetMana());
		cc.mana.textColor = SDL_Color{ 0,0,200 };
		offsetY += 50;
		cc.agility.pos = std::make_pair(offsetX, offsetY);
		cc.agility.text = "Agility: " + std::to_string(c.GetAgility());
		cc.agility.textColor = SDL_Color{ 0,200,0 };
		offsetY += 50;
		cc.stamina.pos = std::make_pair(offsetX, offsetY);
		cc.stamina.text = "Stamina: " + std::to_string(c.GetStamina());
		cc.stamina.textColor = SDL_Color{ 100,200,150 };
		offsetY += 50;
		cc.movement.pos = std::make_pair(offsetX, offsetY);
		cc.movement.text = "Movement: " + std::to_string(c.GetMovement());
		cc.movement.textColor = SDL_Color{ 0,100,25 };

		mSceneText.push_back(cc.health);
		mSceneText.push_back(cc.mana);
		mSceneText.push_back(cc.agility);
		mSceneText.push_back(cc.stamina);
		mSceneText.push_back(cc.movement);

		//mSceneText.push_back(temp);

		offsetX += 250;
		offsetY = 330;
	}

	
	
}
