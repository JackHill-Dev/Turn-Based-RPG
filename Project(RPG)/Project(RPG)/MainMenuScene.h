#pragma once
#include "Scene.h"
#include <fstream>
#include <SDL.h>
#include <iostream>


class MainMenuScene :
    public Scene
{
public:

    MainMenuScene(Interface* rng);
    void Load();
    void OnHover(RenderObject* rObj);
    void OnLeave(RenderObject* rObj);

protected:

    void Update(double dTime, Act act, std::pair<int, int> mouse) override;

private:

    Mix_Music* mStartMus;
    Mix_Chunk* confirm_SFX;
    Mix_Chunk* back_SFX;

    RenderObject* pMenuBg;
    RenderObject* pNoughtsAndCrossesGraphic;
    RenderObject* pBanner;

    // Main menu buttons
    RenderObject* pStartButton;
    RenderObject* pQuitButton;
    RenderObject* pHostGameButton;
    RenderObject* pJoinGameButton;
    std::vector<RenderObject*> buttons;

};

