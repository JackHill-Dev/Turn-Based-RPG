#pragma once
#include <string>

class Item
{
public:
	Item() {}
	Item(std::string name, int cost);
	~Item();
	std::string GetName() const;
	int GetCost() const;
private:
	std::string mName;
	int mCost;
};

