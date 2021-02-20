#include "OverworldMapScene.h"
#include "json.hpp"
#include <fstream>

using jsonf = nlohmann::json;
static std::random_device rd;
static std::mt19937 random_number_engine(rd());
RenderObject* saveButton;
int seed = 15;
struct new_Node
{
	new_Node(RenderObject* obj, bool shop, int seed) :obj(obj), shop(shop), seed(seed)
	{

	}
	std::vector<new_Node*> adjacentNodes;
	RenderObject* obj;
	bool shop = false;
	int seed = 0;
};
new_Node* boss = nullptr;
std::vector<new_Node> map;

int RandomNumberGenerator(int min, int max)
{
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(random_number_engine);
}
void OverworldMapScene::SaveFile()
{

	std::ofstream file("Savedata.Json");
	nlohmann::json characters;
	for (auto i : mgr->GetPlayer()->GetParty())
	{
		characters.push_back({ {"Portrait", i->GetPortraitName()}, {"Object", i->GetObjName()}, {"Name", i->GetClassName(i->GetStats().cClass)}, {"Class", i->GetStats().cClass}, {"Level", i->GetLevel()},
							   {"Experience", i->GetStats().experience}, {"Dead", i->GetDeadStatus()}, 
								{ "Health", i->GetStats().health}, {"Strength", i->GetStats().strength},{"Intelligence", i->GetStats().intelligence},{"Agility", i->GetStats().agility} });
	}
		
	nlohmann::json j;
	j["Saves"]["Save"]["Seed"] = mgr->GetSeed();
	j["Saves"]["Save"]["Gold"] = mgr->GetPlayer()->GetGold();
	j["Saves"]["Save"]["Characters"] = characters;
	j["Saves"]["Save"]["CurrentNode"] = currentNode;

	file << j;
}
OverworldMapScene::OverworldMapScene(Interface* mObjMgr) : Scene(mObjMgr)
{
	pOverworld = AddObject("overworldObj", 640, 360, Map);
	pLegend = AddObject("legendObj", 1190, 180, UI);
	pLegend->SetScale({ 0.9, 0.9 });
	pArmyViewerButton = AddObject("armyViewerButtonObj", 200, 700, UI);
	pLegendButton = AddObject("legendButtonObj", 1070, 700, UI);
	pSettingsButton = AddObject("settingsBtnObj", 780, 700, UI);
	pMenuButton = AddObject("menuButtonObj", 490, 700, UI);

	mOverworldButtons.push_back(pArmyViewerButton);
	mOverworldButtons.push_back(pLegendButton);
	mOverworldButtons.push_back(pSettingsButton);
	mOverworldButtons.push_back(pMenuButton);

	mBackgroundMus = Mix_LoadMUS("Assets/Music/Overworld.mp3");
	
	Init();
	//LoadNodes();
}
double uniform() 
{
	return (double)rand() / RAND_MAX;
}
void OverworldMapScene::LoadNodes()
{
	for (auto i : mLayers[Game])
	{
		delete i;
	}

	mLayers[Game].clear();
	map.clear();
	
	seed = mgr->GetSeed();

	if(seed == 0)
	for (int i = 1; i < 4; i++)
	{
		seed += std::pow((rand() % 100),i);
	}

	std::pair<int, int> center = std::make_pair(640, 360);
	int squaresize = 350;

	srand(seed);
	SaveFile();

	const double PI = 3.14159265358979732384626433832795;
	double m_radius = 300;

	std::vector< std::pair<double, double>> points;
	points.push_back(center);

	for (int i = 0; i < 300; i++)
	{
		double theta = 2 * 3.14159265358979323846264 * uniform();
		double r = sqrt(uniform());

		std::pair<double, double> point = std::make_pair(
			center.first + r * m_radius * cos(theta),
			center.second + r * m_radius * sin(theta));
		
		bool allow = true;

		for (auto p : points)
			if (!(std::abs(p.first - point.first) > 15 && std::abs(p.second - point.second) > 10))
				allow = false;
				
			if(allow)
				points.push_back(point);		
	};

	int i = 0;	

	points.erase(points.begin());

	int shopamount = 0;

	for (auto i : points)
	{
		bool shop = false;
		if (rand() % 6 == 5 && shopamount < 5)
		{
			shopamount++;
			shop = true;
			map.push_back(new_Node(AddObject("shopNodeObj", i.first, i.second, Game), shop, std::rand() % 100 + 10));
		}
		else
		{
			map.push_back(new_Node(AddObject("nodeObj", i.first, i.second, Game), shop, std::rand() % 100 + 10));
		}
	}

	map.push_back(new_Node(AddObject("battleNodeObj", center.first, center.second, Game), false, 0));
	boss = &map.back();

	for (auto &i : map)
	{
		int adjacentCount = 3;

		while (i.adjacentNodes.size() < adjacentCount)
		{
			int lowestDistance = INT_MAX;
			new_Node* node = nullptr;

			for (auto& n : map)
			{
				auto ind = std::find_if(i.adjacentNodes.begin(), i.adjacentNodes.end(), [n](new_Node* nod) {return n.obj == nod->obj; });
				int range = std::abs(i.obj->GetPos().first - n.obj->GetPos().first) + std::abs(i.obj->GetPos().second - n.obj->GetPos().second);

				if (i.obj != n.obj && range < lowestDistance && ind == i.adjacentNodes.end())
				{
					node = &n;
					lowestDistance = range;
				}			
			}

			if (node == nullptr)
			{
				std::cout << "ERROR cant find node!";
				break;
			}
			else
			{
				i.adjacentNodes.push_back(node);
				node->adjacentNodes.push_back(&i);
			}
		}
	}		
}


void OverworldMapScene::LoadNodes(int loadedseed) 
{
	seed = loadedseed;

	for (auto i : mLayers[Game])
	{
		delete i;
	}

	mLayers[Game].clear();

	std::pair<int, int> center = std::make_pair(640, 360);
	int squaresize = 350;

	srand(seed);

	const double PI = 3.14159265358979732384626433832795;
	double m_radius = 350;

	std::vector< std::pair<double, double>> points;

	points.push_back(center);
	for (int i = 0; i < 300; i++)
	{
		double theta = 2 * 3.14159265358979323846264 * uniform();
		double r = sqrt(uniform());

		std::pair<double, double> point = std::make_pair(
			center.first + r * m_radius * cos(theta),
			center.second + r * m_radius * sin(theta));

		bool allow = true;

		for (auto p : points)
		{
			if (!(std::abs(p.first - point.first) > 15 && std::abs(p.second - point.second) > 15))
			{
				allow = false;
			}
		}

		if (allow)
		{
			points.push_back(point);
		}

	};

	int i = 0;

	for (auto i : points)
	{
		map.push_back(new_Node(AddObject("nodeObj", i.first, i.second, Game), false, std::rand() % 100 + 10));
	}

	for (auto& i : map)
	{
		int adjacentCount = 3;

		while (i.adjacentNodes.size() < adjacentCount)
		{
			int lowestDistance = INT_MAX;
			new_Node* node = nullptr;

			for (auto& n : map)
			{
				auto ind = std::find_if(i.adjacentNodes.begin(), i.adjacentNodes.end(), [n](new_Node* nod) {return n.obj == nod->obj; });
				int range = std::abs(i.obj->GetPos().first - n.obj->GetPos().first) + std::abs(i.obj->GetPos().second - n.obj->GetPos().second);

				if (i.obj != n.obj && range < lowestDistance && ind == i.adjacentNodes.end())
				{
					node = &n;
					lowestDistance = range;
				}

			}

			if (node == nullptr)
			{
				std::cout << "ERROR cant find node!";
				break;
			}
			else
			{
				i.adjacentNodes.push_back(node);
				node->adjacentNodes.push_back(&i);
			}
		}
	}
}

void OverworldMapScene::ShowLegend()
{
	pLegend->SetVisible(true);
	legendOn = true;

	mLegend.mNormalNode = AddObject("nodeObj", 1150, 150, UI);
	mLegend.mNormalNode->Tint({ 255,0,0 });
	mLegend.mHoveredNode = AddObject("nodeObj", 1230, 150, UI);
	mLegend.mHoveredNode->Tint({ 0,0,255 });

	mLegend.mShopNode = AddObject("shopNodeObj", 1150, 230, UI);
	mLegend.mShopNode->Tint({ 255,0,0 });
	mLegend.mHoveredShop = AddObject("shopNodeObj", 1230, 230, UI);
	mLegend.mHoveredShop->Tint({ 0,0,255 });

	mLegend.mBossNode = AddObject("battleNodeObj", 1150, 300, UI);
	mLegend.mBossNode->Tint({ 255,0,0 });
	mLegend.mHoveredBoss = AddObject("battleNodeObj", 1230, 300, UI);
	mLegend.mHoveredBoss->Tint({ 0,0,255 });

	mLegend.mLegendObjects.push_back(mLegend.mNormalNode);
	mLegend.mLegendObjects.push_back(mLegend.mHoveredNode);
	mLegend.mLegendObjects.push_back(mLegend.mShopNode);
	mLegend.mLegendObjects.push_back(mLegend.mHoveredShop);
	mLegend.mLegendObjects.push_back(mLegend.mBossNode);
	mLegend.mLegendObjects.push_back(mLegend.mHoveredBoss);

	mSceneText.clear();
	
	for (auto object : mLegend.mLegendObjects)
	{
		object->SetVisible(true);
	}
	
	mLegend.mHeaderText.text = "LEGEND";
	mLegend.mHeaderText.textColor = Black;
	mLegend.mHeaderText.pos = { 1190, 45 };
	mLegend.mHeaderText.SetTextScale(120, 35);

	mLegend.mCurrentLabel.text = "CURRENT";
	mLegend.mCurrentLabel.textColor = Black;
	mLegend.mCurrentLabel.pos = { 1150, 85 };
	mLegend.mCurrentLabel.SetTextScale(50, 30);

	mLegend.mAdjacentLabel.text = "ADJACENT";
	mLegend.mAdjacentLabel.textColor = Black;
	mLegend.mAdjacentLabel.pos = { 1225, 85 };
	mLegend.mAdjacentLabel.SetTextScale(60, 30);

	mLegend.mStandardNodeLabel.text = "STANDARD";
	mLegend.mStandardNodeLabel.textColor = Black;
	mLegend.mStandardNodeLabel.pos = { 1190, 115 };
	mLegend.mStandardNodeLabel.SetTextScale(60, 30);

	mLegend.mShopNodeLabel.text = "SHOP";
	mLegend.mShopNodeLabel.textColor = Black;
	mLegend.mShopNodeLabel.pos = { 1190, 195 };
	mLegend.mShopNodeLabel.SetTextScale(60, 30);

	mLegend.mBossNodeLabel.text = "BOSS";
	mLegend.mBossNodeLabel.textColor = Black;
	mLegend.mBossNodeLabel.pos = { 1190, 265 };
	mLegend.mBossNodeLabel.SetTextScale(60, 30);


	mLegend.mInstructionText.text = "Click node to travel";
	mLegend.mInstructionText.textColor = Black;
	mLegend.mInstructionText.pos = { 1190, 340 };
	mLegend.mInstructionText.SetTextScale(140, 40);

	mSceneText.push_back(&mLegend.mHeaderText);
	mSceneText.push_back(&mLegend.mCurrentLabel);
	mSceneText.push_back(&mLegend.mAdjacentLabel);
	mSceneText.push_back(&mLegend.mStandardNodeLabel);
	mSceneText.push_back(&mLegend.mShopNodeLabel);
	mSceneText.push_back(&mLegend.mBossNodeLabel);
	mSceneText.push_back(&mLegend.mInstructionText);

}

void OverworldMapScene::HideLegend()
{
	legendOn = false;

	pLegend->SetVisible(false);
	mSceneText.clear();
	for (auto object : mLegend.mLegendObjects)
	{
		object->SetVisible(false);
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
	//currentNode->pNodeObject->tint = DarkMagenta;

	SaveFile();
	
	if (mgr->GetPreviousScene() != Scenes::SettingsPage)
	{
		mgr->FadeInMusic(mBackgroundMus, -1, mgr->fadeTime);
	}

	LoadNodes();

	if (legendOn == true)
	{
		ShowLegend();
	}
	else
	{
		HideLegend();
	}
	
	currentNode = mgr->GetPlayer()->currentNode;
	for (auto i : map[currentNode].adjacentNodes)
		i->obj->tint = { 0,0,255 };
	map[currentNode].obj->tint = { 255,0,0 };
	
}

void OverworldMapScene::OnHover(RenderObject* rObj)
{
	rObj->tint = Lime;
}

void OverworldMapScene::OnLeave(RenderObject* rObj)
{
	rObj->Untint();
}

bool IsCombat()
{
	srand(time(NULL));
	int v = rand() % 10;
	return  v > 6;
}
// Handles mouse events such as hovering and navigation between scenes - EH
void OverworldMapScene::Update(double dTime, Act act, std::pair<int,int> mousePos)
{
	if (act == Act::MouseUpdate)
	{
		int t = 0;
		
			for (auto &i : map)
			{
				if (t != currentNode)
				{
					bool found = (std::find_if(map[currentNode].adjacentNodes.begin(), map[currentNode].adjacentNodes.end(), [i](new_Node* node) {return i.obj == node->obj; }) != map[currentNode].adjacentNodes.end());
					if(!found)
					i.obj->Untint();
				}
				t++;
			}
			t = 0;

			for (auto button : mOverworldButtons)
			{
				if (button->InBounds(mousePos.first, mousePos.second))
				{
					OnHover(button);
				}
				else
				{
					OnLeave(button);
				}
			}
	}

	else if (act == Act::Click)
	{
		if (pMenuButton->InBounds(mousePos.first, mousePos.second))
		{
			mgr->PlaySFX(button_Click_SFX, 0, 1);
			mgr->LoadScene(Scenes::MainMenu);
			mgr->GetPlayer()->GetParty().clear();
			pMenuButton->Untint();
		}

		if (pArmyViewerButton->InBounds(mousePos.first, mousePos.second))
		{
			mgr->PlaySFX(button_Click_SFX, 0, 1);
			mgr->LoadScene(Scenes::Party);
			pArmyViewerButton->Untint();
		}

		if (pSettingsButton->InBounds(mousePos.first, mousePos.second))
		{
			mgr->PlaySFX(button_Click_SFX, 0, 1);
			mgr->LoadScene(Scenes::SettingsPage);
			pSettingsButton->Untint();
		}

		if (pLegendButton->InBounds(mousePos.first, mousePos.second))
		{
			mgr->PlaySFX(button_Click_SFX, 0, 1);
			if (legendOn == true)
			{
				HideLegend();
			}
			else
			{
				ShowLegend();
			}
		}
		else
		{

			int t = 0;
			for (auto &i : map)
			{
				if (t != currentNode)
				{
					bool found = (std::find_if(map[currentNode].adjacentNodes.begin(), map[currentNode].adjacentNodes.end(), [i](new_Node* node) {return i.obj == node->obj; }) != map[currentNode].adjacentNodes.end());
					if (!found)
						i.obj->Untint();
				}

				if (i.obj->InBounds(mousePos.first, mousePos.second))
				{
					if (std::find_if(map[currentNode].adjacentNodes.begin(), map[currentNode].adjacentNodes.end(), [i](new_Node* node) {return i.obj == node->obj; }) != map[currentNode].adjacentNodes.end())
					{
						map[currentNode].obj->Untint();
						for (auto a : map[currentNode].adjacentNodes)
							a->obj->Untint();
						currentNode = t;
						mgr->GetPlayer()->currentNode = currentNode;
						map[currentNode].obj->tint = { 255,0,0 };
						for (auto a : i.adjacentNodes)
							a->obj->tint = { 0,0,255 };
						if (&i == boss)
						{
							mgr->PlaySFX(button_Click_SFX, 0, 1);
							mgr->LoadScene(Scenes::Boss);
						}
						else
						if (i.shop)
						{
							mgr->PlaySFX(shop_Entry_SFX, 0, 1);
							mgr->LoadScene(Scenes::Shops);
						}
						else
						{
							if (IsCombat())
							{
								std::vector<Character*> enemy;

								int number = std::rand() % 4 + 1;

								for (int i = 0; i < number; ++i)
									enemy.push_back(new Character("portrait", "maleObj", " ", UnitClass::NoClass, 0,  std::make_pair(100, 200), false, std::make_pair(20, 20), std::make_pair(10, 10), std::make_pair(10, 10), std::make_pair(10, 10)));

									mgr->LoadCombatScene(enemy, i.seed);
								}
								mgr->PlaySFX(button_Click_SFX, 0, 1);
							}
							mgr->PlaySFX(button_Click_SFX, 0, 1);
						}
					}
				}
				t++;
			}
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
