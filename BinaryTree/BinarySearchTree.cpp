#include "BinarySearchTree.h"



BinarySearchTree::BinarySearchTree()
{
}


BinarySearchTree::~BinarySearchTree()
{
}


BinaryNode* BinarySearchTree::SearchRecursive(BinaryNode * n, int key)
{
	if (n == nullptr)
		return nullptr;

	if (n->GetData() == key)
		return n;
	else if (n->GetData() > key)
		return SearchRecursive(n->GetLeft(), key);
	else if(n->GetData() < key)
		return SearchRecursive(n->GetRight(), key);

}
