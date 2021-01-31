#include "OverworldMapScene.h"
#include "GameManager.h"




static std::random_device rd;
static std::mt19937 random_number_engine(rd());

int RandomNumberGenerator(int min, int max)
{
	int i = 0;
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(random_number_engine);
}

OverworldMapScene::OverworldMapScene(Interface* mObjMgr) : Scene(mObjMgr)
{
	pOverworld = AddObject("overworldObj", 640, 360, Map);
	pArmyViewerButton = AddObject("armyViewerButtonObj", 730, 700, UI);
	pMenuButton = AddObject("menuButtonObj", 440, 700, UI);
	mBackgroundMus = Mix_LoadMUS("Assets/Music/Tavern+Loop+One+-+320bit.mp3");
	
	//Mix_Volume(1, 5);
	Init();
	Load();
}

void OverworldMapScene::Load()
{
	std::vector<Row> rows;

	for (int rowCount = 0; rowCount < maxRows; ++rowCount)
	{
		Row newRow;

		for (int nodeCount = 0; nodeCount < maxNodes; ++nodeCount)
		{
			newRow.nodes.push_back
			(new Node(AddObject(assignRandomNodeSprite(), RandomNumberGenerator(200,1000),
							   RandomNumberGenerator(200,600), Layer::UI), Scenes::NoSceneYet));
			newRow.nodes[nodeCount]->nodeScene = assignSceneByString(newRow.nodes[nodeCount]->pNodeObject->path);
		}
		rows.push_back(newRow);
	}

	//Generating Links
	for (int rowNum = 0; rowNum < rows.size(); ++rowNum)
	{
		for (int rowNode = 0; rowNode < rows[rowNum].nodes.size(); ++rowNode)
		{
			if (rowNum > 0)
			{
				rows[rowNum].nodes[rowNode]->adjacentTiles.push_back(rows[rowNum-1].nodes[rowNode]);
			}
			if (rowNum < rows.size()-1)
			{
				rows[rowNum].nodes[rowNode]->adjacentTiles.push_back(rows[rowNum+1].nodes[rowNode]);
			}
			if (rowNode > 0)
			{
				rows[rowNum].nodes[rowNode]->adjacentTiles.push_back(rows[rowNum].nodes[rowNode-1]);
			}
			if (rowNode < rows[rowNum].nodes.size() - 1)
			{
				rows[rowNum].nodes[rowNode]->adjacentTiles.push_back(rows[rowNum].nodes[rowNode + 1]);
			}
		}
	}
	for (auto row : rows)
	{
		for (auto rowNode : row.nodes)
		{
			mNodes.push_back(rowNode);
		}
	}
	currentNode = mNodes[0];
}

void OverworldMapScene::Init()
{
	//mgr->PlayMusic(mBackgroundMus, -1);
}
void OverworldMapScene::OnHover(Node* node)
{
	node->pNodeObject->tint = SDL_Color{ 0,255, 0 };
}
void OverworldMapScene::OnLeave(Node* node)
{
	node->pNodeObject->Untint();
}

void OverworldMapScene::Update(double dTime, Act act, std::pair<int,int> mousePos)
{
	currentNode->pNodeObject->tint = SDL_Color{ 0,0,255 };
	
	if (act == Act::Click)
	{
		for (auto node : currentNode->adjacentTiles)
		{
			if (node->pNodeObject->InBounds(mousePos.first, mousePos.second))
			{
				currentNode = node;
				if(node->nodeScene != Scenes::NoSceneYet)
				{	
					if (node->nodeScene == Scenes::Combat)
					{
						mgr->LoadCombatScene({ new Character("maleObj", "portrait") });
					}
					else
						mgr->LoadScene(node->nodeScene);
				}
				
			}
			node->pNodeObject->Untint();
		}
		if (pArmyViewerButton->InBounds(mousePos.first, mousePos.second))
		{
			mgr->LoadScene(Scenes::Party);
		}
		if (pMenuButton->InBounds(mousePos.first, mousePos.second))
		{
			mgr->LoadScene(Scenes::SettingsPage);
		}
		
	}
	if (act == Act::MouseUpdate)
	{
		for (auto node : currentNode->adjacentTiles)
		{
			if (node->pNodeObject->InBounds(mousePos.first, mousePos.second))
			{
				OnHover(node);
			}
			else
			{
				OnLeave(node);
			}			
		}
	}
	for (auto node : currentNode->adjacentTiles)
	{
		if (node != currentNode)
		{
			node->pNodeObject->tint = SDL_Color{ 0, 0, 0 };
		}
	}
}

std::string OverworldMapScene::assignRandomNodeSprite()
{
	return objNames[RandomNumberGenerator(0, 3)];
}

Scenes OverworldMapScene::assignSceneByString(std::string& nodeSceneString)
{
	if (nodeSceneString == "battleNode")
	{
		return Scenes::Combat;
	}
	if (nodeSceneString == "shopNode")
	{
		return Scenes::Shops;
	}
	else
	{
		return Scenes::NoSceneYet;
	}
}

