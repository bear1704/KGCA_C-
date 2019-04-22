#pragma once
#include "HeaderManager.h"
#include "StudentData.h"


class Node
{
	
public:
	StudentData data;
	Node* next;
	Node* prev;

public:
	Node(StudentData student_, Node* next_, Node* prev_);
	Node();
	~Node();

};

	