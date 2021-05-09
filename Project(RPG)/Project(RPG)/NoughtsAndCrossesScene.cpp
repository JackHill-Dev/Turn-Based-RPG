#include "NoughtsAndCrossesScene.h"



NoughtsAndCrossesScene::NoughtsAndCrossesScene(Interface* mObjMgr) : Scene(mObjMgr)
{

    pGameBackground = AddObject("ChalkBoardObj", 640, 360, Layer::Background);
    pLeaveButton = AddObject("LeaveGameButtonObj", 145, 650, Layer::UI);
    pRematchButton = AddObject("RematchButtonObj", 1130, 650, Layer::UI);
    pRematchButton->SetScale(std::make_pair<float, float>(0.8, 0.65));
    pRematchButton->SetVisible(false);
   
}

void NoughtsAndCrossesScene::Load()
{
    SetUpUI();
    SetUpBoardPieces();
}

void NoughtsAndCrossesScene::SetUpBoardPieces()
{
    BoardPiece TopLeft;
    TopLeft.mPiece = AddObject("BoardPieceObj", mLeftPos, mTopHeight, Layer::Game);
    TopLeft.mNought = AddObject("NoughtObj", mLeftPos, mTopHeight, Layer::UI);
    TopLeft.mNought->SetVisible(false);
    TopLeft.mCross = AddObject("CrossObj", mLeftPos, mTopHeight, Layer::UI);
    TopLeft.mCross->SetVisible(false);

    BoardPiece TopCentre;
    TopCentre.mPiece = AddObject("BoardPieceObj", mMiddlePos, mTopHeight, Layer::Game);
    TopCentre.mNought = AddObject("NoughtObj", mMiddlePos, mTopHeight, Layer::UI);
    TopCentre.mNought->SetVisible(false);
    TopCentre.mCross = AddObject("CrossObj", mMiddlePos, mTopHeight, Layer::UI);
    TopCentre.mCross->SetVisible(false);

    BoardPiece TopRight;
    TopRight.mPiece = AddObject("BoardPieceObj", mRightPos, mTopHeight, Layer::Game);
    TopRight.mNought = AddObject("NoughtObj", mRightPos, mTopHeight, Layer::UI);
    TopRight.mNought->SetVisible(false);
    TopRight.mCross = AddObject("CrossObj", mRightPos, mTopHeight, Layer::UI);
    TopRight.mCross->SetVisible(false);

    BoardPiece MidLeft;
    MidLeft.mPiece = AddObject("BoardPieceObj", mLeftPos, mMidHeight, Layer::Game);
    MidLeft.mNought = AddObject("NoughtObj", mLeftPos, mMidHeight, Layer::UI);
    MidLeft.mNought->SetVisible(false);
    MidLeft.mCross = AddObject("CrossObj", mLeftPos, mMidHeight, Layer::UI);
    MidLeft.mCross->SetVisible(false);

    BoardPiece MidCentre;
    MidCentre.mPiece = AddObject("BoardPieceObj", mMiddlePos, mMidHeight, Layer::Game);
    MidCentre.mNought = AddObject("NoughtObj", mMiddlePos, mMidHeight, Layer::UI);
    MidCentre.mNought->SetVisible(false);
    MidCentre.mCross = AddObject("CrossObj", mMiddlePos, mMidHeight, Layer::UI);
    MidCentre.mCross->SetVisible(false);

    BoardPiece MidRight;
    MidRight.mPiece = AddObject("BoardPieceObj", mRightPos, mMidHeight, Layer::Game);
    MidRight.mNought = AddObject("NoughtObj", mRightPos, mMidHeight, Layer::UI);
    MidRight.mNought->SetVisible(false);
    MidRight.mCross = AddObject("CrossObj", mRightPos, mMidHeight, Layer::UI);
    MidRight.mCross->SetVisible(false);

    BoardPiece BottomLeft;
    BottomLeft.mPiece = AddObject("BoardPieceObj", mLeftPos, mBottomHeight, Layer::Game);
    BottomLeft.mNought = AddObject("NoughtObj", mLeftPos, mBottomHeight, Layer::UI);
    BottomLeft.mNought->SetVisible(false);
    BottomLeft.mCross = AddObject("CrossObj", mLeftPos, mBottomHeight, Layer::UI);
    BottomLeft.mCross->SetVisible(false);

    BoardPiece BottomCentre;
    BottomCentre.mPiece = AddObject("BoardPieceObj", mMiddlePos, mBottomHeight, Layer::Game);
    BottomCentre.mNought = AddObject("NoughtObj", mMiddlePos, mBottomHeight, Layer::UI);
    BottomCentre.mNought->SetVisible(false);
    BottomCentre.mCross = AddObject("CrossObj", mMiddlePos, mBottomHeight, Layer::UI);
    BottomCentre.mCross->SetVisible(false);

    BoardPiece BottomRight;
    BottomRight.mPiece = AddObject("BoardPieceObj", mRightPos, mBottomHeight, Layer::Game);
    BottomRight.mNought = AddObject("NoughtObj", mRightPos, mBottomHeight, Layer::UI);
    BottomRight.mNought->SetVisible(false);
    BottomRight.mCross = AddObject("CrossObj", mRightPos, mBottomHeight, Layer::UI);
    BottomRight.mCross->SetVisible(false);

    pBoardPieces.push_back(TopLeft);
    pBoardPieces.push_back(TopCentre);
    pBoardPieces.push_back(TopRight);
    pBoardPieces.push_back(MidLeft);
    pBoardPieces.push_back(MidCentre);
    pBoardPieces.push_back(MidRight);
    pBoardPieces.push_back(BottomLeft);
    pBoardPieces.push_back(BottomCentre);
    pBoardPieces.push_back(BottomRight);
}

void NoughtsAndCrossesScene::SetUpUI()
{
    mBoard.pWinnerTextBackground = AddObject("TurnAndGameInfoObj", 640, 65, Layer::UI);
    mBoard.pWinnerTextBackground->SetScale(std::make_pair(0.8, 0.8));
    if (mPlayerTurn == true)
    {
        mBoard.mTurnText.text = "Current Turn: Player O";
        mBoard.mTurnText.textColor = Black;
        mBoard.mTurnText.SetTextScale(250, 100);
        mBoard.mTurnText.pos = { 640, 65 };
    }
    else
    {
        mBoard.mTurnText.text = "Current Turn: Player X";
        mBoard.mTurnText.textColor = Black;
        mBoard.mTurnText.SetTextScale(250, 100);
        mBoard.mTurnText.pos = { 640, 65 };
    }

    mPlayer1.mInfoBackground = AddObject("PlayerInfoObj", 150, 380, Layer::UI);
    mPlayer1.mInfoBackground->SetScale({ 0.8,0.8 });
    mPlayer1.mPlayerId.text = "Player: O";
    mPlayer1.mPlayerId.textColor = Black;
    mPlayer1.mPlayerId.SetTextScale(150, 80);
    mPlayer1.mPlayerId.pos = { 150, 200 };
    mPlayer1.mWinTally.text = "Wins: " + std::to_string(mgr->GetPlayer()->winTally);
    mPlayer1.mWinTally.textColor = Black;
    mPlayer1.mWinTally.SetTextScale(150, 80);
    mPlayer1.mWinTally.pos = { 150, 290 };
    mPlayer2.mInfoBackground = AddObject("PlayerInfoObj", 1130, 380, Layer::UI);
    mPlayer2.mInfoBackground->SetScale({ 0.8,0.8 });
    mPlayer2.mPlayerId.text = "Player: X";
    mPlayer2.mPlayerId.textColor = Black;
    mPlayer2.mPlayerId.SetTextScale(150, 80);
    mPlayer2.mPlayerId.pos = { 1130, 200 };
    mPlayer2.mWinTally.text = "Wins: " + std::to_string(mgr->GetPlayer()->loseTally);
    mPlayer2.mWinTally.textColor = Black;
    mPlayer2.mWinTally.SetTextScale(150, 80);
    mPlayer2.mWinTally.pos = { 1130, 290 };

    mSceneText.push_back(&mBoard.mTurnText);
    mSceneText.push_back(&mPlayer1.mPlayerId);
    mSceneText.push_back(&mPlayer1.mWinTally);
    mSceneText.push_back(&mPlayer2.mPlayerId);
    mSceneText.push_back(&mPlayer2.mWinTally);
}

void NoughtsAndCrossesScene::ChangeTurn()
{
    mPlayerTurn = !mPlayerTurn;
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
    if (act == Act::MouseUpdate)
    {

    }

    else if (act == Act::Click)
    {

    }
}
