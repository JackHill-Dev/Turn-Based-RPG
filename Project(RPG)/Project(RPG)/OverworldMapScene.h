#pragma once
#include "Character.h"
#include "Scene.h"
#include "Actions.h"
#include <SDL.h>

struct Node
{
	RenderObject* pNodeObj;
	Scenes nodeScene;
};


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

	OverworldMapScene(Interface* mObjMgr);

	OverworldMapScene* Load(std::vector<Node*> nodes);
	void setRandomNodePos(Node* node);
	void Init();
	void OnHover();
	void OnLeave();
	void Update(double dTime, Act act, std::pair<int,int> mousePos) override;

};


