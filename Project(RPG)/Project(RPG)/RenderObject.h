#pragma once
#include <utility>
#include <string>
#include "SpriteSheet.h"
#include "Actions.h"
#include "Animation.h"
#include "ManagerStruct.h"

class SceneManager;
class GameManager;

class RenderObject
{

private:
	
	
	std::string mName;
	bool mVisible;
	SpriteSheet* mSheet;
protected:
	Managers* mgrs;
	std::pair<double, double> mPos;
	Animation* mCurrentAnim;
public:
	std::string path;
	RenderObject();
	RenderObject(std::string sprSheet);
	SDL_Color tint = { 255,255,255 }; //white
	virtual bool Update(double dTime, Act act, std::pair<int, int> mouse);
	bool Init(Managers* mgrs);
	std::pair<int, int> GetPos();
	void SetAnim(std::string id);
	void SetPos(std::pair<int, int> nPos);
	void SetTexture(SpriteSheet* nSheet);
	SpriteSheet* GetSheet();
	bool IsVisible();
	bool InBounds(int x, int y);
	virtual void Select();
	Animation* GetAnim();
	virtual RenderObject* Clone() { return new RenderObject(*this); }
};

