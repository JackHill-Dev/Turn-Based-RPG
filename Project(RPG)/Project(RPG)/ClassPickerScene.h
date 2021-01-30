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
	UIText mWarriorLabel;
	UIText mRogueLabel;
	UIText mMageLabel;
	UIText mFooterInstruction;

	RenderObject* pBackBtn;
	RenderObject* pWarriorIcon;
	RenderObject* pRogueIcon;
	RenderObject* pMageIcon;
	RenderObject* pScrollBg;

	Mix_Music* bg_Music;
	Mix_Chunk* confirm_SFX;
	Mix_Chunk* back_SFX;

	// This will be to add to the party - Currently going to get it working with 3.
	Player* pPlayer;

protected:

public:

	ClassPickerScene(Interface* mObjMgr);
	void Init();

	void Update(double dTime, Act act, std::pair<int, int> mousePos) override;
};

