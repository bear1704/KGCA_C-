#pragma once
#include "HeapNode.h"
#define MAX_HEAP 200
#define MAX_ELEMENT 200

class Heap
{
private:
	HeapNode node[MAX_HEAP];
	int size; //사용 중인 노드의 갯수 

public:
	Heap();
	~Heap();

	bool isEmpty() { return size == 0; }
	bool isFull() { return size == MAX_ELEMENT - 1; } //배열의 0번 요소를 사용하지 않음

	HeapNode& getParent(int i) { return node[i / 2];  }
	HeapNode& getLeft(int i) { return node[i * 2]; }
	HeapNode& getRight(int i) { return node[i * 2 + 1]; }

	void insert(int key); //노드를 트리의 적절한 위치에 삽입한다.
	HeapNode remove(); //루트 노드를 뽑아내 리턴하고, 트리를 재정렬한다.
	void display();

	HeapNode find() { return node[1]; }  //첫 번째 노드(루트 노드) 리턴
};

