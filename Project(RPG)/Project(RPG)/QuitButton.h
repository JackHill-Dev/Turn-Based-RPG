#pragma once
#include "Button.h"
class QuitButton :
    public Button
{
public:
    QuitButton() {}
    QuitButton(std::string sprSheet);


    bool Update(double dTime, Act act, std::pair<int, int> mouse) override;
    virtual QuitButton* Clone() { return new QuitButton(*this); };
};

