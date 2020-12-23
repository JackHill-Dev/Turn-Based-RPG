#pragma once
#include "Button.h"

class SceneManager;

class StartButton :
    public Button
{
public:
	StartButton() {}
	StartButton(std::string sprSheet);
	void Select() override;
	bool Update(double dTime, Act act, std::pair<int, int> mouse) override;
	virtual StartButton* Clone() { return new StartButton(*this); };
};

