#include "GameManager.h"

using Json = nlohmann::json;
/* Receive until the peer shuts down the connection
do {

	iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
	if (iResult > 0) {
		printf("Bytes received: %d\n", iResult);

		// Echo the buffer back to the sender
		iSendResult = send(ClientSocket, recvbuf, iResult, 0);
		if (iSendResult == SOCKET_ERROR) {
			printf("send failed with error: %d\n", WSAGetLastError());
			closesocket(ClientSocket);
			WSACleanup();
		}
		printf("Bytes sent: %d\n", iSendResult);
	}
	else if (iResult == 0)
		printf("Connection closing...\n");
	else {
		printf("recv failed with error: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
	}
	
	// shutdown the connection since we're done
	iResult = shutdown(ClientSocket, SD_SEND);
		if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();

	}
} while (iResult > 0); */
/*  // Receive until the peer closes the connection
    do {

        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0)
            printf("Bytes received: %d\n", iResult);
        else if (iResult == 0)
            printf("Connection closed\n");
        else
            printf("recv failed with error: %d\n", WSAGetLastError());

    } while (iResult > 0);

    // cleanup*/
// Host flag determines whether game is sending or receiving, usedSocket is the relevant socket to the host or client
// Host needs to send the data from it's interaction and then wait to receive, client needs to do the opposite
void GameManager::Run(bool isHost, SOCKET usedSocket)
{
	//scale texture later
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
	Act act;

	// Socket prep code
	bool hostFlag = isHost;
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
				SDL_SetRenderDrawColor(mRnd, 0x00, 0x00, 0x00, 0x00);
				int temp = act;
				char test = static_cast<char>(temp);
				char* balls = &test;
				std::pair<int, int> coords = std::make_pair(x, y);
				SDL_SetRenderTarget(mRnd, NULL);
				if (isHost == true)
				{
					send(usedSocket,(char*)&temp, sizeof(int), 0);
					send(usedSocket, (char*)&x, sizeof(x), 0);
					send(usedSocket, (char*)&y, sizeof(y), 0);
					if (act == Act::Click)
					{
						isHost = !isHost;
					}
					scenes[mCScene]->SceneUpdate(delta, act, std::make_pair(x, y));
					scenes[mCScene]->Draw(mRnd);
				}
				else
				{
					int n = 0;
					
					int info = recv(usedSocket, (char*)&n, sizeof(int), 0);
					int action = n;
					Act recvAct = static_cast<Act>(n);

					int xInfo = recv(usedSocket, (char*)&n, sizeof(x), 0);
					int xVal = n;
					int yInfo = recv(usedSocket, (char*)&n, sizeof(y), 0);
					int yVal = n;

					if (recvAct == Act::Click)
					{
						std::cout << recvAct;
						isHost = !isHost;
					}
					scenes[mCScene]->SceneUpdate(delta, recvAct, std::make_pair(xVal, yVal));
					scenes[mCScene]->Draw(mRnd);
				}


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
bool GameManager::Init()
{
	Create_Window();
	mInterface.StoreWindow(mWnd);
	SetUp();
	
	mMainMenuSceneInstance = new MainMenuScene(&mInterface);
	scenes.push_back(mMainMenuSceneInstance); // 0

	mNoughtsAndCrossesSceneInstance = new NoughtsAndCrossesScene(&mInterface);
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
