#include <string>
#include <vector>
#include <iostream>
#define MAX_SCOVILE 1000000

using namespace std;


class HeapNode
{
private:
	int K;

public:
	void SetK(int k_)
	{
		K = k_;
	}
	int GetK()
	{
		return K;
	}
};

class Heap
{
private:
	HeapNode node[MAX_SCOVILE];
	int size;

public:
	Heap() : size(0) {}

	bool isEmpty() { return size <= 0; }
	bool isFull() { return size == MAX_SCOVILE - 1; }
	int GetSize() { return size; }
	HeapNode GetNode(int i) { return node[i]; }

	void insert(int K)
	{
		if (isFull())
			return;

		size++;
		int i = size;

		while (i != 1 && K < GetParent(i).GetK()) //MIN HEAP
		{
			node[i] = GetParent(i);
			i /= 2;
		}

		node[i].SetK(K);
	}

	int remove()
	{
		if (isEmpty()) return -1;

		HeapNode item = node[1];
		HeapNode last = node[size--];

		int parent = 1;
		int child = 2;

		while (child <= size)
		{

			if (child < size && GetLeftChild(parent).GetK() > GetRightChild(parent).GetK()) // MIN_HEAP
				child++;

			if (last.GetK() <= node[child].GetK())
				break;

			node[parent] = node[child];
			parent = child;
			child = parent * 2;
		}

		node[parent] = last;
		return item.GetK();

	}

	HeapNode& GetParent(int i) { return node[i / 2]; }
	HeapNode& GetLeftChild(int i) { return node[2 * i]; }
	HeapNode& GetRightChild(int i) { return node[2 * i + 1]; }
};


bool isAllScovilleOverK(Heap* heap, int K)
{
	for (int i = 1; i < heap->GetSize() + 1; i++)
	{
		if (heap->GetNode(i).GetK() < K)
			return false;
	}
	return true;
}



int solution(vector<int> scoville, int K) {

	int totalBlend = 0;
	Heap *heap = new Heap();
	for (auto i = scoville.begin(); i != scoville.end(); i++)
	{
		heap->insert(*i);
	}

	int first;
	int second;

	while (!(heap->isEmpty()))
	{

		if (isAllScovilleOverK(heap, K))
			return totalBlend;

		if (heap->GetSize() <= 1) //2회 remove할 때, size가 0이하로 떨어지지 않게 하기 위함
			break;

		totalBlend++;

		first = heap->remove();
		second = heap->remove();

		int newFoodScoville = first + second * 2;

		heap->insert(newFoodScoville);

	}

	return -1;
}

int main()
{
	std::vector<int> scoville;
	scoville.push_back(0);
	scoville.push_back(0);
	scoville.push_back(1);

	int answer = solution(scoville, 3);

	std::cout << "answer : " << answer << std::endl;

	system("pause");

}
