#pragma once
#include <string>

class Item
{
public:
	virtual void SetName(std::string& name) = 0;
	virtual void SetCost(int& name) = 0;
	std::string GetName() const;
	int GetCost() const;
private:
	std::string mName;
	int mCost;
};

