#pragma once
#include "Scene.h"
#include "Actions.h"
#include <SDL.h>
#include <iostream>
class MainMenuClass :
    public Scene
{
public:
    MainMenuClass(Interface* rng);
protected:
    void Update(double dTime, Act act, std::pair<int, int> mouse) override;
private:
    RenderObject* pMenuButton;
};

