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
	bool bFilled = false;
};

struct ScoreBoard
{
	RenderObject* pWinnerTextBackground;
	UIText mTurnText;
	UIText mWinnerText;
};

class NoughtsAndCrossesScene : public Scene
{

private:

	std::vector<BoardPiece> pBoardPieces;

	BoardPiece TopLeft;
	BoardPiece TopCentre;
	BoardPiece TopRight;
	BoardPiece MidLeft;
	BoardPiece MidCentre;
	BoardPiece MidRight;
	BoardPiece BottomLeft;
	BoardPiece BottomCentre;
	BoardPiece BottomRight;

	RenderObject* pGameBackground;

	RenderObject* pLeaveButton;
	RenderObject* pRematchButton;

	PlayerInfo mPlayer1;
	PlayerInfo mPlayer2;
	ScoreBoard mBoard;

	double mTopHeight = 220;
	double mMidHeight = 420;
	double mBottomHeight = 620;

	double mLeftPos = 440;
	double mMiddlePos = 640;
	double mRightPos = 840;

	// true = nought, false = cross (So host will set it to true and client will have false)
	bool mPlayerTurn = true; 
	SDL_Color Black = SDL_Color{ 0,0,0 };
	SDL_Color Lime = SDL_Color{ 0,255,0 };
	SDL_Color Gray = SDL_Color{ 128,128,128 };

protected:

public:

	NoughtsAndCrossesScene(Interface* mObjMgr);

	// Handles assigning the turn to players, this should decide who can place tokens and interact with the game.
	// Perhaps add a check to the update loop which then ignores the other conditions for performance purposes.
	void ChangeTurn();

	// Will check what symbol the player has, then reveal that RenderObject from the tile that's been clicked
	void DrawSymbol(BoardPiece& selectedPiece);

	// Will assign one player as 'X' and the other as 'O'
	void AssignSymbol();
	void Load();
	void SetUpBoardPieces();
	void SetUpUI();
	void ResolveGame();
	void ResetGame();
	void Update(double dTime, Act act, std::pair<int, int> mousePos) override;

	// Will check board piece vector after symbol has been drawn 
	bool hasWon();
};

