#pragma once
#include "Scene.h"
#include "Actions.h"
#include "ProgressBar.h"
#include <fstream>
#include <SDL.h>
#include <iostream>

struct DropDownOption
{
    RenderObject* obj = nullptr;
    UIText ResOption;
    int w, h;
};

class MainMenuScene :
    public Scene
{
public:
    MainMenuScene(Interface* rng);
protected:
    void Update(double dTime, Act act, std::pair<int, int> mouse) override;
private:

    Mix_Chunk* confirm_SFX;
    Mix_Chunk* back_SFX;

    // Main menu buttons
    RenderObject* start;
    RenderObject* quit;
    RenderObject* settings;
    RenderObject* ApplyBtn;

};

