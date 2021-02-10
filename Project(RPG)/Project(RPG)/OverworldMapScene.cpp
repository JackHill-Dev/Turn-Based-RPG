#include "OverworldMapScene.h"
#include "GameManager.h"
#include <set>




static std::random_device rd;
static std::mt19937 random_number_engine(rd());

int RandomNumberGenerator(int min, int max)
{
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(random_number_engine);
}

OverworldMapScene::OverworldMapScene(Interface* mObjMgr) : Scene(mObjMgr)
{
	pOverworld = AddObject("overworldObj", 640, 360, Map);
	pArmyViewerButton = AddObject("armyViewerButtonObj", 730, 700, UI);
	pMenuButton = AddObject("menuButtonObj", 440, 700, UI);
	mBackgroundMus = Mix_LoadMUS("Assets/Music/Overworld.mp3");
	
	Init();
	LoadNodes();
}

void OverworldMapScene::LoadNodes()
{


	int maxVals = maxRows * maxNodes;
	int valCount = 0;
	int nodeIndex = 0;
	std::vector<Row> rows;
	std::set<std::pair<int, int>> uniqueCoords;
	std::vector<std::pair<int, int>> validCoords;
	std::pair<int, int> oldCoords = std::make_pair<int,int>(0,0);
	

	while (valCount < maxVals)
	{
		int oldSetSize = uniqueCoords.size();

		uniqueCoords.insert(GoodNodePos[RandomNumberGenerator(0, 49)]);

		if (uniqueCoords.size() > oldSetSize)
		{
			++valCount;
		}
	}

	std::copy(uniqueCoords.begin(), uniqueCoords.end(), std::back_inserter(validCoords));
	//for (auto cord : validCoords)
	//{
	//	std::cout << cord.first << " -X\tY: ";
	//	std::cout << cord.second << std::endl;
	//}

	for (int rowCount = 0; rowCount < maxRows; ++rowCount)
	{
		Row newRow;

		
		for (int nodeCount = 0; nodeCount < maxNodes; ++nodeCount)
		{
			newRow.nodes.push_back
			(new Node(AddObject(assignRandomNodeSprite(rowCount), validCoords[nodeIndex].first,
							   validCoords[nodeIndex].second, Layer::UI), Scenes::NoSceneYet));
			newRow.nodes[nodeCount]->nodeScene = assignSceneByString(newRow.nodes[nodeCount]->pNodeObject->path);
			++nodeIndex;
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
	currentNode->pNodeObject->tint = SDL_Color{ 139,0, 139 };
	for (auto node : currentNode->adjacentTiles)
	{
		if (node != currentNode)
		{
			node->pNodeObject->tint = SDL_Color{ 65, 105, 225 };
		}
	}
}

void OverworldMapScene::Init()
{
	confirm_SFX = Mix_LoadWAV("Assets/SFX/confirmSound.wav");
	back_SFX = Mix_LoadWAV("Assets/SFX/BackSound.wav");
	button_Click_SFX = Mix_LoadWAV("Assets/SFX/GenericClick.wav");
	shop_Entry_SFX = Mix_LoadWAV("Assets/SFX/DoorOpen.wav");
}
void OverworldMapScene::Load()
{
	currentNode->pNodeObject->tint = SDL_Color{ 139,0, 139 };

	if (mgr->GetPreviousScene() != Scenes::SettingsPage)
	{
		mgr->FadeInMusic(mBackgroundMus, -1, mgr->fadeTime);
	}
}
void OverworldMapScene::OnHover(RenderObject* rObj)
{
	rObj->tint = SDL_Color{ 0,255, 0 };
}
void OverworldMapScene::OnLeave(RenderObject* rObj)
{
	rObj->Untint();
}

void OverworldMapScene::Update(double dTime, Act act, std::pair<int,int> mousePos)
{
	currentNode->pNodeObject->tint = SDL_Color{ 139,0, 139 };
	
	if (act == Act::Click)
	{
		for (auto node : currentNode->adjacentTiles)
		{
			if (node->pNodeObject->InBounds(mousePos.first, mousePos.second))
			{
				currentNode = node;
				if (node->nodeScene != Scenes::NoSceneYet)
				{
					switch (node->nodeScene)
					{
						case Scenes::Combat:
							mgr->PlaySFX(button_Click_SFX, 0, 1);
							mgr->LoadCombatScene({ new Character("maleObj", "portrait"), new Character("maleObj", "portrait"), new Character("maleObj", "portrait") });
							break;

						case Scenes::Shops:
							mgr->PlaySFX(shop_Entry_SFX, 0, 1);
							mgr->LoadScene(node->nodeScene);
							break;

						default:
							mgr->LoadScene(node->nodeScene);
							break;
					}
				}
				else
				{
					mgr->PlaySFX(button_Click_SFX, 0, 1);
				}				
			}
			node->pNodeObject->Untint();
		}

		if (pArmyViewerButton->InBounds(mousePos.first, mousePos.second))
		{
			mgr->PlaySFX(button_Click_SFX, 0, 1);			
			OnLeave(pArmyViewerButton);
			mgr->LoadScene(Scenes::Party);
		}
		if (pMenuButton->InBounds(mousePos.first, mousePos.second))
		{
			mgr->PlaySFX(button_Click_SFX, 0, 1);
			OnLeave(pMenuButton);
			mgr->LoadScene(Scenes::SettingsPage);
		}
		
	}
	if (act == Act::MouseUpdate)
	{
		if (pMenuButton->InBounds(mousePos.first, mousePos.second))
		{
			OnHover(pMenuButton);
		}
		else
		{
			OnLeave(pMenuButton);
		}
		if(pArmyViewerButton->InBounds(mousePos.first, mousePos.second))
		{
			OnHover(pArmyViewerButton);
		}
		else
		{
			OnLeave(pArmyViewerButton);
		}
	}
	for (auto node : currentNode->adjacentTiles)
	{
		if (node != currentNode)
		{
			node->pNodeObject->tint = SDL_Color{ 65, 105, 225 };
		}
	}
}

std::string OverworldMapScene::assignRandomNodeSprite(int num)
{
	if (num <=3)
	{
		return objNames[num];
	}
	else 
	{
		return objNames[RandomNumberGenerator(0, 3)];
	}
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

void OverworldMapScene::MutateNodePos(Node node)
{
	float mutator = 25;
	std::pair<float, float> oldPos = node.pNodeObject->GetPos();
	oldPos.first += RandomNumberGenerator(-mutator, mutator); // Mutate x
	if (oldPos.first >= 1280)
		oldPos.first -= mutator;
	oldPos.second += RandomNumberGenerator(-mutator, mutator); // Mutate Y
	if (oldPos.second >= 720)
		oldPos.second -= mutator;
	node.pNodeObject->SetPos(oldPos);
}

