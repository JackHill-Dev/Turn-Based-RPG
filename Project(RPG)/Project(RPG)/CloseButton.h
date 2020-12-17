#pragma once
#include "Button.h"
class MainMenuClass;

class CloseButton :
    public Button
{
public:
	CloseButton() {}
	CloseButton(std::string sprSheet);
	void Select(Managers* mgrs) override;
private:
	MainMenuClass* pMainMenu;

};

