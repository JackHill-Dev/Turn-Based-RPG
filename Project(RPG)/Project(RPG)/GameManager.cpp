#include "GameManager.h"
#include "TestScene.h"
bool GameManager::Init()
{
	MainMenuClass* mMenu = new MainMenuClass();
	TestScene* mTest = new TestScene();
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());

	}
	mDb = new Database();
	SetupManagers();
	InitManagers();

	mMgrs->mSceneMgr->AddScene(mMenu);
	mMgrs->mSceneMgr->AddScene(mTest);
	mMgrs->mSceneMgr->SetScene(0);

	mMgrs->mInputMgr->CreateKeyBind('a', Act::Jump);

	CreateWindow();

	return true;
}

bool GameManager::Running()
{
	return bRunning;
}

void GameManager::Run()
{
	SDL_Surface* screenSurface;
	SDL_Event ev;
	while(Running())
	while (SDL_PollEvent(&ev))
	{
		switch (ev.type)
		{
		case SDL_KEYUP:
			
		
		 	mMgrs->mSceneMgr->Update(0, Poll(ev.key.keysym.sym));
			break;
		case SDL_MOUSEBUTTONDOWN:
			//auto e = ev.button.button;
			int x, y;
			SDL_GetMouseState(&x, &y);
			// TODO: Pass in struct with all managers to reduce amount of arguments being passed
			mMgrs->mSceneMgr->Select(x,y, mMgrs->mSceneMgr, mMgrs->mGameMgr); // With what aaron has said should we pass in a scenemanager pointer into select so i can access it - JP

		}
		
		screenSurface = SDL_GetWindowSurface(mWnd);
		mMgrs->mSceneMgr->Draw(screenSurface);
		SDL_UpdateWindowSurface(mWnd);
		SDL_FreeSurface(screenSurface);
	}

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
	mMgrs = new Managers(); // Instantiate new struct of managers
	mMgrs->mGameMgr = this;
	mMgrs->mObjectMgr = &ObjectManager::Instance();
	mMgrs->mAudioMgr = new AudioManager();
	mMgrs->mSceneMgr = new SceneManager();
	mMgrs->mImportMgr = new ImportManager(mDb);
	mMgrs->mInputMgr = new InputManager();


	//mScManager  = new SceneManager();
	//mInputMgr   = new InputManager();
	//mObjMgr = &ObjectManager::Instance();
	//mAudioMgr = AudioManager::Instance();
}

void GameManager::InitManagers()
{
	mMgrs->mAudioMgr->Init();
	mMgrs->mSceneMgr->Init();
}

Act GameManager::Poll(SDL_Keycode kCode)
{
	return mMgrs->mInputMgr->Call(kCode);

}

InputManager* GameManager::GetInputMgr()
{
	return mMgrs->mInputMgr;
}

void GameManager::Quit()
{
	bRunning = false;
}
