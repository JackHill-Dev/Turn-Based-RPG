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
    void SetupSettings();
    void SetupResOptions();
    void UpdateSettings(Act act, std::pair<int, int> mouse);
    void ShowSettings( bool actvis);
    void ApplySettings();
    void Collapse(bool collapsed);
    // Main menu buttons
    RenderObject* start;
    RenderObject* quit;
    RenderObject* settings;
    RenderObject* ApplyBtn;

    // Settings UI elements
    RenderObject* settingsOverlay;
    RenderObject* SettingsCloseBtn;
    RenderObject* dropDownCollapsed;
   // RenderObject* dropDownUnCollapsed;

    std::vector<DropDownOption> resOptions;
    UIText currentRes;
    CheckBox mFsCheckBox;
	// RenderObject* ResOption1;
	// RenderObject* ResOption2;
	// RenderObject* ResOption3;

    // temp 
    RenderObject* resChange;
};

