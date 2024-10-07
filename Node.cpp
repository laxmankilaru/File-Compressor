#include "Node.h"

Node::Node(char x, int f)
{
    character = x;
    frequency = f;
    this->left = nullptr;
    this->right = nullptr;
}

Node *Node::getleft() const
{
    return this->left;
}

Node *Node::getright() const
{
    return this->right;
}

void Node::setleft(Node *l)
{
    left = l;
}

void Node::setright(Node *r)
{
    right = r;
}

char Node::getchar() const
{
    return character;
}

int Node::getfrequency() const
{
    return frequency;
}
