#pragma once
#include "Globals.h"
#include "RenderObject.h"

class Node
{
private:

	RenderObject* mRenderObj;
	std::string mNodeName = "";
	std::string mNodeRole = "";
	std::pair<int, int> mNodePos = std::make_pair(0, 0);
	std::vector<Node*> mNodes;
	

public:
	Node();
	~Node();
	
	std::string GetNodeName() const;
	std::string GetNodeRole() const;
	RenderObject* GetRenderObject();
	Node* GetNode();

	void setNodeRole(std::string nodeRole);
	void setNodePos(int xVal, int yVal);
	void setRenderObject(RenderObject* rObj);

	void OnHover();
	void OnLeave();

	void AddNode(Node* node);
	void RemoveNode(Node* node);


};

