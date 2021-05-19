#include "GameManager.h"

using Json = nlohmann::json;

int Deserialize(std::string &serialString)
{
	int i = 0;
	while (i < serialString.length() && serialString[i] != '/')
	{
		++i;
	}
	if (i < serialString.length())
	{
		std::string toRemove = serialString.substr(0, i);
		i = std::stoi(serialString.substr(0, i));
		serialString.erase(0, toRemove.length() + 1);
	}
	return i;
}
// Host flag determines whether game is sending or receiving, usedSocket is the relevant socket to the host or client
// Host needs to send the data from it's interaction and then wait to receive, client needs to do the opposite
void GameManager::Run(bool isHost, SOCKET usedSocket)
{
	//scale texture later
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
	Act act;
	int x, y;
	bool hostFlag = isHost;
	std::thread sendThread(&GameManager::SendData, this, &x, &y, &act, &hostFlag, &usedSocket, &mut);
	std::thread receiveThread(&GameManager::ReceiveData, this, &x, &y, &act, &hostFlag, &usedSocket, &mut);

	const char* sendbuf = nullptr;
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;
	mInterface.SetMasterVolume(-1, 16, 16);
	float overlayOpacity = 0;

	SDL_Texture* texture = SDL_CreateTexture(mRnd, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1920, 1080);
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
				lastSceneIndex = mCScene;
				LoadScene();
		}
			if (delta > 1000 / 60.0 ) // 60 fps cap
			{
				b = a;
				//mut.lock();
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
				SDL_SetRenderDrawColor(mRnd, 0x00, 0x00, 0x00, 0x00);
				SDL_SetRenderTarget(mRnd, NULL);
				if (hostFlag == true)
				{
					scenes[mCScene]->SceneUpdate(delta, act, std::make_pair(x, y));
				}
					
				//mut.unlock();
					scenes[mCScene]->Draw(mRnd);

				int w, h;

				SDL_GetRendererOutputSize(mRnd, &w, &h);
				float resolutionScaleX = 1 + ((float)w - 1280) / 1280;
				float resolutionScaleY = 1 + ((float)h - 720) / 720;
				SDL_RenderSetScale(mRnd,
					resolutionScaleX,
					resolutionScaleY);
				SDL_RenderPresent(mRnd);
			}
	}
	
	Mix_CloseAudio(); // Shuts down and cleans up the whole mixer API. Ensures all music and sfx are disposed of. Mix_Quit doesn't necessarily handle everything. - EH
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
	for (int i = 0; i < 7; i++)
		Mix_UnregisterAllEffects(i);
	switch (mCScene)
	{
		case Scenes::MainMenu:
		{
			mMainMenuSceneInstance->Load(); 
			break;
		}

		case Scenes::NoughtsAndCrosses:
		{
			mNoughtsAndCrossesSceneInstance->Load();
			break;
		}

		default: std::cout << "Error loading scene!" << std::endl;

	}


}
bool GameManager::Create_Window()
{
	SDL_CreateWindowAndRenderer(1920, 1080, 0, &mWnd, &mRnd);
	SDL_SetWindowResizable(mWnd,SDL_TRUE);
	SDL_ShowWindow(mWnd);
	return true;
}
void GameManager::SendData(int *x, int *y, Act *act, bool *isSender, SOCKET *usedSocket, std::mutex* mut)
{
	char buffer[DEFAULT_BUFLEN];

	while (bRunning)
	{
		if (*isSender == true)
		{
			int temp = static_cast<int>(*act);

			if (static_cast<Act>(temp) == Act::Click)
			{
				mut->lock();

				std::string stringy = std::to_string(temp) + '/' + std::to_string(*x) + '/' + std::to_string(*y) + '/';
				strcpy_s(buffer, stringy.c_str());
				std::cout << send(*usedSocket, buffer, DEFAULT_BUFLEN, 0);
				*isSender = !*isSender;

				mut->unlock();
			}
		}
	}
}
void GameManager::ReceiveData(int *x, int *y, Act *act, bool *isSender, SOCKET *usedSocket, std::mutex* mut)
{
	char buffer[DEFAULT_BUFLEN];

	while (bRunning)
	{
		//mut->lock();

			int info = recv(*usedSocket, buffer, DEFAULT_BUFLEN, 0);
			std::string receivedData(buffer);
			*act = static_cast<Act>(Deserialize(receivedData));
			*x = Deserialize(receivedData);
			*y = Deserialize(receivedData);

			if (*act == Act::Click)
			{
				std::cout << "Received Click Action:" << (int)*act << std::endl;
				std::cout << "Click received!" << std::endl;
				std::cout << std::boolalpha << "hostFlag before: " << *isSender << std::endl;
				*isSender = !*isSender;
				std::cout << std::boolalpha << "hostFlag after: " << *isSender << std::endl;
				scenes[mCScene]->SceneUpdate(0, *act, std::make_pair(*x, *y));
			}

		//mut->unlock();
	}
}
GameManager::~GameManager()
{
	for (auto& obj : objects)
		obj.second = nullptr;

	for (auto& sheet : sheets)
		sheet.second = nullptr;

	for (auto& i : definedSheets)
		delete i.second;
	for (auto& i : definedObjects)
		delete i.second;

	delete mMainMenuSceneInstance;
	mMainMenuSceneInstance = nullptr;

	currentScene = nullptr;

}
bool GameManager::Init(bool isSender)
{
	Create_Window();
	mInterface.StoreWindow(mWnd);
	SetUp();
	
	mMainMenuSceneInstance = new MainMenuScene(&mInterface);
	scenes.push_back(mMainMenuSceneInstance); // 0

	mNoughtsAndCrossesSceneInstance = new NoughtsAndCrossesScene(&mInterface, isSender);
	scenes.push_back(mNoughtsAndCrossesSceneInstance); // 1

	currentScene->Clear(mRnd);
	mInterface.LoadScene(Scenes::NoughtsAndCrosses);

	return true;
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

	return true;
}

SDL_Texture* GameManager::LoadTexture(std::string path)
{

	SDL_Surface* img = IMG_Load((path.c_str()));
	auto e = SDL_CreateTextureFromSurface(mRnd, img);
	SDL_FreeSurface(img);
	//if (IMG_GetError)
	//	throw std::invalid_argument("could not load image at: " + path);
	//std::cout << IMG_GetError() << std::endl;
	return e;
}
