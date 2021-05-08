#pragma once
#include "Scene.h"
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

	std::vector<BoardPiece> pBoardPieces;
	RenderObject* pGameBackground;
	RenderObject* pWinnerTextBackground;
	RenderObject* pLeaveButton;
	RenderObject* pRematchButton;

	PlayerInfo mPlayer1;
	PlayerInfo mPlayer2;

	double mTopHeight = 220;
	double mMidHeght = 420;
	double mBottomHeight = 620;

	double mLeftPos = 440;
	double mMiddlePos = 640;
	double mRightPos = 840;

protected:

public:

	NoughtsAndCrossesScene(Interface* mObjMgr);

	// Handles assigning the turn to players, this should decide who can place tokens and interact with the game.
	// Perhaps add a check to the update loop which then ignores the other conditions for performance purposes.
	void ChangeTurn();

	// Will check what symbol the player has, then reveal that RenderObject from the tile that's been clicked
	void DrawSymbol();

	// Will assign one player as 'X' and the other as 'O'
	void AssignSymbol();
	void Load();
	void Update(double dTime, Act act, std::pair<int, int> mousePos) override;

	// Will check board piece vector after symbol has been drawn 
	bool hasWon();
};

