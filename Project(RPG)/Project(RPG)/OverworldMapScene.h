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

struct Legend
{
	UIText mStandardNodeLabel;
	UIText mShopNodeLabel;
	UIText mBossNodeLabel;
	UIText mCurrentLabel;
	UIText mAdjacentLabel;
	UIText mHeaderText;
	UIText mInstructionText;

	RenderObject* mNormalNode = nullptr;
	RenderObject* mHoveredNode = nullptr;
	RenderObject* mShopNode = nullptr;
	RenderObject* mHoveredShop = nullptr;
	RenderObject* mBossNode = nullptr;
	RenderObject* mHoveredBoss = nullptr;

	std::vector<RenderObject*> mLegendObjects;
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
	};

	int currentNode = 0;

	RenderObject* pOverworld = nullptr;
	RenderObject* pLegend = nullptr;
	RenderObject* pLegendButton = nullptr;
	RenderObject* pMenuButton = nullptr;
	RenderObject* pSettingsButton = nullptr;
	RenderObject* pArmyViewerButton = nullptr;

	std::vector<RenderObject*> mOverworldButtons;

	Mix_Music* mBackgroundMus = nullptr;
	Mix_Chunk* button_Click_SFX;
	Mix_Chunk* confirm_SFX;
	Mix_Chunk* back_SFX;
	Mix_Chunk* shop_Entry_SFX;

	SDL_Color RoyalBlue = SDL_Color{ 65, 105, 225 };
	SDL_Color DarkMagenta = SDL_Color{ 139,0, 139 };
	SDL_Color Lime = SDL_Color{ 0,255, 0 };
	SDL_Color Black = SDL_Color{ 0,0,0 };

	

	const int maxRows = 4;
	const int maxNodes = 3;
	Legend mLegend;
	bool legendOn = true;

protected:

public:
	void SaveFile();
	OverworldMapScene(Interface* mObjMgr);

	void Init();
	void Load();
	void LoadNodes();
	void LoadNodes(int seed);
	void ShowLegend();
	void HideLegend();
	void Update(double dTime, Act act, std::pair<int,int> mousePos) override;

	std::string assignRandomNodeSprite(int num);
	Scenes assignSceneByString(std::string& nodeSceneString);

	void OnHover(RenderObject* rObj);
	void OnLeave(RenderObject* rObj);

};


