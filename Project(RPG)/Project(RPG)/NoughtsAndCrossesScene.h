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

	std::vector<BoardPiece> mBoardPieces;
	RenderObject* mWinnerTextBackground;
	RenderObject* mLeaveButton;
	RenderObject* mRematchButton;

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

