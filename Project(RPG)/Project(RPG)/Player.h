#pragma once

class Player
{

public:

	Player();
	~Player();


	bool isNought = false;
	bool isCrosses = false;
	int winTally = 0;

private:

	void AssignNought();
	void AssignCross();
	void PlayerWon();
	void ResetTally();

};

