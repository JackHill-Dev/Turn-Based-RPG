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

	Node* currentNode = nullptr;

	RenderObject* pOverworld = nullptr;
	RenderObject* pMenuButton = nullptr;
	RenderObject* pSettingsButton = nullptr;
	RenderObject* pInventoryButton = nullptr;
	RenderObject* pArmyViewerButton = nullptr;

	Mix_Music* mBackgroundMus = nullptr;
	Mix_Chunk* mSFX = nullptr;

	const int maxRows = 3;
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
	std::string assignRandomNodeSprite();
	Scenes assignSceneByString(std::string& nodeSceneString);

	void OnHover(Node* node);
	void OnLeave(Node* node);
};


