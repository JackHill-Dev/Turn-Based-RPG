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
    void Update(double dTime, Act act) override;
private:
    RenderObject* pMenuButton;
};

