#pragma once
#include "HeaderManager.h"
#include "StudentData.h"

class Node
{
	
private:
	StudentData* data;
	Node* next;
	Node* prev;

public:
	Node(StudentData *student_, Node* next_, Node* prev_);
	Node();
	~Node();
	Node* getNext();
	Node* getPrev();
	void SetNextAndPrev(Node* next_ = nullptr, Node* prev_ = nullptr);
	StudentData* getData();
	void SetData(StudentData* data_);
	void SetAdressPrevToNext(Node* source, Node* target);
	StudentData** getDataAdr();
	Node& operator=(const Node& pt);


};

	