#include "GameManager.h"

bool GameManager::Init()
{
	MainMenuClass* mMenu = new MainMenuClass();
	mDb = new Database();
	SetupManagers();
	mMenu->AddObject(new RenderObject(mDb->GetSpriteSheet("Male 01-1.png")), UI);
	mScManager->AddScene(mMenu);
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
	mAudioMgr = AudioManager::Instance();
	mImportMgr = new ImportManager(mDb);
	mScManager = new SceneManager();
	mInputMgr =	 new InputManager();
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
