#pragma once
//#include <string>
#include "RenderObject.h"
class Item
{
public:
	Item() = delete;
	Item(std::string name, int cost);
	~Item();
	std::string GetName() const;
	std::string GetObjName() const;
	int GetCost() const;
	RenderObject* GetRenderObject();
	void SetObjName(std::string name);
	void SetRenderObject(RenderObject obj);
	void OnHover();
	void OnLeave();
private:
	std::string mName;
	std::string mObjName;
	RenderObject mRenderObject;
	int mCost;
};

