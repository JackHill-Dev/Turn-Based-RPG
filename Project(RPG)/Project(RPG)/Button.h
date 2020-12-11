#pragma once
#include "UiObject.h"

class Button :
    public UiObject
{
public:
    Button() {}
    Button(std::string);
    virtual void Select() override;
};

