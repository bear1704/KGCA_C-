#pragma once
#include "HeaderManager.h"


class Node
{
	
public:
	StudentData student;
	Node* next;
	Node* prev;

public:
	Node(StudentData student_, Node* next_, Node* prev_);
	Node();
	~Node();
};

