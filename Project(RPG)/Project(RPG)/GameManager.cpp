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
	SDL_Event ev;
	Act act;
	int x, y;
	bool hostFlag = isHost;
	bRunning = true;
	//std::thread sendThread(&GameManager::SendData, this, &x, &y, &act, &hostFlag, &usedSocket, &mut);
	//std::thread receiveThread(&GameManager::ReceiveData, this, &x, &y, &act, &hostFlag, &usedSocket, &mut);
	std::thread sendReceiveThread(&GameManager::SendOrReceiveData, this, &x, &y, &act, &hostFlag, &usedSocket, &mut, &ev);

	const char* sendbuf = nullptr;
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;
	mInterface.SetMasterVolume(-1, 16, 16);
	float overlayOpacity = 0;

	SDL_Texture* texture = SDL_CreateTexture(mRnd, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1920, 1080);

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
					mut.lock();
					scenes[mCScene]->SceneUpdate(0, act, std::make_pair(x, y));	
					mut.unlock();
					//Sleep(400);
				}
				
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
	
	sendReceiveThread.join();
	//sendThread.join();
	//receiveThread.join();
	Mix_CloseAudio(); // Shuts down and cleans up the whole mixer API. Ensures all music and sfx are disposed of. Mix_Quit doesn't necessarily handle everything. - EH
	SDL_DestroyRenderer(mRnd);
	SDL_DestroyWindow(mWnd);
	//TTF_CloseFont(font);
	SDL_Quit();

	std::cout << "Somebody quit the game or disconnected!" << std::endl;
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
				send(*usedSocket, buffer, DEFAULT_BUFLEN, 0);
				*isSender = false;
				std::cout << "Sender" << std::endl;
				mut->unlock();
			}
		}
	}
}
void GameManager::SendOrReceiveData(int* x, int* y, Act* act, bool* isSender, SOCKET* usedSocket, std::mutex* mut, SDL_Event* ev)
{
	char buffer[DEFAULT_BUFLEN];
	fd_set readFds = { 0 };
	fd_set writeFds = { 0 };
	TIMEVAL tv = { 0 };
	tv.tv_sec = 15;
	DWORD dwTimeoutVal = 500;
	int iSelectReturnStatus = -1;

	while (bRunning)
	{
		
		if (*isSender == true)
		{
			FD_ZERO(&writeFds);
			FD_SET(*usedSocket, &writeFds);

			iSelectReturnStatus = select(*usedSocket + 1, NULL, &writeFds, NULL, &tv);

			if (iSelectReturnStatus == SOCKET_ERROR)
			{
				std::cout << "Cannot write to socket! Select failed with SOCKET_ERROR..." << std::endl;
			}

			// Can write to socket, send will work!
			else if (FD_ISSET(*usedSocket, &writeFds))
			{
				setsockopt(*usedSocket, SOL_SOCKET, SO_SNDTIMEO, (const char*)&dwTimeoutVal, sizeof(dwTimeoutVal));


				int temp = static_cast<int>(*act);

				if (static_cast<Act>(temp) == Act::Click)
				{
					mut->lock();
					std::string stringy = std::to_string(temp) + '/' + std::to_string(*x) + '/' + std::to_string(*y) + '/';
					strcpy_s(buffer, stringy.c_str());
					std::cout << buffer << std::endl;
					int sendInfo = send(*usedSocket, buffer, DEFAULT_BUFLEN, 0);

					// Data transmitted normally
					if (sendInfo > 0)
					{						
						*isSender = false;
						mut->unlock();
						Sleep(400);
					}

					// Graceful disconnect on client side
					else if (sendInfo == 0)
					{
						std::cout << "Client disconnected! (Gracefully)..." << std::endl;
						bRunning = false;
					}

					// Disgraceful disconnection or something has gone wrong with the client!
					else
					{
						std::cout << "No data received, disgraceful disconnection on client side with error: " << WSAGetLastError() << std::endl;
						bRunning = false;
					}
				}		 
			}
			else
			{
				std::cout << "Client idled for too long! Select timed out on send..." << std::endl;
				bRunning = false;
			}
		}
		else
		{
			FD_ZERO(&readFds);
			FD_SET(*usedSocket, &readFds);
			iSelectReturnStatus = select(*usedSocket + 1, &readFds, NULL, NULL, &tv);

			if (iSelectReturnStatus == SOCKET_ERROR)
			{
				std::cout << "Cannot read from socket! Select failed with SOCKET_ERROR..." << std::endl;
			}

			// Can read from socket, receive will work!
			else if(FD_ISSET(*usedSocket, &readFds))
			{
				setsockopt(*usedSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&dwTimeoutVal, sizeof(dwTimeoutVal));
				
				int info = recv(*usedSocket, buffer, DEFAULT_BUFLEN, 0);
				std::cout << "received..." << buffer << std::endl;
				// Received data normally
				if (info > 0)
				{
					
					std::string receivedData(buffer);
					*act = static_cast<Act>(Deserialize(receivedData));
					*x = Deserialize(receivedData);
					*y = Deserialize(receivedData);

					if (*act == Act::Click)
					{
						mut->lock();
						std::cout << std::boolalpha << "hostFlag before: " << *isSender << std::endl;
						scenes[mCScene]->SceneUpdate(0, Act::Click, std::make_pair(*x, *y));
						*isSender = true;
						std::cout << std::boolalpha << "hostFlag after: " << *isSender << std::endl;
						mut->unlock();
						Sleep(400);
					}
				}

				// Graceful disconnection
				else if (info == 0)
				{
					std::cout << "Sender has disconnected (gracefully)..." << std::endl;
					bRunning = false;
				}

				// Disgraceful disconnection or something has gone wrong
				else
				{
					std::cout << "No data received, disgraceful disconnection on server side with error: " << WSAGetLastError() << std::endl;
					bRunning = false;
				}
			}
			else
			{
				std::cout << "Server idled for too long! Select timed out on receive..." << std::endl;
				bRunning = false;
			}
		}
	}
}
void GameManager::ReceiveData(int *x, int *y, Act *act, bool *isSender, SOCKET *usedSocket, std::mutex* mut)
{
	char buffer[DEFAULT_BUFLEN];

	while (bRunning)
	{
		if (*isSender == false)
		{			
			int info = recv(*usedSocket, buffer, DEFAULT_BUFLEN, 0);
			mut->lock();
			std::string receivedData(buffer);
			*act = static_cast<Act>(Deserialize(receivedData));
			*x = Deserialize(receivedData);
			*y = Deserialize(receivedData);

			if (*act == Act::Click)
			{
				std::cout << "Click received!" << std::endl;
				std::cout << std::boolalpha << "hostFlag before: " << *isSender << std::endl;
				scenes[mCScene]->SceneUpdate(0, *act, std::make_pair(*x, *y));
				*isSender = true;
				std::cout << "Receiving" << std::endl;
				std::cout << std::boolalpha << "hostFlag after: " << *isSender << std::endl;			
			}
			mut->unlock();
		}
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
	
	scenes.clear();
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
