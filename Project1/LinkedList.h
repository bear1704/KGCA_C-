#pragma once
#include "HeaderManager.h"
#include "Node.h"



class Node;


class LinkedList
{
public:

	Node* head;
	Node* tail;
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
};

