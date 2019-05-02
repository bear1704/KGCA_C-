#pragma once
#include <iostream>

class HeapNode
{
private:
	int key;

public:
	HeapNode();
	HeapNode(int key);
	~HeapNode();

	void SetKey(int k);
	int GetKey();
	void DisplayKey();

};

