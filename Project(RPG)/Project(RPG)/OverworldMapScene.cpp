#include "OverworldMapScene.h"

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
	
	// Makes use of std::set which prevents duplicate values. Retrieves a random coordinate pair from a lookup table and tries to insert it
	// If it is successfully added and the size of the set increases, increment the count until there's a pair for every node - EH
	while (valCount < maxVals)
	{
		int oldSetSize = uniqueCoords.size();

		uniqueCoords.insert(GoodNodePos[RandomNumberGenerator(0, 49)]);

		if (uniqueCoords.size() > oldSetSize)
		{
			++valCount;
		}
	}

	// Copy into a vector so we can access by index - EH
	std::copy(uniqueCoords.begin(), uniqueCoords.end(), std::back_inserter(validCoords));

	// For debugging purposes. Keep in for testing to allow all of us to track node positions during testing - EH
	for (auto cord : validCoords)
	{
		std::cout << cord.first << " :X\tY: ";
		std::cout << cord.second << std::endl;
	}

	// Generates a group of  x amount of nodes collected into x amount of rows - EH
	for (int rowCount = 0; rowCount < maxRows; ++rowCount)
	{
		Row newRow;

		
		for (int nodeCount = 0; nodeCount < maxNodes; ++nodeCount)
		{
			newRow.nodes.push_back
			(new Node(AddObject(assignRandomNodeSprite(rowCount + nodeCount), validCoords[nodeIndex].first,
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
			// Adjacent Node above - EH
			if (rowNum > 0)
			{
				rows[rowNum].nodes[rowNode]->adjacentTiles.push_back(rows[rowNum-1].nodes[rowNode]);
			}
			// Adjacent Node below - EH
			if (rowNum < rows.size()-1)
			{
				rows[rowNum].nodes[rowNode]->adjacentTiles.push_back(rows[rowNum+1].nodes[rowNode]);
			}

			// Adjacent Node behind - EH
			if (rowNode > 0)
			{
				rows[rowNum].nodes[rowNode]->adjacentTiles.push_back(rows[rowNum].nodes[rowNode-1]);
			}
			// Adjacent Node in front - EH
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

	// Set current node and the colour for it - EH
	currentNode = mNodes[0];
	currentNode->pNodeObject->tint = DarkMagenta;

	// Tint ndoes adjacent to current - EH
	for (auto node : currentNode->adjacentTiles)
	{
		if (node != currentNode)
		{
			node->pNodeObject->tint = RoyalBlue;
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

// Mainly for music transitions, can be used to update any state changes to overworld from scenes transitioning to it - EH
void OverworldMapScene::Load()
{
	currentNode->pNodeObject->tint = DarkMagenta;

	if (mgr->GetPreviousScene() != Scenes::SettingsPage)
	{
		mgr->FadeInMusic(mBackgroundMus, -1, mgr->fadeTime);
	}
}

void OverworldMapScene::OnHover(RenderObject* rObj)
{
	rObj->tint = Lime;
}

void OverworldMapScene::OnLeave(RenderObject* rObj)
{
	rObj->Untint();
}

// Handles mouse events such as hovering and navigation between scenes - EH
void OverworldMapScene::Update(double dTime, Act act, std::pair<int,int> mousePos)
{
	currentNode->pNodeObject->tint = DarkMagenta;
	
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
			node->pNodeObject->tint = RoyalBlue;
		}
	}
}

// Forces the first four to be different nodes and guarantees the first node is a start node, then it's random from there - EH
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

// Assigns a scene to the appropriate node based on the spritesheet name - EH
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
