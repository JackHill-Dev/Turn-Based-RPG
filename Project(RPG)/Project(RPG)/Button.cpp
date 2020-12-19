#include "Button.h"
#include "SceneManager.h"
#include "ManagerStruct.h"
Button::Button(std::string sprSheet) : UiObject(sprSheet)
{
	
}

void Button::Select()
{
	std::cout << "Button Pressed";

}


