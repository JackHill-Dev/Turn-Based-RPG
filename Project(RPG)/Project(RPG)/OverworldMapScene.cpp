#include "OverworldMapScene.h"
#include "GameManager.h"

enum NodeRole{Battle, Boss, Shop, Start};

OverworldMapScene::OverworldMapScene(GameManager* mObjMgr) : Scene(mObjMgr)
{
	pOverworld = AddObject("overworldObj", 1024, 1024, Map);
	pStartNode = AddObject("startNodeObj", 1024, 980, UI);
	pBossNode = AddObject("bossNodeObj", 2000, 400, UI);
	pShopNode = AddObject("shopNodeObj", 800, 1100, UI);
	pBattleNode = AddObject("battleNodeObj", 1200, 400, UI);

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
			//mgr->LoadCombatScene({ new Character("maleObj"),new Character("maleObj"), new Character("maleObj") , new Character("maleObj") }, { new Character("maleObj") });
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
