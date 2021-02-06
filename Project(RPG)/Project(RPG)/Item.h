#pragma once
//#include <string>
#include "RenderObject.h"
#include <string.h>
struct InvPos
{
	std::pair<int, int> pos = std::make_pair(0,0);
	bool gridPosFilled = false;
};

enum ItemType
{
	UNDEFINED = 0,
	ARMOUR,
	WEAPON
};
class Item
{
public:
	Item() {}
	Item(std::string name, int cost);
	~Item();
	virtual std::string GetDescription() = 0;
	std::string GetName() const;
	std::string GetObjName() const;
	int GetCost() const;
	RenderObject* GetRenderObject();
	void SetObjName(std::string name);
	void SetRenderObject(RenderObject* obj);
	ItemType GetType() { return mType; }
	void OnHover();
	void OnLeave();
	bool bPickedUp = false;
	bool bEquipped = false;
	InvPos inventoryPos;
protected:
	std::string mName;
	std::string mObjName;
	ItemType mType = UNDEFINED;
private:
	RenderObject* mRenderObject;

	int mCost;
	
	
	
	
};

