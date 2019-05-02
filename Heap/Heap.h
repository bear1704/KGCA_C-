#pragma once
#include "HeapNode.h"
#define MAX_HEAP 200
#define MAX_ELEMENT 200

class Heap
{
private:
	HeapNode node[MAX_HEAP];
	int size; //��� ���� ����� ���� 

public:
	Heap();
	~Heap();

	bool isEmpty() { return size == 0; }
	bool isFull() { return size == MAX_ELEMENT - 1; } //�迭�� 0�� ��Ҹ� ������� ����

	HeapNode& getParent(int i) { return node[i / 2];  }
	HeapNode& getLeft(int i) { return node[i * 2]; }
	HeapNode& getRight(int i) { return node[i * 2 + 1]; }

	void insert(int key); //��带 Ʈ���� ������ ��ġ�� �����Ѵ�.
	HeapNode remove(); //��Ʈ ��带 �̾Ƴ� �����ϰ�, Ʈ���� �������Ѵ�.
	void display();

	HeapNode find() { return node[1]; }  //ù ��° ���(��Ʈ ���) ����
};

