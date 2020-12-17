#pragma once
#include "Button.h"
class MainMenuClass;

class SettingsButton :
    public Button
{
public:
	SettingsButton(){}
	SettingsButton(std::string sprSheet);
	void Select(Managers* mgrs) override;
};

