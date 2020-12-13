#pragma once
#include "UiObject.h"

class SceneManager; // forward declared so the scene can be changed on button pressed
//class GameManager;
/// <summary>
/// A specification of the ui object that allows for button functionality - JP
/// </summary>

class Button :
    public UiObject
{
public:
    Button() {}
    Button(std::string);
    
    virtual void Select(Managers* mgrs) override;
};

