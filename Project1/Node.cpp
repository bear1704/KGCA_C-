#include "Node.h"



Node::Node(StudentData student_, Node* next_, Node* prev_)
{
	data = student_;
	next = next_;
	prev = prev_;
}

Node::Node() 
{

}

Node::~Node()
{

}
