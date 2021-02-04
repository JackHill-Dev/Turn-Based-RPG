#pragma once
#include "Character.h"
#include "Scene.h"
#include "Actions.h"
#include <SDL.h>

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

	bool IsFocused = false;
	bool IsWarriorView = false;
	bool IsRogueView = false;
	bool IsMageView = false;

	int PartyCount = 0;
	const int maxPartySize = 3;

protected:

public:

	ClassPickerScene(Interface* mObjMgr);

	void Init();
	void Load();

	void OnHover(RenderObject* rObj);
	void OnLeave(RenderObject* rObj);

	void Update(double dTime, Act act, std::pair<int, int> mousePos) override;

	void SetUpSummaryView();
	void SetUpWarriorView();
	void SetUpRogueView();
	void SetUpMageView();

	void SetUpBackgroundView();
	void SetUpVillagerView();
	void SetUpScholarView();
	void SetUpNobleView();

};

