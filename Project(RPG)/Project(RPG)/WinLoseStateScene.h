#pragma once
#include "Scene.h"
#include "Actions.h"
#include "Character.h"
#include <SDL.h>


struct PlayerCharacter
{
	RenderObject* rObj;
	Character* pCharacter;
};

class WinLoseStateScene : public Scene
{
private:

	UIText mHeader;
	UIText mHeaderInstruction;
	UIText mFlavourText1;
	UIText mFlavourText2;
	UIText mFlavourText3;
	UIText mFlavourText4;
	UIText mFlavourText5;
	UIText mFlavourText6;
	UIText mFooterInstruction;

	RenderObject* pBackground = nullptr;
	RenderObject* pLevelUpOverlay = nullptr;
	RenderObject* pConfirmButton = nullptr;
	RenderObject* pRejectButton = nullptr;
	RenderObject* pQuitButton = nullptr;
	RenderObject* pMenuButton = nullptr;
	RenderObject* pLeftSprite = nullptr;
	RenderObject* pCentreSprite = nullptr;
	RenderObject* pRightSprite = nullptr;

	Mix_Music* Victory_Music = nullptr;
	Mix_Music* Defeat_Music = nullptr;

	Mix_Chunk* Victory_Sfx = nullptr;
	Mix_Chunk* Defeat_Sfx = nullptr;
	Mix_Chunk* Button_Sfx = nullptr;

	SDL_Color Lime = SDL_Color{ 0, 255, 0 };
	SDL_Color DimGray = SDL_Color{ 105,105,105 };

	std::vector<std::string> names;
	std::vector<PlayerCharacter*> pCharacters;
	



protected:

public:

	WinLoseStateScene(Interface* mObjMgr);

	void Init();
	void Load();
	void Update(double dTime, Act act, std::pair<int, int> mousePos) override;

	void OnHover(RenderObject* rObj);
	void OnLeave(RenderObject* rObj);

	void SetUpWinState();
	void SetUpLoseState();

};

