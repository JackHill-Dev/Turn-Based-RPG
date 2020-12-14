#include "OverworldMap.h"
#include "OverworldMapScene.h"

OverworldMapScene::OverworldMapScene()
{
	pOverworld = AddObject("overworldObj", 0, 0, Map);
}

void OverworldMapScene::Update(double dTime, Act act)
{
}
