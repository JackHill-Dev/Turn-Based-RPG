#pragma once
#include "Scene.h"
#include "Actions.h"
#include <SDL.h>
#include "Node.h"

class OverworldMapScene : public Scene
{
private:
	std::vector<Node*> mNodes;
	RenderObject* pOverworld;
	RenderObject* pStartNode;
	RenderObject* pBossNode;
	RenderObject* pShopNode;
	RenderObject* pBattleNode;
	Mix_Music* mBackgroundMus;
	Mix_Chunk* mSFX;

protected:

public:

	OverworldMapScene(GameManager* mObjMgr);

	OverworldMapScene* Load(std::vector<Node*> nodes);
	void Init();

	void Update(double dTime, Act act, std::pair<int,int> mousePos) override;

};


