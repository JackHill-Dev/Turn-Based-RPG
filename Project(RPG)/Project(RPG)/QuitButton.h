#pragma once
#include "Button.h"
class QuitButton :
    public Button
{
public:
    QuitButton() {}
    QuitButton(std::string sprSheet);

    void Select(Managers* mgrs) override;

};

