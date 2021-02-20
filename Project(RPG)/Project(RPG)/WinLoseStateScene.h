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
	RenderObject* pGameClearBanner = nullptr;
	RenderObject* pLevelUpOverlay = nullptr;
	RenderObject* pConfirmButton = nullptr;
	RenderObject* pContinueButton = nullptr;
	RenderObject* pRejectButton = nullptr;
	RenderObject* pQuitButton = nullptr;
	RenderObject* pMenuButton = nullptr;
	RenderObject* pLeftSprite = nullptr;
	RenderObject* pCentreSprite = nullptr;
	RenderObject* pRightSprite = nullptr;
	RenderObject* StrengthButton = nullptr;
	RenderObject* AgilityButton = nullptr;
	RenderObject* IntelligenceButton = nullptr;

	Mix_Music* Victory_Music = nullptr;
	Mix_Music* Defeat_Music = nullptr;

	Mix_Chunk* Victory_Sfx = nullptr;
	Mix_Chunk* Defeat_Sfx = nullptr;
	Mix_Chunk* Button_Sfx = nullptr;
	Mix_Chunk* Error_Sfx = nullptr;

	SDL_Color Lime = SDL_Color{ 0, 255, 0 };
	SDL_Color DimGray = SDL_Color{ 105,105,105 };
	SDL_Color Gold = SDL_Color{ 255,215,0 };

	PlayerCharacter* firstCharacter = nullptr;
	PlayerCharacter* SecondCharacter  = nullptr;
	PlayerCharacter* ThirdCharacter   = nullptr;
	PlayerCharacter* pTargetCharacter =	nullptr;

	std::vector<std::string> names;
	std::vector<RenderObject*> pAllButtons;
	std::vector<RenderObject*> pStatButtons;
	std::vector<PlayerCharacter*> pCharacters;

	int statPoints = 0;
	int strPoints = 0;
	int agiPoints = 0;
	int intPoints = 0;
	int dividedXp = 0;
	
protected:

public:

	WinLoseStateScene(Interface* mObjMgr);

	void SetUpButtons();
	void PickState();
	void Load();
	void Update(double dTime, Act act, std::pair<int, int> mousePos) override;

	void OnHover(RenderObject* rObj);
	void OnLeave(RenderObject* rObj);

	void SetUpWinState();
	void SetUpLoseState();
	void SetUpLevelUpState(PlayerCharacter* &pc);
	void SetUpGameClearState();

};

