#include "GameManager.h"
#include "CombatScene.h"
#include "ShopScene.h";
#include "PartyViewerScene.h"
#include "SettingsScene.h"
#include "json.hpp"
#include <fstream>;
#include <istream>
using Json = nlohmann::json;
void GameManager::Run()
{

	Act act;

	mInterface.SetMasterVolume(-1, 1);


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
	if (mCScene == 1)
	{
		combatInstance.first->Load(combatInstance.second);
	}
}
bool GameManager::CreateWindow()
{
	SDL_CreateWindowAndRenderer(mSettings.w, mSettings.h, 0, &mWnd, &mRnd);
	SDL_ShowWindow(mWnd);
	return true;
}
bool GameManager::Init()
{
	LoadSettings();
	CreateWindow();
	mInterface.StoreWindow(mWnd);
	SetUp();

	mPlayer.SetGold(1000);
	mPlayer.SetupParty({ new Character("maleObj", "WizardObj"), new Character("maleObj", "ClericObj"), new Character("maleObj", "RogueObj"), new Character("maleObj", "WarriorObj") });

	scenes.push_back(new MainMenuScene(&mInterface));
    scenes.push_back(new OverworldMapScene(&mInterface));
	combatInstance.first = new CombatScene(&mInterface);
	scenes.push_back(combatInstance.first);
	scenes.push_back(new ShopScene(&mInterface));
	scenes.push_back(new PartyViewerScene(&mInterface));
	scenes.push_back(new SettingsScene(&mInterface));

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
		//objects[i.first]->Init(mgrs);
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

