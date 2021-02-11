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

	std::vector<std::pair<int, int>> GoodNodePos
	{
		std::make_pair(120,440), std::make_pair(240,240), std::make_pair(340,230), std::make_pair(460,190), std::make_pair(580,260), std::make_pair(700,290), std::make_pair(820,150), std::make_pair(940,490), std::make_pair(1060,490), std::make_pair(1180,505),
		std::make_pair(140,500), std::make_pair(220,310), std::make_pair(350,300), std::make_pair(470,250), std::make_pair(590,350), std::make_pair(710,450), std::make_pair(830,200), std::make_pair(955,535), std::make_pair(1070,545), std::make_pair(1190,555),
		std::make_pair(80,540), std::make_pair(260,360), std::make_pair(360,340), std::make_pair(480,300), std::make_pair(600,450), std::make_pair(720,500), std::make_pair(840,50), std::make_pair(960,610), std::make_pair(1080,605), std::make_pair(1200,600),
		std::make_pair(100,610), std::make_pair(230,390), std::make_pair(370,510), std::make_pair(490,430), std::make_pair(630,550), std::make_pair(730,550), std::make_pair(850,550), std::make_pair(970,650), std::make_pair(1090,650), std::make_pair(1210,640),
		std::make_pair(110,650), std::make_pair(250,590), std::make_pair(380,550), std::make_pair(500,500), std::make_pair(620,610), std::make_pair(740,600), std::make_pair(860,670), std::make_pair(1240,570), std::make_pair(1110,705), std::make_pair(1220,690),
		std::make_pair(130,690), std::make_pair(270,700), std::make_pair(390,600), std::make_pair(510,560), std::make_pair(1100,660), std::make_pair(760,650), std::make_pair(100,600), std::make_pair(990,550), std::make_pair(690,695), std::make_pair(800,700),
	};

	Node* currentNode = nullptr;

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

	OverworldMapScene(Interface* mObjMgr);

	void Init();
	void Load();
	void LoadNodes();

	void Update(double dTime, Act act, std::pair<int,int> mousePos) override;

	std::string assignRandomNodeSprite(int num);
	Scenes assignSceneByString(std::string& nodeSceneString);

	void OnHover(RenderObject* rObj);
	void OnLeave(RenderObject* rObj);

};


