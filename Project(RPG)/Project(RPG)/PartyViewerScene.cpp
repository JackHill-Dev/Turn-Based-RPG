#include "PartyViewerScene.h"

PartyViewerScene::PartyViewerScene(Interface* mgr) : Scene(mgr)
{
	// Add background to scene
	// Add close button to scene

	// Add character frame object for each party memeber
	// for(Character c  : player.GetCharacters())
	AddObject("characterFrameObj", 250, 350, Background);


	wizard = AddObject("WizardObj", 250, 200, Game);
	wizard->scale = 0.4;
	rogue = AddObject("RogueObj", 500, 200, Game);
	rogue->scale = 0.36;
	cleric = AddObject("ClericObj", 750, 200, Game);
	cleric->scale = 0.29;
	warrior = AddObject("WarriorObj", 1000, 200, Game);
	warrior->scale = 0.26;

	

	UIText intelligence;
	intelligence.pos = std::make_pair(160, 330);
	intelligence.text = "Intelligence: ";
	intelligence.textColor = SDL_Color{ 0,0,255 };
	mSceneText["Int stat"] = intelligence;
	
}

void PartyViewerScene::Update(double dTime, Act act, std::pair<int, int> mousePos)
{
	// Check if close button has been pressed 
	//if(act == Act::Click && close->InBounds(mousePos.first, mousePos.second)
		// Go to previous scene that opened the party viewer
		// mgr->LoadScene(mPreviousScene);


	// Update current party stats
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
}

void PartyViewerScene::GetCharacterStatistics()
{
	// Get all party memebers from player
		// for each party memeber
			// get each statistic 
				// convert and store to UIText, need to change slightly how scene text is handled
}
