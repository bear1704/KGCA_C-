#pragma once
class BinaryNode
{
private:
	int data;
	BinaryNode* left;
	BinaryNode* right;

public:
	BinaryNode(int val, BinaryNode* left, BinaryNode* right);
	~BinaryNode();

	void SetData(int val);
	void SetLeft(BinaryNode* left);
	void SetRight(BinaryNode* right);
	int GetData();
	BinaryNode* GetRight();
	BinaryNode* GetLeft();

	void Insert(int val);

};

