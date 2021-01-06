#include "OverworldMapScene.h"
#include "GameManager.h"

OverworldMapScene::OverworldMapScene(Interface* mObjMgr) : Scene(mObjMgr)
{
	pOverworld = AddObject("overworldObj", 640, 360, Map);
	pStartNode = AddObject("startNodeObj", 200, 360, UI);
	pBossNode = AddObject("bossNodeObj", 800, 400, UI);
	pShopNode = AddObject("shopNodeObj", 400, 100, UI);
	pBattleNode = AddObject("battleNodeObj", 1000, 200, UI);

	mBackgroundMus = Mix_LoadMUS("Assets/Music/Tavern+Loop+One+-+320bit.mp3");
	
	Mix_Volume(1, 5);
}
OverworldMapScene* OverworldMapScene::Load(std::vector<Node*> nodes)
{
	//mgr->GetAudioManager()->PlayMusic(mBackgroundMus);
	return nullptr;
}
void OverworldMapScene::Init()
{
	
}
void OverworldMapScene::Update(double dTime, Act act, std::pair<int,int> mousePos)
{
	// Mouse interaction, check current act(mouse click = act::click)
	// Iterate through my nodes(is in bounds of mouse position)
	// Check for mouse update
	if (act == Act::Click)
	{
		if (pBattleNode->InBounds(mousePos.first, mousePos.second))
		{
			mgr->LoadScene(Scenes::Combat);
			std::cout << "This is the combat node" << std::endl;
		}
		if (pStartNode->InBounds(mousePos.first, mousePos.second))
		{
			std::cout << "This is the start node" << std::endl;
		}
		if (pShopNode->InBounds(mousePos.first, mousePos.second))
		{
			std::cout << "This is the shop node" << std::endl;
		}
		if (pBossNode->InBounds(mousePos.first, mousePos.second))
		{
			std::cout << "This is the boss node" << std::endl;
		}
	}

	

}