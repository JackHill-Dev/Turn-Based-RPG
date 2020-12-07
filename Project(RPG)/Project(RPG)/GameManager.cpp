#include "GameManager.h"
#include "TestScene.h"
bool GameManager::Init()
{
	MainMenuClass* mMenu = new MainMenuClass();
	TestScene* mTest = new TestScene();
	mDb = new Database();
	SetupManagers();


	mScManager->AddScene(mTest);
	mScManager->SetScene(0);
	mInputMgr->CreateKeyBind('a', Act::Jump);
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
			
		
			mScManager->Update(0, Poll(ev.key.keysym.sym));
			break;
		case SDL_MOUSEBUTTONDOWN:
			//auto e = ev.button.button;
			int x, y;
			SDL_GetMouseState(&x, &y);
			mScManager->Select(x,y);

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
	SDL_CreateWindowAndRenderer(500, 500, 0, &mWnd, &mRnd);
	SDL_ShowWindow(mWnd);
	return true;
}

void GameManager::SetupManagers()
{

	mScManager  = new SceneManager();
	mInputMgr   = new InputManager();
	mObjMgr = &ObjectManager::Instance();
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
