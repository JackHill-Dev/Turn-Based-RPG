#include "NoughtsAndCrossesScene.h"



NoughtsAndCrossesScene::NoughtsAndCrossesScene(Interface* mObjMgr) : Scene(mObjMgr)
{

    pGameBackground = AddObject("ChalkBoardObj", 640, 360, Layer::Background);
    BoardPiece TopLeft;
    TopLeft.mPiece = AddObject("BoardPieceObj", mLeftPos , mTopHeight, Layer::Game);
    BoardPiece TopCentre;
    TopCentre.mPiece = AddObject("BoardPieceObj", mMiddlePos, mTopHeight, Layer::Game);
    BoardPiece TopRight;
    TopRight.mPiece = AddObject("BoardPieceObj", mRightPos, mTopHeight, Layer::Game);
    BoardPiece MidLeft;
    MidLeft.mPiece = AddObject("BoardPieceObj", mLeftPos, mMidHeght, Layer::Game);
    BoardPiece MidCentre;
    MidCentre.mPiece = AddObject("BoardPieceObj", mMiddlePos, mMidHeght, Layer::Game);
    BoardPiece MidRight;
    MidRight.mPiece = AddObject("BoardPieceObj", mRightPos, mMidHeght, Layer::Game);
    BoardPiece BottomLeft;
    BottomLeft.mPiece = AddObject("BoardPieceObj", mLeftPos, mBottomHeight, Layer::Game);
    BoardPiece BottomCentre;
    BottomCentre.mPiece = AddObject("BoardPieceObj", mMiddlePos, mBottomHeight, Layer::Game);
    BoardPiece BottomRight;
    BottomLeft.mPiece = AddObject("BoardPieceObj", mRightPos, mBottomHeight, Layer::Game);

    pLeaveButton = AddObject("LeaveGameButtonObj", 200, 900, Layer::UI);
    pWinnerTextBackground = AddObject("TurnAndGameInfoObj", 640, 65, Layer::UI);
    pWinnerTextBackground->SetScale(std::make_pair(0.8,0.8));

    mPlayer1.mInfoBackground = AddObject("PlayerInfoObj", 150, 380, Layer::UI);
    mPlayer1.mInfoBackground->SetScale({ 0.8,0.8 });
    mPlayer2.mInfoBackground = AddObject("PlayerInfoObj", 1130, 380, Layer::UI);
    mPlayer2.mInfoBackground->SetScale({ 0.8,0.8 });
}

void NoughtsAndCrossesScene::Load()
{

}

void NoughtsAndCrossesScene::ChangeTurn()
{
}

void NoughtsAndCrossesScene::DrawSymbol()
{
}

void NoughtsAndCrossesScene::AssignSymbol()
{
}

bool NoughtsAndCrossesScene::hasWon()
{
    return false;
}



void NoughtsAndCrossesScene::Update(double dTime, Act act, std::pair<int, int> mousePos)
{
}
