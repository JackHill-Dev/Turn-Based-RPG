#pragma once
#include "Scene.h"
#include "Actions.h"
#include <SDL.h>
#include <iostream>
class MainMenuClass :
    public Scene
{
    void Update(double dTime, Act act) override;

};

