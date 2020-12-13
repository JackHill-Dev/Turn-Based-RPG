#pragma once
#include "Button.h"


class SceneManager;

class StartButton :
    public Button
{

public:
	StartButton() {}
	StartButton(std::string sprSheet);
	void Select(Managers* mgrs) override;

	

};

