#include "Animation.h"
Animation::Animation(int start, int end)
{
	mStartCell = start;
	mEndCell = end;
	mCurrentCell = start;
}

int Animation::GetCurrentCell()
{
	return mCurrentCell;
}

void Animation::Advance()
{
	mCurrentCell++;
	if (mCurrentCell > mEndCell)
		mCurrentCell = mStartCell;
}