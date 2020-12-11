#include "Button.h"

Button::Button(std::string sprSheet) : UiObject(sprSheet)
{
	
}

void Button::Select()
{
	std::cout << "Button Pressed";
}
