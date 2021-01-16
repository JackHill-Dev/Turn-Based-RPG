#pragma once
#include "Scene.h"
#include "Actions.h"
#include "ProgressBar.h"
#include <SDL.h>
#include <iostream>
class MainMenuScene :
    public Scene
{
public:
    MainMenuScene(Interface* rng);
protected:
    void Update(double dTime, Act act, std::pair<int, int> mouse) override;
private:
    void SetupSettings();
    void UpdateSettings(Act act, std::pair<int, int> mouse);
    void ShowSettings( bool actvis);
    void Collapse(bool collapsed);
    // Main menu buttons
    RenderObject* start;
    RenderObject* quit;
    RenderObject* settings;

    // Settings UI elements
    RenderObject* settingsOverlay;
    RenderObject* SettingsCloseBtn;
    RenderObject* dropDownCollapsed;
    RenderObject* dropDownUnCollapsed;
	// RenderObject* ResOption1;
	// RenderObject* ResOption2;
	// RenderObject* ResOption3;

    // temp 
    RenderObject* resChange;
};

