#pragma once
#include "Scene.h"
#include "Actions.h"
#include "SettingsButton.h"

#include <SDL.h>
#include <iostream>
class CloseButton;

class MainMenuClass :
    public Scene
{
public:
    MainMenuClass(ObjectManager* rng);
    void Init(Managers* mgrs);
    void Update(double dTime, Act act) override;
    void ViewSettings();
    void CloseSettings();
private:
    void SetupObjects();
    void SetupButtons();
    
private:
    RenderObject* pStartButton;
    RenderObject* pQuitButton;
    SettingsButton* pSettingsButton;
    CloseButton* pCloseButton;
    RenderObject* pSettingsOverlay;
};

