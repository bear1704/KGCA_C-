#pragma once
#include <iostream>
#include "BinaryTree.h"

int main()
{
	int val = 0;
	BinaryTree tree;
	

	std::cin >> val;
	BinaryNode *a = new BinaryNode(val, nullptr, nullptr);
	tree.SetRoot(a);
	

	

	tree.PreOrder();


	return 0;
}