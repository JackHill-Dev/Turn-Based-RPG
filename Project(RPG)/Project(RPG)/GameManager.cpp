#include "GameManager.h"
#include "CombatScene.h"


void GameManager::Run()
{
	Act act;
	SDL_Rect r;
	r.w = 500;
	r.h = 500;
	SDL_Texture* texture = SDL_CreateTexture(mRnd, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1280, 720);
	SDL_Event ev;
	unsigned int a = SDL_GetTicks();
	unsigned int b = SDL_GetTicks();
	double delta = 0;
	double deltaTime = 0;
	double cd = 0;
	while (SDL_PollEvent(&ev)|| bRunning )
	{
		a = SDL_GetTicks();
		delta = a - b;

		if (delta > 1000 / 60.0) // 60 fps cap
		{
			//std::cout << "fps: " << 1000 / delta << std::endl;

			b = a;

			int x, y;
			act = Act::Blank;
			if (cd <= 0)
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
			else
				cd -= delta;

			SDL_RenderClear(mRnd);

			SDL_SetRenderTarget(mRnd, texture);
			SDL_SetRenderDrawColor(mRnd, 0x64, 0x00, 0x00, 0x00);
	
			SDL_SetRenderTarget(mRnd, NULL);
			
			currentScene->SceneUpdate(delta, act, std::make_pair(x, y));
			currentScene->Draw(mRnd);
			SDL_RenderPresent(mRnd);
		}





		
		//SDL_Delay(16);
	}
	SDL_DestroyRenderer(mRnd);
	SDL_DestroyWindow(mWnd);
	SDL_Quit();
}
void GameManager::Quit()
{
	bRunning = false;
}
void GameManager::SetScene(int index)
{
	currentScene->Clear(mRnd);
	currentScene = scenes[index];
}
AudioManager* GameManager::GetAudioManager() const
{
	return mAudioMgr;
}

void GameManager::LoadOverworldMapScene()
{
	currentScene->Clear(mRnd);

	OverworldMapScene* ovScene = static_cast<OverworldMapScene*>(scenes[1]);
}

void GameManager::LoadCombatScene(std::vector<Character*> player, std::vector<Character*> enemy)
{
	currentScene->Clear(mRnd);

	CombatScene* scene = static_cast<CombatScene*>(scenes[2]);
	scene->Load(player, enemy);
	currentScene = scene;
}

bool GameManager::CreateWindow()
{
	SDL_CreateWindowAndRenderer(2048, 2048, 0, &mWnd, &mRnd);
	SDL_ShowWindow(mWnd);
	return true;
}
bool GameManager::Init()
{
	
	CreateWindow();
	SetUp();
	//scenes.push_back(new MainMenuClass(this));
	scenes.push_back(new OverworldMapScene(this));
	//scenes.push_back(new CombatScene(this));
	//LoadCombatScene({ new Character("maleObj"),new Character("maleObj"), new Character("maleObj") , new Character("maleObj") }, { new Character("maleObj") });
	SetScene(0);

	return true;
}
bool GameManager::SetUp()
{
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());

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

	std::cout << IMG_GetError();
	return SDL_CreateTextureFromSurface(mRnd, img);
}

RenderObject* GameManager::RequestObject(std::string name)
{

	return objects[name]->Clone();
}