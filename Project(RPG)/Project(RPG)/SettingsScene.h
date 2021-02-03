#pragma once
#include "Scene.h"
#include "json.hpp"

struct ResolutionOption
{
	RenderObject* obj = nullptr;
	UIText ResOption;
	int w, h;
};


class SettingsScene :
    public Scene
{
public:
    SettingsScene(Interface* interface);
    void ApplySettings();
    void Collapse(bool collapsed);
    void Setup();
    void SetupResOptions();
private:
    RenderObject* checkBox;
    RenderObject* ApplyBtn;
    RenderObject* dropdownCollapsed;
    RenderObject* settingsCloseBtn;

    Mix_Chunk* confirm_SFX;
    Mix_Chunk* back_SFX;
    Mix_Chunk* button_Click_SFX;
    UIText currentRes;
    std::vector<ResolutionOption> resOptions;
protected:
    void Update(double dTime, Act act, std::pair<int, int> mousePos) override;

};

