#include "HeapNode.h"

HeapNode::HeapNode()
{

}


HeapNode::HeapNode(int key)
{
	this->key = key;
}

HeapNode::~HeapNode()
{
}

void HeapNode::SetKey(int k)
{
	key = k;
}

int HeapNode::GetKey()
{
	return key;
}

void HeapNode::DisplayKey()
{
	printf("%4d", key);
}
