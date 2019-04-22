#include "Node.h"



Node::Node(StudentData student_, Node* next_, Node* prev_)
{
	student = student_;
	next = next_;
	prev = prev_;
}

Node::Node() 
{

}

Node::~Node()
{
}
