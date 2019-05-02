#pragma once
#include "BinaryTree.h"

class BinarySearchTree :
	public BinaryTree
{
public:
	BinarySearchTree();
	~BinarySearchTree();


	BinaryNode* SearchRecursive(BinaryNode* n, int key);
};

