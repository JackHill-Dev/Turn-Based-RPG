#pragma once
#include <utility>
#include <string>
#include "SpriteSheet.h"
#include "Actions.h"
#include "Animation.h"


class RenderObject
{

private:
	
	
	std::string mName;
	bool mVisible;
	SpriteSheet* mSheet;
protected:
	
	std::pair<double, double> mPos;
	Animation* mCurrentAnim;
public:
	std::pair<float, float> scale;
	void Untint();
	void Tint(SDL_Colour tkint);
	std::string path;
	RenderObject() {}
	RenderObject(std::string sprSheet, std::pair<float, float> scale = std::make_pair(1,1));
	SDL_Color tint = { 255,255,255 }; //white
	SDL_Color GetTint() { return tint; }
	virtual bool Update(double dTime, Act act, std::pair<int, int> mouse);
	bool Init();
	std::pair<int, int> GetPos();
	std::pair<float, float> GetScale() { return scale; }
	void SetAnim(std::string id);
	void SetPos(std::pair<int, int> nPos);
	void SetScale(std::pair<float, float> nScale) { scale = nScale; }
	void SetTexture(SpriteSheet* nSheet);
	void SetVisible(const bool vis);
	SpriteSheet* GetSheet();
	bool IsVisible();
	bool InBounds(int x, int y);
	virtual void Select();
	Animation* GetAnim();
	virtual RenderObject* Clone() { return new RenderObject(*this); }
};

