#pragma once
#include "Character.h"
#include "Scene.h"
#include "Actions.h"
#include <set>
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
		"shopNodeObj",
		"battleNodeObj",
		"bossNodeObj" 
	};

	std::vector<std::vector<std::pair<int, int>>> nodepositions
	{
		{},{},{},{},{}
	}
		;

	int currentNode = 0;

	RenderObject* pOverworld = nullptr;
	RenderObject* pMenuButton = nullptr;
	RenderObject* pSettingsButton = nullptr;
	RenderObject* pArmyViewerButton = nullptr;

	Mix_Music* mBackgroundMus = nullptr;
	Mix_Chunk* button_Click_SFX;
	Mix_Chunk* confirm_SFX;
	Mix_Chunk* back_SFX;
	Mix_Chunk* shop_Entry_SFX;

	SDL_Color RoyalBlue = SDL_Color{ 65, 105, 225 };
	SDL_Color DarkMagenta = SDL_Color{ 139,0, 139 };
	SDL_Color Lime = SDL_Color{ 0,255, 0 };

	const int maxRows = 4;
	const int maxNodes = 3;

protected:

public:
	void SaveFile();
	OverworldMapScene(Interface* mObjMgr);

	void Init();
	void Load();
	void LoadNodes();
	void LoadNodes(int seed);
	void Update(double dTime, Act act, std::pair<int,int> mousePos) override;

	std::string assignRandomNodeSprite(int num);
	Scenes assignSceneByString(std::string& nodeSceneString);

	void OnHover(RenderObject* rObj);
	void OnLeave(RenderObject* rObj);

};


