#include "BinaryTree.h"
#include <queue>
#include <conio.h>

static std::queue<BinaryNode*> levelQueue;

BinaryTree::BinaryTree()
{
	root = nullptr;
}


BinaryTree::~BinaryTree()
{
}

void BinaryTree::SetRoot(BinaryNode * node)
{
	root = node;
}

BinaryNode * BinaryTree::GetRoot()
{
	return root;
}

bool BinaryTree::IsEmpty()
{
	if (!root)
		return false;
	else
		return true;
}

void BinaryTree::InOrder()
{
	InOrder(root);
}

void BinaryTree::InOrder(BinaryNode * node) // LVR
{
	if (node->GetLeft() != nullptr)
		InOrder(node->GetLeft());
	
	std::cout <<  node->GetData() << " ";

	if (node->GetRight() != nullptr)
		InOrder(node->GetRight());
}

void BinaryTree::PreOrder()
{
	PreOrder(root);
}

void BinaryTree::PreOrder(BinaryNode* node) //VLR 
{
	std::cout <<  node->GetData() << "\n";
	
	if (node->GetLeft() != nullptr)
		PreOrder(node->GetLeft());
	if (node->GetRight() != nullptr)
		PreOrder(node->GetRight());
}

void BinaryTree::PostOrder()
{
	PostOrder(root);
}

void BinaryTree::PostOrder(BinaryNode * node)
{
	if (node->GetLeft() != nullptr)
		PostOrder(node->GetLeft());
	if (node->GetRight() != nullptr)
		PostOrder(node->GetRight());
	
	std::cout << node->GetData() << " ";
}

void BinaryTree::LevelOrder(BinaryNode* node)
{
	levelQueue.push(node);

	while (!levelQueue.empty())
	{
		if (levelQueue.front())
		{
			std::cout << levelQueue.front()->GetData() << " ";
			
			if(levelQueue.front()->GetLeft() != nullptr)
				levelQueue.push(levelQueue.front()->GetLeft());
			if (levelQueue.front()->GetRight() != nullptr)
				levelQueue.push(levelQueue.front()->GetRight());

			levelQueue.pop();

			std::cout << ".." << std::endl;
		} 
	}

}
