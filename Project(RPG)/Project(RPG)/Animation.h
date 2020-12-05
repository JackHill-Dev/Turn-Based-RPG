#pragma once
class Animation
{
private:
	int mCurrentCell;
	int mStartCell, mEndCell;

public:
	Animation(int start, int end);
	int GetCurrentCell();
	void Advance();
};

