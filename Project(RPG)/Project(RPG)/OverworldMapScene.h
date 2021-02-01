#pragma once
#include "Character.h"
#include "Scene.h"
#include "Actions.h"
#include <SDL.h>

struct Node
{
	Node(RenderObject* rObj, Scenes sceneForNode) : pNodeObject(rObj), nodeScene(sceneForNode){}
	RenderObject* pNodeObject;
	Scenes nodeScene;
	std::vector<Node*> adjacentTiles;
};

struct Row
{
	std::vector<Node*> nodes;
};

	

class OverworldMapScene : public Scene
{
private:

	std::vector<Node*> mNodes;
	std::vector<std::string> objNames
	{ 
		"startNodeObj",
		"battleNodeObj",
		"shopNodeObj", 
		"bossNodeObj" 
	};

	std::vector<std::pair<int, int>> GoodNodePos
	{
		std::make_pair(120,450), std::make_pair(240,250), std::make_pair(360,250), std::make_pair(480,200), std::make_pair(600,250), std::make_pair(720,300), std::make_pair(840,150), std::make_pair(960,500), std::make_pair(1080,500), std::make_pair(1200,500),
		std::make_pair(120,500), std::make_pair(240,300), std::make_pair(360,300), std::make_pair(480,250), std::make_pair(600,350), std::make_pair(720,450), std::make_pair(840,200), std::make_pair(960,550), std::make_pair(1080,550), std::make_pair(1200,550),
		std::make_pair(120,550), std::make_pair(240,350), std::make_pair(360,350), std::make_pair(480,300), std::make_pair(600,450), std::make_pair(720,500), std::make_pair(840,50), std::make_pair(960,600), std::make_pair(1080,600), std::make_pair(1200,600),
		std::make_pair(120,600), std::make_pair(240,400), std::make_pair(360,500), std::make_pair(480,400), std::make_pair(600,550), std::make_pair(720,550), std::make_pair(840,550), std::make_pair(960,650), std::make_pair(1080,650), std::make_pair(1200,650),
		std::make_pair(120,650), std::make_pair(240,600), std::make_pair(360,550), std::make_pair(480,500), std::make_pair(600,600), std::make_pair(720,600), std::make_pair(840,650), std::make_pair(1300,700), std::make_pair(1080,700), std::make_pair(1200,700),
		std::make_pair(120,7000), std::make_pair(240,700), std::make_pair(360,600), std::make_pair(480,550), std::make_pair(1500,650), std::make_pair(720,650), std::make_pair(100,600), std::make_pair(1300,500), std::make_pair(700,700), std::make_pair(800,700),
	};

	Node* currentNode = nullptr;

	RenderObject* pOverworld = nullptr;
	RenderObject* pMenuButton = nullptr;
	RenderObject* pSettingsButton = nullptr;
	RenderObject* pInventoryButton = nullptr;
	RenderObject* pArmyViewerButton = nullptr;

	Mix_Music* mBackgroundMus = nullptr;
	Mix_Chunk* mSFX = nullptr;

	const int maxRows = 4;
	const int maxNodes = 3;

protected:

public:

	OverworldMapScene(Interface* mObjMgr);
	void Init();
	void Load();

	void Update(double dTime, Act act, std::pair<int,int> mousePos) override;

	//Both SceneChange and HoverHandler will need to be revisited when buttons are in -EH
	void SceneChange(Node* node, Act act, std::pair<int, int> mousePos);
	void HoverHandler(Node* node, Act act, std::pair<int, int> mousePos);
	std::string assignRandomNodeSprite(int num);
	Scenes assignSceneByString(std::string& nodeSceneString);

	void OnHover(Node* node);
	void OnLeave(Node* node);
};


