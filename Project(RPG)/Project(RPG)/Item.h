#pragma once
#include <string>

class Item
{
public:
	Item(std::string& name, int cost);
	std::string GetName() const;
	int GetCost() const;
private:
	std::string mName;
	int mCost;
};

