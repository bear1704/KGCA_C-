#pragma once
#include <iostream>
#include "BinaryTree.h"
#include "BinarySearchTree.h"

int main()
{
	
	BinarySearchTree tree;

	BinaryNode *d = new BinaryNode('D', nullptr, nullptr);
	BinaryNode *e = new BinaryNode('E', nullptr, nullptr);
	BinaryNode *b = new BinaryNode('B', d, e);
	BinaryNode *f = new BinaryNode('F', nullptr, nullptr);
	BinaryNode *c = new BinaryNode('C', f, nullptr);
	BinaryNode *a = new BinaryNode('A', b, c);
	
	tree.SetRoot(a);

	tree.LevelOrder(a);

	std::cout << "\n��\n" << std::endl;

	std::cout << "����Լ��� ������ �˻� : " << tree.SearchRecursive(a, 68)->GetData() << std::endl;


	system("pause");

	return 0;
}