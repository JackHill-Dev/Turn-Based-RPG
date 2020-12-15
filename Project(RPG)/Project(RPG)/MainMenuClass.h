#pragma once
#include "Scene.h"
#include "Actions.h"
#include <SDL.h>
#include <iostream>
class MainMenuClass :
    public Scene
{
public:
    MainMenuClass();
	void Init(Managers* mgrs);
    void Update(double dTime, Act act) override;
    void ViewSettings();
private:
    RenderObject* pMenuButton;
    RenderObject* pSettings;
};

