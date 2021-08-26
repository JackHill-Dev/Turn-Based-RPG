#pragma once

class Player
{

public:

	Player();
	~Player();


	bool isNought = false;
	bool isCrosses = false;
	bool isDraw = false;
	int winTally = 0;
	int loseTally = 0;

private:

	void AssignNought();
	void AssignCross();
	void PlayerWon();
	void PlayerLoss();
	void ResetTally();

};

