#include "GameManager.h"
#include "TestScene.h"
#include "CombatScene.h"
#include "ShopScene.h"
bool GameManager::Init()
{
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());

	}

	CreateWindow();

	mDb = new Database();
	SetupManagers();
	InitManagers();
	SetupManagersStruct();

	MainMenuScene* mMenu = new MainMenuScene(mObjMgr);
	CombatScene* cS = new CombatScene(mObjMgr);
	ShopScene* shopScene = new ShopScene(mObjMgr);
	mScManager->AddScene(mMenu);
	mScManager->AddScene(shopScene);
	mScManager->SetScene(0);

	mInputMgr->CreateKeyBind('a', Act::Jump);

	return true;
}

bool GameManager::Running()
{
	return bRunning;
}

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
			switch (ev.type)
			{
			case SDL_KEYUP:



				break;
			case SDL_MOUSEBUTTONDOWN:
				//auto e = ev.button.button;

				SDL_GetMouseState(&x, &y);
				if(ev.button.button == SDL_BUTTON_LEFT)
					act = Act::Click;
			
				if (ev.button.button == SDL_BUTTON_RIGHT)
					act = Act::RightClick;

				break;
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&x, &y);
				act = Act::Hover;
				break;
			//case SDL_WINDOWEVENT_SIZE_CHANGED: std::cout << "Size changed";

			}
			SDL_RenderClear(mRnd);

			SDL_SetRenderTarget(mRnd, texture);
			SDL_SetRenderDrawColor(mRnd, 0x64, 0x00, 0x00, 0x00);
			
			//SDL_RenderFillRect(mRnd, &r);
			SDL_SetRenderTarget(mRnd, NULL);
			mScManager->Update(delta, act, std::make_pair(x, y));
			mScManager->Draw(mRnd);
			SDL_RenderPresent(mRnd);
		}





		
		//SDL_Delay(16);
	}
	SDL_DestroyRenderer(mRnd);
	SDL_DestroyWindow(mWnd);
	SDL_Quit();
}



bool GameManager::CreateWindow()
{
	SDL_CreateWindowAndRenderer(1280, 720, 0, &mWnd, &mRnd);
	SDL_ShowWindow(mWnd);
	return true;
}

void GameManager::SetupManagers()
{
	mScManager = new SceneManager();
	mInputMgr = new InputManager();
	mObjMgr = new ObjectManager(mRnd, &mMgrs);
	mAudioMgr = new AudioManager();
}

void GameManager::SetupManagersStruct()
{
	mMgrs.GameMgr = this;
	mMgrs.SceneMgr = mScManager;
	mMgrs.AudioMgr = mAudioMgr;
	mMgrs.ImportMgr = mImportMgr;
	mMgrs.InputMgr = mInputMgr;
	mMgrs.ObjectMgr = mObjMgr;

}

void GameManager::InitManagers()
{
	mAudioMgr->Init();
	mScManager->Init(mRnd);
}

Act GameManager::Poll(SDL_Keycode kCode)
{
	return mInputMgr->Call(kCode);
}

InputManager* GameManager::GetInputMgr()
{
	return mInputMgr;
}

void GameManager::Quit()
{
	bRunning = false;
	
}
