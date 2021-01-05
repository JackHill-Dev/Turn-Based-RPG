#include "OverworldMapScene.h"

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
	
}
