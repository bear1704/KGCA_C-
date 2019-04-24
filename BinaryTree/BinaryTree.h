#pragma once
#include <iostream>
#include "BinaryNode.h"

class BinaryTree
{
	BinaryNode* root;

public:
	BinaryTree();
	~BinaryTree();

	void SetRoot(BinaryNode* node);
	BinaryNode* GetRoot();
	bool IsEmpty();

	void InOrder();
	void InOrder(BinaryNode* node);
	void PreOrder();
	void PreOrder(BinaryNode* node);
	void PostOrder();
	void PostOrder(BinaryNode* node);
	void LevelOrder();



};

