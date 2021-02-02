#include "GameManager.h"
#include "CombatScene.h"
#include "ShopScene.h";
#include "PartyViewerScene.h"
#include "SettingsScene.h"
#include "ClassPickerScene.h"
#include "json.hpp"
#include <fstream>;
#include <istream>
using Json = nlohmann::json;
void GameManager::Run()
{
	//scale texture later
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
	Act act;

	mInterface.SetMasterVolume(-1, 16, 8);


	SDL_Texture* texture = SDL_CreateTexture(mRnd, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, mSettings.w, mSettings.h);
	SDL_Event ev;
	unsigned int a = SDL_GetTicks();
	unsigned int b = SDL_GetTicks();
	double delta = 0;
	double deltaTime = 0;
	int lastSceneIndex = mCScene;
	while ( bRunning )
	{
		a = SDL_GetTicks();
		delta = a - b;
		if (delta > 130)
			delta = 130;
		srand(delta);
		if (mCScene != lastSceneIndex)
		{
			LoadScene();
		}
		lastSceneIndex = mCScene;

		if (delta > 1000 / 60.0) // 60 fps cap
		{
			//std::cout << "fps: " << 1000 / delta << std::endl;

			b = a;

			int x, y;
			act = Act::Blank;
			if (SDL_PollEvent(&ev))
				switch (ev.type)
				{
				case SDL_KEYUP:
					if (ev.button.button == SDL_BUTTON_LEFT)
						act = Act::MouseUp;


					break;
				case SDL_MOUSEBUTTONDOWN:
					//auto e = ev.button.button;
					if (ev.button.button == SDL_BUTTON_LEFT)
						act = Act::Click;
					else
						act = Act::RClick;
					SDL_GetMouseState(&x, &y);

					break;
				case SDL_MOUSEMOTION:
					SDL_GetMouseState(&x, &y);
					act = Act::MouseUpdate;
					break;

				

				
				}
		

			SDL_RenderClear(mRnd);

			SDL_SetRenderTarget(mRnd, texture);
			SDL_SetRenderDrawColor(mRnd, 0x64, 0x00, 0x00, 0x00);
	
			SDL_SetRenderTarget(mRnd, NULL);
		
			scenes[mCScene]->SceneUpdate(delta, act, std::make_pair(x, y));
			scenes[mCScene]->Draw(mRnd);
			SDL_RenderPresent(mRnd);
		
		}

		//SDL_Delay(16);
	}
	Mix_Quit();
	SDL_DestroyRenderer(mRnd);
	SDL_DestroyWindow(mWnd);
	//TTF_CloseFont(font);
	SDL_Quit();
}
void GameManager::Quit()
{
	bRunning = false;
}
void GameManager::LoadScene()
{
	switch (mCScene)
	{
	case Scenes::Combat: combatInstance.first->Load(combatInstance.second); break;
	case Scenes::Shops: mShopSceneInstance->Load(); break;
	case Scenes::Party:  partyViewerInstance->Load(); break;
	case Scenes::InventoryScreen : mInventorySceneInstance->Load(); break;
	}


}
bool GameManager::CreateWindow()
{
	SDL_CreateWindowAndRenderer(mSettings.w, mSettings.h, 0, &mWnd, &mRnd);
	SDL_SetWindowResizable(mWnd,SDL_TRUE);
	SDL_ShowWindow(mWnd);
	return true;
}
bool GameManager::Init()
{
	LoadSettings();
	CreateWindow();
	mInterface.StoreWindow(mWnd);
	SetUp();
	SetupPlayer();
	

	mPlayer.SetGold(1000);

	//mPlayer.SetupParty({ new Character("mageObj", "portrait"), new Character("mageObj", "portrait"), new Character("mageObj", "portrait") });
	mPlayer.SetDeck({new Card(*cards["Slash"]), new Card(*cards["Magic"]), new Card(*cards["Slash"]), new Card(*cards["Magic"]), new Card(*cards["Magic"]), new Card(*cards["Slash"]), new Card(*cards["Slash"]) });

	scenes.push_back(new MainMenuScene(&mInterface));
    scenes.push_back(new OverworldMapScene(&mInterface));
	combatInstance.first = new CombatScene(&mInterface);
	scenes.push_back(combatInstance.first); // 2
	mShopSceneInstance = new ShopScene(&mInterface);
	scenes.push_back(mShopSceneInstance); // 3
	partyViewerInstance = new PartyViewerScene(&mInterface);
	scenes.push_back(partyViewerInstance); // 4
	scenes.push_back(new SettingsScene(&mInterface)); // 5
	scenes.push_back(new ClassPickerScene(&mInterface)); // 6
	mInventorySceneInstance = new InventoryScene(&mInterface);
	scenes.push_back(mInventorySceneInstance); // 7

	//LoadCombatScene({ new Character("maleObj"),new Character("maleObj"), new Character("maleObj") , new Character("maleObj") }, { new Character("maleObj") });
	currentScene->Clear(mRnd);
	currentScene = scenes[0];

	return true;
}
void GameManager::LoadSettings()
{
	std::ifstream ifs("Settings.json");
	if (ifs.is_open())
	{
		Json jf = Json::parse(ifs);
		mSettings.mMasterVolume = jf["Audio"]["master-volume"].get<int>();
		mSettings.w = jf["Display"]["Width"].get<int>();
		mSettings.h = jf["Display"]["Height"].get<int>();
		mSettings.bIsFullScreen = jf["Display"]["fullscreen"].get<bool>();

	}
	ifs.close();
}

void GameManager::SetupPlayer()
{
	mPlayer.SetGold(1000);
	mArmour = Armour("armourObj", 100, 20);
	mPlayer.GetInventory().AddItem(&mArmour);

	mWizard = Character("maleObj", "WizardObj");
	mWarrior = Character("maleObj", "WarriorObj");

	//mPlayer.SetupParty({ &mWizard, new Character("maleObj", "ClericObj"), new Character("maleObj", "RogueObj"), &mWarrior });
}

bool GameManager::SetUp()
{
	if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 4096) < 0)
	{
		std::cout << "Mixer load failed, error: " << Mix_GetError() << std::endl;
	}
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n\n", IMG_GetError());

	}

	if(TTF_Init() < 0) {
		std::cout << "TTF lib not initialised" << TTF_GetError << std::endl;
	}
	//Converts definitions found in GameObjects.h to fully initlised and stored objects

	//Load sheets
	for (auto i : definedSheets)
	{
		sheets[i.first] = i.second;
		sheets[i.first]->SetTexture(LoadTexture(i.second->mFilePath));
	}
	//Add animations to sheets
	for (auto i : definedAnimations)
	{
		for (auto anim : i.second)
		{
			sheets[i.first]->AddAnim(anim.GetName(), anim);
		}
	}
	//Create Object types
	for (auto i : definedObjects)
	{
		objects[i.first] = i.second;
		objects[i.first]->SetTexture(sheets[(objects[i.first]->path)]);
		if (objects[i.first]->GetSheet()->fillScreen)
		{

			float xDif = 1+ (1280 - objects[i.first]->GetSheet()->GetCellSize().first)/ objects[i.first]->GetSheet()->GetCellSize().first;
			float yDif = 1 + (720 - objects[i.first]->GetSheet()->GetCellSize().second) / objects[i.first]->GetSheet()->GetCellSize().second;
			objects[i.first]->SetScale(std::make_pair(xDif,yDif));
		}
		//objects[i.first]->Init(mgrs);
	}

	for (auto i : definedCards)
	{
		CreateCard(&i.second);
	}
	return true;
}

SDL_Texture* GameManager::LoadTexture(std::string path)
{

	SDL_Surface* img = IMG_Load((path.c_str()));
	//if (IMG_GetError)
	//	throw std::invalid_argument("could not load image at: " + path);
	std::cout << IMG_GetError();
	return SDL_CreateTextureFromSurface(mRnd, img);
}


void GameManager::CreateCard(DefinedCard* card)
{

	int imageWidth = 225;
	int imageHeight = 225;


	SDL_Texture* base = SDL_CreateTexture(mRnd, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, sheets["card"]->GetCellSize().first, sheets["card"]->GetCellSize().second);

	SDL_SetRenderTarget(mRnd, base);

	SDL_Rect rect;
	SpriteSheet* obj = sheets["card"];


	SDL_Rect crop;
	crop.x = 0;
	crop.y = 0;
	crop.w = imageWidth;
	crop.h = imageHeight;

	rect.w = imageWidth;
	rect.h = imageHeight;
	rect.x = 0;
	rect.y = 0;

	SDL_RenderCopy(mRnd, sheets[card->picture]->GetTexture(), NULL, &rect);
	SDL_RenderCopy(mRnd, sheets["card"]->GetTexture(), NULL, NULL);


	rect.x = 10;
	rect.y = 2;
	rect.w = 100;
	rect.h = 15;

	obj = new SpriteSheet("", sheets["card"]->GetTextureSize().first, sheets["card"]->GetTextureSize().second, sheets["card"]->GetTextureSize().first, sheets["card"]->GetTextureSize().second, 1);

	obj->SetTexture(base);
	sheets.insert(std::make_pair("cardSheet_"+ std::to_string(cards.size()), obj));

	objects.insert(std::make_pair("cardObj" + std::to_string(cards.size()), new RenderObject("card1")));

	objects["cardObj" + std::to_string(cards.size())]->SetTexture(sheets["cardSheet_" + std::to_string(cards.size())]);

	cards.insert({ card->name, new Card(card->damage, card->name, card->range, "cardObj" + std::to_string(cards.size()), card->animation) });
	SDL_SetRenderTarget(mRnd, NULL);

	//SDL_Texture* fontTexture = (SDL_CreateTextureFromSurface(mRnd, TTF_RenderText_Blended(mFont, card.name , SDL_Color{ 0,0,0 }));;
}

