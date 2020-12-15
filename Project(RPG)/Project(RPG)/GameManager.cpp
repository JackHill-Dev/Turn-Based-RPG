#include "GameManager.h"
#include "TestScene.h"
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

	MainMenuClass* mMenu = new MainMenuClass();
	TestScene* mTest = new TestScene();

	mScManager->AddScene(mMenu);
	mScManager->AddScene(mTest);
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
	SDL_Surface* screenSurface;
	SDL_Event ev;
	while(Running())
	while (SDL_PollEvent(&ev))
	{
		switch (ev.type)
		{
		case SDL_KEYUP:
			
		
			mScManager->Update(0, Poll(ev.key.keysym.sym));
			break;
		case SDL_MOUSEBUTTONDOWN:
			//auto e = ev.button.button;
			int x, y;
			SDL_GetMouseState(&x, &y);
			// TODO: Pass in struct with all managers to reduce amount of arguments being passed
			mScManager->Select(x,y, &mMgrs); // With what aaron has said should we pass in a scenemanager pointer into select so i can access it - JP
			break;
		case SDL_WINDOWEVENT_SIZE_CHANGED: std::cout << "Size changed";

		}
		
		screenSurface = SDL_GetWindowSurface(mWnd);
		mScManager->Draw(screenSurface);
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
	mScManager = new SceneManager();
	mInputMgr = new InputManager();
	mObjMgr = &ObjectManager::Instance();
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
