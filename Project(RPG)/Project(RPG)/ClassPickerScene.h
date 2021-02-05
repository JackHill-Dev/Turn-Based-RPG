#pragma once
#include "Character.h"
#include "Scene.h"
#include "Actions.h"
#include <SDL.h>
#include <numeric>

enum CharacterPickerState
{
	ClassView = 0,
	WarriorView = 1,
	RogueView = 2,
	MageView = 3,
	BackgroundView = 4,
	VillagerView = 5,
	ScholarView = 6,
	NobleView = 7,
};

class ClassPickerScene : public Scene
{
private:

	UIText mHeader;
	UIText mHeaderInstruction;
	UIText mFlavourText1;
	UIText mFlavourText2;
	UIText mFlavourText3;
	UIText mFlavourText4;
	UIText mFooterInstruction;

	RenderObject* pBackBtn;
	RenderObject* pRejectBtn;
	RenderObject* pYesBtn;
	RenderObject* pWarriorIcon;
	RenderObject* pRogueIcon;
	RenderObject* pMageIcon;
	RenderObject* pVillagerIcon;
	RenderObject* pScholarIcon;
	RenderObject* pNobleIcon;
	RenderObject* pScrollBg;

	Mix_Music* bg_Music;
	Mix_Chunk* confirm_SFX;
	Mix_Chunk* back_SFX;
	std::vector<Character*> mCharacters;
	std::vector<int> currentPartyGold;

	CharacterPickerState currentState;
	CharacterPickerState previousState;

	bool isFocused = false;

	int PartyCount = 0;

	const int mVillagerGold = 50;
	const int mScholarGold = 100;
	const int mNobleGold = 150;
	const int maxPartySize = 3;

protected:

public:

	ClassPickerScene(Interface* mObjMgr);

	void Init();
	void Load();

	void OnHover(RenderObject* rObj);
	void OnLeave(RenderObject* rObj);

	void Update(double dTime, Act act, std::pair<int, int> mousePos) override;

	void SetUpClassView(CharacterPickerState originState);
	void SetUpWarriorView(CharacterPickerState originState);
	void SetUpRogueView(CharacterPickerState originState);
	void SetUpMageView(CharacterPickerState originState);

	void SetUpBackgroundView(CharacterPickerState originState);
	void SetUpVillagerView(CharacterPickerState originState);
	void SetUpScholarView(CharacterPickerState originState);
	void SetUpNobleView(CharacterPickerState originState);

};

