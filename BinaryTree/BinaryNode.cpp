#include "BinaryNode.h"



BinaryNode::BinaryNode(int val, BinaryNode * left, BinaryNode * right) : data(val)
{
	this->left = left; this->right = right;
}

BinaryNode::~BinaryNode()
{
}

void BinaryNode::SetData(int val)
{
	data = val;
}

void BinaryNode::SetLeft(BinaryNode * left)
{
	this->left = left;
}

void BinaryNode::SetRight(BinaryNode * right)
{
	this->right = right;
}

int BinaryNode::GetData()
{
	return data;
}

BinaryNode * BinaryNode::GetRight()
{
	return right;
}

BinaryNode * BinaryNode::GetLeft()
{
	return left;
}

void BinaryNode::Insert(int val)
{
	if (val < GetData() && GetLeft() == nullptr)
	{
		left = new BinaryNode(val, nullptr, nullptr);
		return;
	}
	if (val > GetData() && GetRight() == nullptr)
	{
		right = new BinaryNode(val, nullptr, nullptr);
		return;
	}
	if (val < GetData())
		left->Insert(val);
	else if (val > GetData())
		right->Insert(val);


	
}
