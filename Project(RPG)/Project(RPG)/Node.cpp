#include "Node.h"

Node::Node()
{
}

Node::~Node()
{
    for (Node* node : mNodes)
    {
        delete node;
    }
}

// Tint node yellow on hover
void Node::OnHover()
{
    mRenderObj->tint = SDL_Color{ 255,255, 0 }; 
}

// Tint node white on leave
void Node::OnLeave()
{
    mRenderObj->tint = SDL_Color{ 255, 255, 255 };
}

void Node::AddNode(Node* node)
{

}

void Node::RemoveNode(Node* node)
{

}


std::string Node::GetNodeName() const
{
    return mNodeName;
}

std::string Node::GetNodeRole() const
{
    return mNodeRole;
}

RenderObject* Node::GetRenderObject()
{
    return mRenderObj;
}

Node* Node::GetNode()
{
    return nullptr;
}

void Node::setNodeRole(std::string nodeRole)
{
    mNodeRole = nodeRole;
}

void Node::setNodePos(int xVal, int yVal)
{
    mNodePos = std::make_pair(xVal, yVal);
}

void Node::setRenderObject(RenderObject* rObj)
{
    mRenderObj = rObj;
}
