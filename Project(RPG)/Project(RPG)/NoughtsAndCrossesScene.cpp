#include "NoughtsAndCrossesScene.h"



NoughtsAndCrossesScene::NoughtsAndCrossesScene(Interface* mObjMgr) : Scene(mObjMgr)
{
    pGameBackground = AddObject("ChalkBoardObj", 640, 360, Layer::Background);
    pLeaveButton = AddObject("LeaveGameButtonObj", 145, 650, Layer::UI);
    pRematchButton = AddObject("RematchButtonObj", 1130, 650, Layer::UI);
    pRematchButton->SetScale(std::make_pair<float, float>(0.8, 0.65));
    pRematchButton->SetVisible(false);

    TopLeft.mPiece = AddObject("BoardPieceObj", mLeftPos, mTopHeight, Layer::Game);
    TopLeft.mNought = AddObject("NoughtObj", mLeftPos, mTopHeight, Layer::UI);
    TopLeft.mNought->SetVisible(false);
    TopLeft.mCross = AddObject("CrossObj", mLeftPos, mTopHeight, Layer::UI);
    TopLeft.mCross->SetVisible(false);

   
    TopCentre.mPiece = AddObject("BoardPieceObj", mMiddlePos, mTopHeight, Layer::Game);
    TopCentre.mNought = AddObject("NoughtObj", mMiddlePos, mTopHeight, Layer::UI);
    TopCentre.mNought->SetVisible(false);
    TopCentre.mCross = AddObject("CrossObj", mMiddlePos, mTopHeight, Layer::UI);
    TopCentre.mCross->SetVisible(false);

    
    TopRight.mPiece = AddObject("BoardPieceObj", mRightPos, mTopHeight, Layer::Game);
    TopRight.mNought = AddObject("NoughtObj", mRightPos, mTopHeight, Layer::UI);
    TopRight.mNought->SetVisible(false);
    TopRight.mCross = AddObject("CrossObj", mRightPos, mTopHeight, Layer::UI);
    TopRight.mCross->SetVisible(false);

   
    MidLeft.mPiece = AddObject("BoardPieceObj", mLeftPos, mMidHeight, Layer::Game);
    MidLeft.mNought = AddObject("NoughtObj", mLeftPos, mMidHeight, Layer::UI);
    MidLeft.mNought->SetVisible(false);
    MidLeft.mCross = AddObject("CrossObj", mLeftPos, mMidHeight, Layer::UI);
    MidLeft.mCross->SetVisible(false);

   
    MidCentre.mPiece = AddObject("BoardPieceObj", mMiddlePos, mMidHeight, Layer::Game);
    MidCentre.mNought = AddObject("NoughtObj", mMiddlePos, mMidHeight, Layer::UI);
    MidCentre.mNought->SetVisible(false);
    MidCentre.mCross = AddObject("CrossObj", mMiddlePos, mMidHeight, Layer::UI);
    MidCentre.mCross->SetVisible(false);

   
    MidRight.mPiece = AddObject("BoardPieceObj", mRightPos, mMidHeight, Layer::Game);
    MidRight.mNought = AddObject("NoughtObj", mRightPos, mMidHeight, Layer::UI);
    MidRight.mNought->SetVisible(false);
    MidRight.mCross = AddObject("CrossObj", mRightPos, mMidHeight, Layer::UI);
    MidRight.mCross->SetVisible(false);

    
    BottomLeft.mPiece = AddObject("BoardPieceObj", mLeftPos, mBottomHeight, Layer::Game);
    BottomLeft.mNought = AddObject("NoughtObj", mLeftPos, mBottomHeight, Layer::UI);
    BottomLeft.mNought->SetVisible(false);
    BottomLeft.mCross = AddObject("CrossObj", mLeftPos, mBottomHeight, Layer::UI);
    BottomLeft.mCross->SetVisible(false);

    
    BottomCentre.mPiece = AddObject("BoardPieceObj", mMiddlePos, mBottomHeight, Layer::Game);
    BottomCentre.mNought = AddObject("NoughtObj", mMiddlePos, mBottomHeight, Layer::UI);
    BottomCentre.mNought->SetVisible(false);
    BottomCentre.mCross = AddObject("CrossObj", mMiddlePos, mBottomHeight, Layer::UI);
    BottomCentre.mCross->SetVisible(false);

   
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
   
    mPlayerTurn = true;
    SetUpUI();
    SetUpBoardPieces();
}

void NoughtsAndCrossesScene::Load()
{
    mPlayerTurn = true;
    SetUpUI();
    SetUpBoardPieces();
}

void NoughtsAndCrossesScene::SetUpBoardPieces()
{
    for (auto& piece : pBoardPieces)
    {
        piece.bFilled = false;
        piece.mCross->SetVisible(false);
        piece.mNought->SetVisible(false);
    }
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

    mSceneText.push_back(&mBoard.mTurnText);    // 0
    mSceneText.push_back(&mPlayer1.mPlayerId);  // 1
    mSceneText.push_back(&mPlayer1.mWinTally);  // 2
    mSceneText.push_back(&mPlayer2.mPlayerId);  // 3
    mSceneText.push_back(&mPlayer2.mWinTally);  // 4
}

void NoughtsAndCrossesScene::ResolveGame()
{
    if (std::all_of(pBoardPieces.begin(), pBoardPieces.end(), [](BoardPiece piece) {
        return piece.bFilled == true;
        }))
    {
        mSceneText[0]->text = "IT'S A DRAW! Rematch?";
    }
    else if (mPlayerTurn == true)
    {
        mgr->GetPlayer()->winTally += 1;
        mSceneText[0]->text = "WINNER Player O! Rematch?";
        mSceneText[2]->text = "Wins: " + std::to_string(mgr->GetPlayer()->winTally);
    }
    else
    {
        mgr->GetPlayer()->loseTally += 1;
        mSceneText[0]->text = "WINNER Player X! Rematch?";
        mSceneText[4]->text = "Wins: " + std::to_string(mgr->GetPlayer()->loseTally);
    }

    for (auto& piece : pBoardPieces)
    {
        piece.bFilled = true;
    }

    pRematchButton->SetVisible(true);
}

void NoughtsAndCrossesScene::ResetGame()
{
    for (auto& piece : pBoardPieces)
    {
        piece.bFilled = false;
        piece.mCross->SetVisible(false);
        piece.mNought->SetVisible(false);
    }
    pRematchButton->SetVisible(false);
}

void NoughtsAndCrossesScene::ChangeTurn()
{
    mPlayerTurn = !mPlayerTurn;

    if (mPlayerTurn == true)
    {
        mSceneText[0]->text = "Current Turn: Player O";
    }
    else
    {
        mSceneText[0]->text = "Current Turn: Player X";
    }

}

void NoughtsAndCrossesScene::DrawSymbol(BoardPiece& selectedPiece)
{
    if (mPlayerTurn == true)
    {
        selectedPiece.bFilled = true;
        selectedPiece.mNought->SetVisible(true);
    }
    else
    {
        selectedPiece.bFilled = true;
        selectedPiece.mCross->SetVisible(true);
    }
}

void NoughtsAndCrossesScene::AssignSymbol()
{
}

bool NoughtsAndCrossesScene::hasWon()
{

    // Nought win conditions
         // Horizontal
         if (pBoardPieces[0].mNought->IsVisible() && pBoardPieces[1].mNought->IsVisible() && pBoardPieces[2].mNought->IsVisible())
         {
             return true;
         }
         else if (pBoardPieces[3].mNought->IsVisible() && pBoardPieces[4].mNought->IsVisible() && pBoardPieces[5].mNought->IsVisible())
         {
             return true;
         }
         else if (pBoardPieces[6].mNought->IsVisible() && pBoardPieces[7].mNought->IsVisible() && pBoardPieces[8].mNought->IsVisible())
         {
             return true;
         }

         // Vertical
         else if (pBoardPieces[0].mNought->IsVisible() && pBoardPieces[3].mNought->IsVisible() && pBoardPieces[6].mNought->IsVisible())
         {
             return true;
         }
         else if (pBoardPieces[1].mNought->IsVisible() && pBoardPieces[4].mNought->IsVisible() && pBoardPieces[7].mNought->IsVisible())
         {
             return true;
         }
         else if (pBoardPieces[2].mNought->IsVisible() && pBoardPieces[5].mNought->IsVisible() && pBoardPieces[8].mNought->IsVisible())
         {
             return true;
         }

         // Diagonal
         else if (pBoardPieces[0].mNought->IsVisible() && pBoardPieces[4].mNought->IsVisible() && pBoardPieces[8].mNought->IsVisible())
         {
             return true;
         }
         else if (pBoardPieces[2].mNought->IsVisible() && pBoardPieces[4].mNought->IsVisible() && pBoardPieces[6].mNought->IsVisible())
         {
             return true;
         }

     // Cross win conditions
        // Horizontal
         if (pBoardPieces[0].mCross->IsVisible() && pBoardPieces[1].mCross->IsVisible() && pBoardPieces[2].mCross->IsVisible())
         {
             return true;
         }
         else if (pBoardPieces[3].mCross->IsVisible() && pBoardPieces[4].mCross->IsVisible() && pBoardPieces[5].mCross->IsVisible())
         {
             return true;
         }
         else if (pBoardPieces[6].mCross->IsVisible() && pBoardPieces[7].mCross->IsVisible() && pBoardPieces[8].mCross->IsVisible())
         {
             return true;
         }

         // Vertical
         else if (pBoardPieces[0].mCross->IsVisible() && pBoardPieces[3].mCross->IsVisible() && pBoardPieces[6].mCross->IsVisible())
         {
             return true;
         }
         else if (pBoardPieces[1].mCross->IsVisible() && pBoardPieces[4].mCross->IsVisible() && pBoardPieces[7].mCross->IsVisible())
         {
             return true;
         }
         else if (pBoardPieces[2].mCross->IsVisible() && pBoardPieces[5].mCross->IsVisible() && pBoardPieces[8].mCross->IsVisible())
         {
             return true;
         }

         // Diagonal
         else if (pBoardPieces[0].mCross->IsVisible() && pBoardPieces[4].mCross->IsVisible() && pBoardPieces[8].mCross->IsVisible())
         {
             return true;
         }
         else if (pBoardPieces[2].mCross->IsVisible() && pBoardPieces[4].mCross->IsVisible() && pBoardPieces[6].mCross->IsVisible())
         {
             return true;
         }

    // Draw Condition
         else if (std::all_of(pBoardPieces.begin(), pBoardPieces.end(), [](BoardPiece piece) {
             return piece.bFilled == true;
             }))
         {
             return true;
         }

         else
         {
             return false;
         }
}



void NoughtsAndCrossesScene::Update(double dTime, Act act, std::pair<int, int> mousePos)
{
    if (act == Act::MouseUpdate)
    {
        if (pLeaveButton->InBounds(mousePos.first, mousePos.second))
        {
            pLeaveButton->Tint(Lime);
        }
        else
        {
            pLeaveButton->Untint();
        }
        if (pRematchButton->InBounds(mousePos.first, mousePos.second))
        {
            pRematchButton->Tint(Lime);
        }
        else
        {
            pRematchButton->Untint();
        }

        for (auto& piece : pBoardPieces)
        {
            if (piece.mPiece->InBounds(mousePos.first, mousePos.second) && (!piece.bFilled))
            {
                piece.mPiece->Tint(Lime);
            }
            else if(piece.mPiece->InBounds(mousePos.first, mousePos.second) && (piece.bFilled))
            {
                piece.mPiece->Tint(Gray);
                piece.mCross->Tint(Gray);
                piece.mNought->Tint(Gray);
            }
            else
            {
                piece.mPiece->Untint();
                piece.mCross->Untint();
                piece.mNought->Untint();
            }
        }
    }

    else if (act == Act::Click)
    {
        if (pLeaveButton->InBounds(mousePos.first, mousePos.second))
        {
            /*
            mgr->LoadScene(Scenes::MainMenu);
            mgr->GetPlayer()->loseTally = 0;
            mgr->GetPlayer()->winTally = 0;
            pLeaveButton->Untint();
            */

            mgr->Quit();
        }

        if (pRematchButton->InBounds(mousePos.first, mousePos.second))
        {
            ResetGame();
            ChangeTurn();
        }

        for (auto& piece : pBoardPieces)
        {
            // If you click an 'Empty' board piece then fill it.
            if (piece.mPiece->InBounds(mousePos.first, mousePos.second) && (!piece.bFilled))
            {
                piece.mPiece->Untint();
                DrawSymbol(piece);
                if (hasWon() == true)
                {
                    ResolveGame();
                   
                }
                else
                {
                    ChangeTurn();
                }
            }
        }
    }
}
