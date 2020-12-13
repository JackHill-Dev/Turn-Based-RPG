#include "Button.h"
#include "SceneManager.h"
#include "GameManager.h"
Button::Button(std::string sprSheet) : UiObject(sprSheet)
{
	
}

void Button::Select(SceneManager* sceneManager, GameManager* gameMgr)
{
	std::cout << "Button Pressed";

}


