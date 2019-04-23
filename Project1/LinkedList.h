#pragma once
#include "HeaderManager.h"
#include "Node.h"



class Node;


class LinkedList
{
private:

	Node* head;
	Node* tail;
public:
	static int index;

public:
	LinkedList();
	~LinkedList();
	Node* CreateNode(int index, const char* name, const int age, const int korScore, const int mathScore);
	void InsertStudent();
	void InsertStudentNode(Node* node);
	void SortData();
	Node* SwapStudent(Node* A, Node* B);
	void DeleteStudent(Node* node);
	void IndexRearrange();
	void PrintData();
	void SearchModify();
	void SearchDeleteTarget(char* name);
	void WriteSampleData();
	void AllFree(Node* node);
	Node* getHead();
	Node* getTail();
	void SetHeadAndTail(Node* head_ = nullptr, Node* tail_ = nullptr);


};

