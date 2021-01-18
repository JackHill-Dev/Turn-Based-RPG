#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <SDL.h>
#include <SDL_ttf.h>
#include "RenderObject.h"
#include "Globals.h"
#include "GameObjects.h"

#include "Interface.h"

struct UIText
{
	std::string text;
	std::pair<int, int> pos;
	SDL_Color textColor;
	bool isVisible = true;
};

struct CheckBox
{
	RenderObject* obj;
	bool bIsChecked = false;
};

class Scene
{
private:
	
	std::string name;
	int counter = 0;
	SDL_Surface* mSurface = nullptr;
	TTF_Font* mFont;
protected:
	std::vector<std::vector<RenderObject*>> mLayers;
	std::vector<UIText> mSceneText;

	virtual void Update(double dTime, Act act, std::pair<int, int> mousePos);
	
	Interface* mgr;
public:
	Scene(Interface* objmg);

	void SceneUpdate(double dTime, Act act, std::pair<int, int> mousePos);

	void Draw(SDL_Renderer* rnd);
	
	void Clear(SDL_Renderer* rnd);
	RenderObject* AddObject(std::string obj, int x, int y, Layer layerNum);
};

