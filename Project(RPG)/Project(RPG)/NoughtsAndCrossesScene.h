#pragma once
#include "Scene.h"
#include "Actions.h"
#include <SDL.h>

struct PlayerInfo
{
	UIText mPlayerId;
	UIText mWinTally;
	RenderObject* mInfoBackground;
};

struct BoardPiece
{
	RenderObject* mPiece = nullptr;
	RenderObject* mNought = nullptr;
	RenderObject* mCross = nullptr;
	bool bFilledNought = false;
	bool bFilledCross = false;
};

class NoughtsAndCrossesScene : public Scene
{

private:

	UIText mTurnText;
	UIText mWinnerText;

	std::vector<RenderObject*> mBoardPieces;
	RenderObject* mWinnerTextBackground;

protected:

public:


};

